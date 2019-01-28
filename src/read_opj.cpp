#include <string>

#include <Rcpp.h>
using namespace Rcpp;

#include "OriginFile.h"

// [[Rcpp::export(name="read.opj")]]
List read_opj(const std::string & file) {
	OriginFile opj(file);

	if (!opj.parse()) stop("Failed to parse " + file); // throws

	List ret;

	// only spreadsheets for now
	for (unsigned int i = 0; i < opj.spreadCount(); i++) {
		Origin::SpreadSheet & osp = opj.spread(i);

		NumericMatrix rsp(osp.maxRows, osp.columns.size());
		rsp.fill(NAN);

		CharacterVector names(osp.columns.size());

		for (unsigned int col = 0; col < osp.columns.size(); col++) {
			names[col] = osp.columns[col].comment; // what's that with @ characters in there?
			for (unsigned int row = 0; row < osp.columns[col].data.size(); row++) {
				Origin::variant v(osp.columns[col].data[row]);
				if (v.type() == Origin::variant::V_DOUBLE)
					rsp(row,col) = v.as_double();
			}
		}

		colnames(rsp) = names;
		ret[osp.name] = rsp;
	}

	// TODO: dataset, spread, matrix, excel, function, graph, note

    return ret;
}
