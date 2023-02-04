library(tools)

for (std in c('CXX17', 'CXX14', 'CXX11', 'CXX1X')) {
	cat('Checking if R knows a', std, 'compiler... ')
	out <- suppressWarnings(Rcmd(paste('config', std)))
	if (out == 0) break
}
if (out != 0) stop("Couldn't find a C++ >= 11 compiler")
if (std == 'CXX1X') std <- 'CXX11'

f <- file(file.path('src', 'Makevars'), 'wb')
writeLines(c(
	paste('CXX_STD =', std),
	'OBJECTS = liborigin.o RcppExports.o read_opj.o',
	'PKG_CPPFLAGS = -I . -I liborigin'
), f)
close(f)
