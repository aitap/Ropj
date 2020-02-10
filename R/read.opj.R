.preserve.attributes <- function(f) function(x, ...)
	do.call(structure, c(list(.Data = f(x, ...)), attributes(x)))

.lapply <- .preserve.attributes(lapply)
.as.data.frame <- .preserve.attributes(as.data.frame)

.matrix <- function(x) {
	d <- attr(x, 'dimensions')
	dimnames(x) <- list(
		seq(d[4], d[2], length.out = nrow(x)),
		seq(d[3], d[1], length.out = ncol(x))
	)
	t(x)
}

read.opj <- function(file, encoding = 'latin1', tree = FALSE, ...) .lapply(
	read_opj(file, encoding, tree), function(x) if (is.list(x)) switch(
		attr(x, 'type'),
		spreadsheet = .as.data.frame(x, ...),
		matrix = .lapply(x, .matrix),
		excel = .lapply(x, .as.data.frame, ...),
	) else x
)
