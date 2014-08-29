#' A wrapper class for k-NN search using float (4 byte) data points
#' 
#' This expects and returns doubles but uses floats internally
#' @name WKNNF
#' @exportClass WKNNF
#' @export WKNNF
WKNNF <- setRcppClass("WKNNF")

#' A wrapper class for k-NN search using double (8 byte) data points
#' 
#' this uses the same data type as R both internally and as arguments
#' @name WKNND
#' @exportClass WKNND
#' @export WKNND
WKNND <- setRcppClass("WKNND")
