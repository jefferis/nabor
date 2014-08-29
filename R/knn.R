#' Find K nearest neighbours for multiple query points
#' 
#' @description knn uses a k-d tree optimised for k ~< 30 nearest neighbours
#' 
#' @param data Mxd matrix of M target points with dimension d
#' @param query Nxd matrix of N query points with dimension d (nb \code{data} and 
#'   \code{query} must have same dimension)
#' @param k an integer number of nearest neighbours to find
#' @param eps An approximate error bound. The default of 0 implies exact
#'   matching.
#' @return A list with elements \code{nn.idx} (1-indexed indices) and 
#'   \code{nn.dists} (distances), both of which are N x k matrices
#' @export
knn <- function(data, query, k, eps = 0.0) {
    .Call('nabo_knn_cpp', PACKAGE = 'nabo', data, query, k, eps)
}

#' @description knn_brute checks all point combinations (for validation only)
#' @export
#' @rdname knn
knn_brute <- function(data, query, k) {
    .Call('nabo_knn_brute_cpp', PACKAGE = 'nabo', data, query, k)
}

