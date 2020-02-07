% vi:et:ts=2
\name{read.opj}
\alias{read.opj}
\docType{package}
\title{Parse Origin(R) project file into a list of objects}
\description{
  This function parses an OPJ file into a list of objects it consists
  of. Items understood by \code{read.opj} include spreadsheets, matrices,
  and notes.
}
\usage{
  read.opj(file, encoding = 'latin1', ...)
}
\arguments{
  \item{file}{
    Path to the OPJ file to parse.  Only file paths are supported,
    not R connections.
  }
  \item{encoding}{
    Encoding of the strings inside the file being opened. The default of
    \code{'latin1'} is usually safe to use. See \code{\link{iconvlist}()}
    for the full list of encodings supported by your R installation. This
    should correspond to the ANSI code page of Windows installation used
    to produce the file.
  }
  \item{\dots}{
    The rest of the arguments is passed to \code{\link{as.data.frame}}
    when converting spreadsheets, making it possible to set
    \code{stringsAsFactors} and other parameters as needed.
  }
}
\value{
  A named \code{\link{list}} containing objects stored in the file.

  \itemize{
    \item Spreadsheets are presented as \code{\link{data.frame}}s,
    with additional \code{\link{attributes}}:
    \itemize{
      \item \code{\link{comment}} contains the fields Long name, Units,
      and Comment, joined by \code{\\r\\n}, if present.  Due to a
      possible bug in \code{liborigin}, these values are sometimes
      followed by \code{@} and some text that wasn't present in
      the original document. (In versions prior to v0.2-2 it was called
      \code{comments}, which should be still supported until v1.0.)
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
  head(x$Book2, 7)
  comment(x$Book2)
  attr(x$Book2, 'commands')
  with(x$Book1, head(Sheet2 - Sheet1))
  x$MBook1$MSheet1[1:4,1:4]
  x$Note1

  \dontrun{
    # encoding names aren't guaranteed to be supported across all platforms
    x <- read.opj(system.file('test.opj', package = 'Ropj'), 'WINDOWS-1251')
    x$cyrillic
  }
}
\keyword{IO}
\keyword{file}
