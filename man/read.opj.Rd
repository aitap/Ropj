\name{read.opj}
\alias{read.opj}
\docType{package}
\title{Parse OPJ file into a list of objects}
\description{
	This function parses an Origin(R) OPJ file into a list of objects it consists
	of. For now, only spreadsheets are returned as numeric matrices.
}
\usage{
read.opj(file)
}
\arguments{
	\item{file}{Path to the OPJ file to parse. Only file paths are supported, not R connections.}
}
\examples{
	\dontrun{
		read.opj('data.opj')
	}
}
\keyword{IO}
\keyword{file}
