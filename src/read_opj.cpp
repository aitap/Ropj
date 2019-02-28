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

static String decode_string(const std::string & s, const char * encoding) {
	Environment base("package:base");
	Function iconv = base["iconv"];
	return iconv(s, Named("from", encoding), Named("to", ""));
}

static DataFrame import_spreadsheet(const Origin::SpreadSheet & osp) {
	List rsp(osp.columns.size());
	StringVector names(rsp.size()), comments(rsp.size()), commands(rsp.size());

	for (unsigned int c = 0; c < osp.columns.size(); c++) {
		const Origin::SpreadColumn & ocol = osp.columns[c];
		names[c] = String(ocol.name, CE_LATIN1);
		comments[c] = String(ocol.comment, CE_LATIN1);
		commands[c] = String(ocol.command, CE_LATIN1);
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
				if (ncol[row] == _ONAN) ncol[row] = R_NaN;
			}
			rsp[c] = ncol;
		} else {
			StringVector ccol(osp.maxRows, NA_STRING);
			for (int row = 0; row < std::min(ocol.data.size(), (size_t)osp.maxRows); row++) {
				const Origin::variant & v = ocol.data[row];
				if (v.type() == Origin::variant::V_DOUBLE) {
					if (v.as_double() != _ONAN) ccol[row] = std::to_string(v.as_double()); // yuck
				} else {
					ccol[row] = String(v.as_string(), CE_LATIN1);
				}
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

static NumericVector make_dimnames(double from, double to, unsigned short size) {
	Environment base("package:base");
	Function seq = base["seq"];
	return seq(Named("from", from), Named("to", to), Named("length.out", size));
}

static List import_matrix(const Origin::Matrix & omt) {
	List ret(omt.sheets.size());
	StringVector names(ret.size()), commands(ret.size());
	for (unsigned int i = 0; i < omt.sheets.size(); i++) {
		NumericMatrix rms(Dimension(omt.sheets[i].rowCount, omt.sheets[i].columnCount));
		std::copy_n(omt.sheets[i].data.begin(), rms.size(), rms.begin());
		std::replace(rms.begin(), rms.end(), _ONAN, R_NaN);

		List dimnames(2);
		dimnames[0] = make_dimnames(
			omt.sheets[i].coordinates[3], omt.sheets[i].coordinates[1],
			omt.sheets[i].rowCount
		);
		dimnames[1] = make_dimnames(
			omt.sheets[i].coordinates[2], omt.sheets[i].coordinates[0],
			omt.sheets[i].columnCount
		);
		rms.attr("dimnames") = dimnames;

		ret[i] = rms;
		names[i] = omt.sheets[i].name;
		commands[i] = omt.sheets[i].command;
	}
	ret.attr("names") = names;
	ret.attr("commands") = commands;
	return ret;
}

// [[Rcpp::export(name="read.opj")]]
List read_opj(const std::string & file) {
	OriginFile opj(file);

	if (!opj.parse()) stop("Failed to open and/or parse " + file); // throws

	unsigned int j = 0,
		items = opj.spreadCount() + opj.excelCount() + opj.matrixCount() + opj.noteCount();
	List ret(items);
	StringVector retn(items), retl(items);


	for (unsigned int i = 0; i < opj.spreadCount(); i++, j++) {
		const Origin::SpreadSheet & osp = opj.spread(i);
		retn[j] = String(osp.name, CE_LATIN1);
		retl[j] = String(osp.label, CE_LATIN1);
		ret[j] = import_spreadsheet(osp);
	}

	for (unsigned int i = 0; i < opj.excelCount(); i++, j++) {
		const Origin::Excel & oex = opj.excel(i);
		retn[j] = String(oex.name, CE_LATIN1);
		retl[j] = String(oex.label, CE_LATIN1);

		List exl(oex.sheets.size());
		StringVector exln(oex.sheets.size());

		for (size_t sp = 0; sp < oex.sheets.size(); sp++) {
			exl[sp] = import_spreadsheet(oex.sheets[sp]);
			exln[sp] = String(oex.sheets[sp].name, CE_LATIN1);
		}

		exl.attr("names") = exln;
		ret[j] = exl;
	}

	for (unsigned int i = 0; i < opj.matrixCount(); i++, j++) {
		const Origin::Matrix & omt = opj.matrix(i);
		retn[j] = String(omt.name, CE_LATIN1);
		retl[j] = String(omt.label, CE_LATIN1);
		ret[j] = import_matrix(omt);
	}

	for (unsigned int i = 0; i < opj.noteCount(); i++, j++) {
		const Origin::Note & ont = opj.note(i);
		retn[j] = String(ont.name, CE_LATIN1);
		retl[j] = String(ont.label, CE_LATIN1);
		ret[j] = String(ont.text, CE_LATIN1);
	}

	ret.attr("names") = retn;
	ret.attr("comment") = retl;
    return ret;
}
