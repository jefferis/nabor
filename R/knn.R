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
#' @examples
#' ## Basic usage
#' # load sample data consisting of list of 3 separate 3d pointets
#' data(kcpoints)
#' # Nearest neighbour in first pointset of all points in second pointset 
#' nn1 <- knn(data=kcpoints[[1]], query=kcpoints[[2]], k=1)
#' str(nn1)
#' # 5 nearest neighbours
#' nn5 <-knn(data=kcpoints[[1]], query=kcpoints[[2]], k=5)
#' str(nn5)
#' # nearest neighbour with 10% error bound
#' nn1.approx <- knn(data=kcpoints[[1]], query=kcpoints[[2]], k=1, eps=0.1)
#' str(nn1.approx)
#' # 5 nearest neighbours, brute force search
#' nn5.b <-knn(data=kcpoints[[1]], query=kcpoints[[2]], k=5, searchtype='brute')
#' stopifnot(all.equal(nn5.b, nn5))
#' # 5 nearest neighbours, brute force search (specified by int)
#' nn5.b2 <-knn(data=kcpoints[[1]], query=kcpoints[[2]], k=5, searchtype=2L)
#' stopifnot(all.equal(nn5.b2, nn5.b))
knn <- function(data, query, k, eps = 0.0, searchtype=1L) {
  if(is.character(searchtype)) {
    if(length(searchtype)!=1) stop("only 1 searchtype permitted!")
    search_choices=c("auto", "brute", "kd_linear_heap", "kd_tree_heap")
    searchtype=pmatch(searchtype, search_choices)
    if(is.na(searchtype)) stop("Invalid search type!")
  } else {
    if(searchtype>4L || searchtype<1L) stop("Unknown search type!")
  }
  
  # Check input points
  if(!is.matrix(data))
    data <- as.matrix(data, rownames.force = FALSE)
  if(!is.matrix(query))
    query <- as.matrix(query, rownames.force = FALSE)

  .Call('nabor_knn_generic', PACKAGE = 'nabor', searchtype, data, query, k, eps)
}
