#' Find K nearest neighbours for multiple query points
#' 
#' @details If \code{searchtype="auto"}, the default, knn uses a k-d tree with a
#'   linear heap when \code{k < 30} nearest neighbours are requested (equivalent
#'   to \code{searchtype="kd_linear_heap"}), a k-d tree with a tree heap 
#'   otherwise (equivalent to \code{searchtype="kd_tree_heap"}).
#'   \code{searchtype="brute"} checks all point combinations and is intended for
#'   validation only.
#'   
#' @param data Mxd matrix of M target points with dimension d
#' @param query Nxd matrix of N query points with dimension d (nb \code{data} 
#'   and \code{query} must have same dimension)
#' @param k an integer number of nearest neighbours to find
#' @param eps An approximate error bound. The default of 0 implies exact 
#'   matching.
#' @param searchtype A character vector indicating the a search type. See 
#'   details.
#' @return A list with elements \code{nn.idx} (1-indexed indices) and 
#'   \code{nn.dists} (distances), both of which are N x k matrices
#' @export
knn <- function(data, query, k, eps = 0.0, 
                searchtype=c("auto", "kd_linear_heap","kd_tree_heap","brute")) {
  search_choices=c("auto", "kd_linear_heap","kd_tree_heap","brute")
  searchtype=match.arg(searchtype, search_choices)
  
  # There are 3 types of search available via libnabo
  # BRUTE_FORCE = 0, //!< brute force, check distance to every point in the data
  # KDTREE_LINEAR_HEAP, //!< kd-tree with linear heap, good for small k (~up to 30)
  # KDTREE_TREE_HEAP, //!< kd-tree with tree heap, good for large k (~from 30)
  int_search_type = switch(searchtype,
                           auto = ifelse(k<30, 1L, 2L),
                           kd_linear_heap=1L,
                           kd_tree_heap=2L,
                           brute=0L)
  
  .Call('nabo_knn_generic', PACKAGE = 'nabo', int_search_type, data, query, k, eps)
}

#' @description knn_brute checks all point combinations (for validation only)
#' @export
#' @rdname knn
knn_brute <- function(data, query, k) {
  knn(data, query, k, eps=0.0, searchtype='brute')
}
