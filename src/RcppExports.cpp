// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// read_opj
List read_opj(const std::string& file, const char * encoding, bool tree);
RcppExport SEXP _Ropj_read_opj(SEXP fileSEXP, SEXP encodingSEXP, SEXP treeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type file(fileSEXP);
    Rcpp::traits::input_parameter< const char * >::type encoding(encodingSEXP);
    Rcpp::traits::input_parameter< bool >::type tree(treeSEXP);
    rcpp_result_gen = Rcpp::wrap(read_opj(file, encoding, tree));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_Ropj_read_opj", (DL_FUNC) &_Ropj_read_opj, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_Ropj(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
