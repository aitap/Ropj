#!/bin/sh -ex
R -q -e 'Rcpp::compileAttributes()'
nproc=$(nproc) || nproc=1
export MAKE="make -j$nproc" PKG_CXXFLAGS="${PKG_CXXFLAGS} -Wall -Wextra"
rm -vf Ropj_*.tar.gz
R CMD build .
# pass check [--as-cran] before releasing
if [ $# -eq 0 ]; then set -- INSTALL; fi
R CMD "$@" Ropj_*.tar.gz
