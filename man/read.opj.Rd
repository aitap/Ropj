\name{read.opj}
\alias{read.opj}
\docType{package}
\title{Parse Origin(R) project file into a list of objects}
\description{
  This function parses an OPJ file into a list of objects it consists
  of. For now, only spreadsheets are returned as numeric matrices.
}
\usage{
read.opj(file)
}
\arguments{
  \item{file}{Path to the OPJ file to parse. Only file paths are
  supported, not R connections.}
}
\examples{
  x <- read.opj(system.file('test.opj', package = 'Ropj'))
  head(x$Book1)
  attr(x$Book1, 'comments')
  head(x$Book2)
  attr(x$Book2, 'commands')
}
\keyword{IO}
\keyword{file}
