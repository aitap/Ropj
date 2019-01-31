#include <string>

#include <Rcpp.h>
using namespace Rcpp;

#include "OriginFile.h"

template<int T, typename U> // REALSXP or STRSXP
struct unlist {
	static const U NA_value;
	Vector<T> operator()(const List & list) {
		// like R unlist, but supplement NULLs with NAs
		Vector<T> ret(list.size());
		for (unsigned int i = 0; i < list.size(); i++)
			ret[i] = Rf_isNull(list[i]) ? NA_value : as<T>(list[i]);
		return ret;
	}
};

template<>
const decltype(NA_STRING) unlist<STRSXP,decltype(NA_STRING)>::NA_value = NA_STRING;

template<>
const Vector<REALSXP> unlist<REALSXP,decltype(NA_REAL)>::NA_value = NA_REAL;

// [[Rcpp::export(name="read.opj")]]
List read_opj(const std::string & file) {
	OriginFile opj(file);

	if (!opj.parse()) stop("Failed to open and/or parse " + file); // throws

	List ret;

	for (unsigned int i = 0; i < opj.spreadCount(); i++) {
		Origin::SpreadSheet & osp = opj.spread(i);

		List rsp(osp.columns.size());
		CharacterVector names(rsp.size()), comments(rsp.size()), commands(rsp.size());

		for (unsigned int c = 0; c < osp.columns.size(); c++) {
			names[c] = osp.columns[c].name;
			comments[c] = osp.columns[c].comment; // user might want to split by \r\n...
			commands[c] = osp.columns[c].command;
			List col(osp.maxRows);
			for (unsigned int row = 0; row < osp.columns[c].data.size(); row++) {
				Origin::variant & v = osp.columns[c].data[row];
				if (v.type() == Origin::variant::V_DOUBLE)
					col[row] = v.as_double();
				else
					col[row] = v.as_string();
			}
			rsp[c] = Rcpp::Language("unlist", col).eval();
		}

		rsp.attr("names") = names;
		rsp.attr("comments") = comments;
		rsp.attr("commands") = commands;
		ret[osp.name] = rsp;
	}

	// TODO: matrix, excel, graph, note

	// FIXME: "dataset" and "function" are going to be untested
	// because I cannot find them in my copy of Origin

    return ret;
}
