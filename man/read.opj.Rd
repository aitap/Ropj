% vi:et:ts=2
\name{read.opj}
\alias{read.opj}
\docType{package}
\title{Parse Origin(R) project file into a list of objects}
\description{
  This function parses an OPJ file into a list of objects it consists
  of. For now, only spreadsheets are returned as \code{\link{data.frame}}s.
}
\usage{
  read.opj(file)
}
\arguments{
  \item{file}{
    Path to the OPJ file to parse.  Only file paths are supported,
    not R connections.
  }
}
\value{
  A named \code{\link{list}} containing objects stored in the file.

  \itemize{
    \item Spreadsheets are presented as \code{\link{data.frame}}s,
    each having additional \code{\link{attributes}}:
    \itemize{
      \item \code{comments} contains the fields Long name, Units,
      and Comment, joined by \code{\\r\\n}, if present.  Due to a
      possible bug in \code{liborigin}, these values are sometimes
      followed by \code{@} and some text that wasn't present in
      the original document.
      \item \code{commands} contains the formula that was used to
      create the values of the column (e.g. \code{col(A) * 2 + 1}).
    }
    \item Multi-sheet spreadsheets are stored as named lists of
    \code{\link{data.frame}}s described above.
    \item Matrices are presented as \code{\link{list}}s of \code{\link{matrix}}
    objects containing numeric data. \code{\link{dimnames}} are also assigned.
    The list also has attributes:
    \itemize{
      \item \code{commands} contains the formula that was used to
      compute the values in the matrix.
    }
    \item Notes are stored as plain strings.
  }

  The list also has attributes set:
  \itemize{
    \item \code{\link{comment}} contains the long names of the objects stored
    in the file.
  }
}
\examples{
  x <- read.opj(system.file('test.opj', package = 'Ropj'))
  head(x$Book1)
  attr(x$Book1, 'comments')
  head(x$Book2)
  attr(x$Book2, 'commands')
  x$MBook1$MSheet1[1:6,1:4]
  x$Notes
}
\keyword{IO}
\keyword{file}
