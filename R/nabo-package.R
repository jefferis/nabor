#' Wrapper libnabo Nearest Neighbours C++ library
#'
#' @name nabo-package
#' @aliases nabo
#' @useDynLib nabo
#' @import Rcpp RcppEigen methods
NULL

#' List of 3 matrices containing 3D points from Drosophila neurons
#'
#' This R list contains 3 skeletonized \emph{Drosophila} Kenyon cells as
#' \code{dotprops} objects. Original data is due to Chiang et al. 2011, who have
#' generously shared their raw data at \url{http://flycircuit.tw}. Image
#' registration and further processing was carried out by Greg Jefferis.
#' @name kcpoints
#' @docType data
#' @references [1] Chiang A.S., Lin C.Y., Chuang C.C., Chang H.M., Hsieh C.H.,
#'   Yeh C.W., Shih C.T., Wu J.J., Wang G.T., Chen Y.C., Wu C.C., Chen G.Y.,
#'   Ching Y.T., Lee P.C., Lin C.Y., Lin H.H., Wu C.C., Hsu H.W., Huang Y.A.,
#'   Chen J.Y., et al. (2011). Three-dimensional reconstruction of brain-wide
#'   wiring networks in Drosophila at single-cell resolution. Curr Biol 21 (1),
#'   1--11.
NULL
