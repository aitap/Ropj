\name{read.opj}
\alias{read.opj}
\docType{package}
\title{Parse OPJ file into a list of objects}
\description{
    This function parses an Origin(R) OPJ file into a list of objects
    it consists of.  For now, only spreadsheets are returned as numeric
    matrices.
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
    A \code{\link{list}} containing named objects stored in the file.

    \itemize{
        \item Spreadsheets are presented as \code{\link{data.frame}}s,
        each column having additional \code{\link{attributes}}:
        \itemize{
            \item \code{comments} contains the fields Long name, Units,
            and Comment, joined by \code{\\r\\n}, if present.  Due to a
            possible bug in \code{liborigin}, these values are sometimes
            followed by \code{@} and some text that wasn't present in
            the original document.
            \item \code{commands} contains the formula that was used to
            create the values of the column (e.g. \code{col(A) * 2 + 1}).
        }
    }
}
\examples{
    \dontrun{
        read.opj('data.opj')
    }
}
\keyword{IO}
\keyword{file}
