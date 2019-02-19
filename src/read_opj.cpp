/*
Copyright (C) 2019 Ivan Krylov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
*/

#include <algorithm>
#include <string>

#include <Rcpp.h>
using namespace Rcpp;

#include "OriginFile.h"

static DataFrame import_spreadsheet(const Origin::SpreadSheet & osp) {
	List rsp(osp.columns.size());
	CharacterVector names(rsp.size()), comments(rsp.size()), commands(rsp.size());

	for (unsigned int c = 0; c < osp.columns.size(); c++) {
		const Origin::SpreadColumn & ocol = osp.columns[c];
		names[c] = ocol.name;
		comments[c] = ocol.comment; // user might want to split by \r\n...
		commands[c] = ocol.command;
		if (
			std::all_of(
				ocol.data.begin(), ocol.data.end(),
				[](const Origin::variant & v){
					return v.type() == Origin::variant::V_DOUBLE;
				}
			)
		){
			NumericVector ncol(osp.maxRows, NA_REAL);
			for (int row = 0; row < std::min(ocol.data.size(), (size_t)osp.maxRows); row++) {
				ncol[row] = ocol.data[row].as_double();
				if (ncol[row] == _ONAN) ncol[row] = NAN;
			}
			rsp[c] = ncol;
		} else {
			CharacterVector ccol(osp.maxRows, NA_STRING);
			for (int row = 0; row < std::min(ocol.data.size(), (size_t)osp.maxRows); row++) {
				const Origin::variant & v = ocol.data[row];
				if (v.type() == Origin::variant::V_DOUBLE)
					ccol[ocol.beginRow + row] =
						v.as_double() == _ONAN ? "NaN"
						: std::to_string(v.as_double()); // yuck
				else
					ccol[ocol.beginRow + row] = v.as_string();
			}
			rsp[c] = ccol;
		}
	}

	rsp.attr("names") = names;
	DataFrame dsp(rsp);
	// must preserve the attributes - assign them after creating DF
	dsp.attr("comments") = comments;
	dsp.attr("commands") = commands;
	return dsp;
}

// [[Rcpp::export(name="read.opj")]]
List read_opj(const std::string & file) {
	OriginFile opj(file);

	if (!opj.parse()) stop("Failed to open and/or parse " + file); // throws

	unsigned int items = opj.spreadCount() + opj.excelCount(), j = 0;
	List ret(items);
	CharacterVector retn(items);


	for (unsigned int i = 0; i < opj.spreadCount(); i++, j++) {
		const Origin::SpreadSheet & osp = opj.spread(i);
		ret[j] = import_spreadsheet(osp);
		retn[j] = osp.name;
	}

	for (unsigned int i = 0; i < opj.excelCount(); i++) {
		const Origin::Excel & oex = opj.excel(i);

		List exl(oex.sheets.size());
		CharacterVector exln(oex.sheets.size());

		for (size_t sp = 0; sp < oex.sheets.size(); sp++) {
			exl[sp] = import_spreadsheet(oex.sheets[sp]);
			exln[sp] = oex.sheets[sp].name;
		}

		exl.attr("names") = exln;

		ret[j] = exl;
		retn[j] = oex.name;
	}
	ret.attr("names") = retn;

	// TODO: matrix, excel, graph, note

	// FIXME: "dataset" and "function" are going to be untested
	// because I cannot find them in my copy of Origin

    return ret;
}
