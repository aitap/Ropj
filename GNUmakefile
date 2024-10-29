R = R

-include Makevars.local

PACKAGE = $(shell $(R)script -e "\
 cat(read.dcf('DESCRIPTION')[,c('Package','Version')], sep = '_'); \
 cat('.tar.gz') \
")

all: $(PACKAGE)

.PHONY: check check-cran install

$(PACKAGE): DESCRIPTION NAMESPACE .Rbuildignore man/* R/* inst/* src/* src/liborigin/* tools/*
	$(R) -q -e 'Rcpp::compileAttributes()'
	$(R) CMD build .

check: $(PACKAGE)
	$(R) CMD check $(PACKAGE)

check-cran: $(PACKAGE)
	$(R) CMD check --timings --as-cran $(PACKAGE)

install: $(PACKAGE)
	$(R) CMD INSTALL $(PACKAGE)
