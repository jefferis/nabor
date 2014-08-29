#' Find K nearest neighbours for multiple query points
#' 
#' @details If \code{searchtype="auto"}, the default, knn uses a k-d tree with a
#'   linear heap when \code{k < 30} nearest neighbours are requested (equivalent
#'   to \code{searchtype="kd_linear_heap"}), a k-d tree with a tree heap 
#'   otherwise (equivalent to \code{searchtype="kd_tree_heap"}). 
#'   \code{searchtype="brute"} checks all point combinations and is intended for
#'   validation only.
#'   
#'   Integer values of searchtype should be the 1-indexed position in the vector
#'   \code{c("auto", "brute", "kd_linear_heap", "kd_tree_heap")}, i.e. a value
#'   between 1L and 4L.
#'   
#' @param data Mxd matrix of M target points with dimension d
#' @param query Nxd matrix of N query points with dimension d (nb \code{data} 
#'   and \code{query} must have same dimension)
#' @param k an integer number of nearest neighbours to find
#' @param eps An approximate error bound. The default of 0 implies exact 
#'   matching.
#' @param searchtype A character vector or integer indicating the search type. 
#'   The default value of \code{1L} is equivalent to "auto". See details.
#' @return A list with elements \code{nn.idx} (1-indexed indices) and 
#'   \code{nn.dists} (distances), both of which are N x k matrices
#' @export
knn <- function(data, query, k, eps = 0.0, searchtype=1L) {
  if(is.character(searchtype)) {
    if(length(searchtype)!=1) stop("only 1 searchtype permitted!")
    search_choices=c("auto", "brute", "kd_linear_heap", "kd_tree_heap")
    searchtype=pmatch(searchtype, search_choices)
    if(is.na(searchtype)) stop("Invalid search type!")
  } else {
    if(searchtype>4L || searchtype<1L) stop("Unknown search type!")
  }
  .Call('nabo_knn_generic', PACKAGE = 'nabo', searchtype, data, query, k, eps)
}
