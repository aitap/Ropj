#!/bin/sh -ex
R -q -e 'Rcpp::compileAttributes()'
nproc=$(nproc) || nproc=1
export MAKE="make -j$nproc"
rm -vf Ropj_*.tar.gz
R CMD build .
R CMD check --as-cran Ropj_*.tar.gz
