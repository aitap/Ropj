\name{NEWS}
\title{News for package \pkg{Ropj}}
\section{Changes in Ropj version 0.3 (2020-03-14)}{
  \itemize{
    \item Use the \sQuote{comment} attribute (as in \code{comment()}
    function) for spreadsheet imports in addition to \sQuote{comments}
    attribute (as before)

    \item Pass the \code{...} arguments from \code{read.opj} to
    \code{as.data.frame}, making it possible to set
    \code{stringsAsFactors} and other parameters

    \item New \code{tree} parameter to return the objects in a tree structure
    instead of a flat list
  }
}
\section{Changes in Ropj version 0.2-2 (2019-03-14)}{
  \itemize{
    \item Prevent truncation of long tables when importing large files

    \item Fix a memory leak possibly resulting from misuse of
    \code{tree.hh} library

    \item Decode strings using \code{Riconv} interface instead of
    \code{Rcpp::Function} call, making it much faster
  }
}
\section{Changes in Ropj version 0.2-1 (2019-03-01)}{
  \itemize{
    \item Added support for multi-spreadsheets, matrices and notes

    \item Correctly decode byte strings read from the file

    \item Fix undefined variable access found by UBSan
  }
}
