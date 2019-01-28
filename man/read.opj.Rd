\name{read.opj}
\alias{read.opj}
\docType{package}
\title{
Parse OPJ file into a list of objects
}
\description{
This function parses an Origin(tm) file into a list of objects it consists
of. For now, only tables are returned as data.frames (or matrices? FIXME).
}
\usage{
read.opj(file)
}
\arguments{
	\item{file}{Path to the OPJ file to parse. For now, only file paths are supported, not R connections.}
}
\examples{
\dontrun{
read.opj('data.opj')
}
}
\keyword{IO}
\keyword{file}
