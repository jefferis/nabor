#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

#include "WKNND.h"

List knn_generic(Nabo::NNSearchD::SearchType st, const Eigen::Map<Eigen::MatrixXd> data, const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps) {
  
  // create WKNND object but don't build tree
  WKNND tree = WKNND(data, false);
  // build tree using appropriate search type
  tree.build_tree(st);
  
  return tree.query(query, k, eps);
}

//' Find K nearest neighbours for multiple query points
//' 
//' @description knn uses a k-d tree optimised for k ~< 30 nearest neighbours
//' 
//' @param data Mxd matrix of M target points with dimension d
//' @param query Nxd matrix of N query points with dimension d (nb \code{data} and 
//'   \code{query} must have same dimension)
//' @param k an integer number of nearest neighbours to find
//' @param eps An approximate error bound. The default of 0 implies exact
//'   matching.
//' @return A list with elements \code{nn.idx} (1-indexed indices) and 
//'   \code{nn.dists} (distances), both of which are N x k matrices
//' @export
// [[Rcpp::export]]
List knn(const Eigen::Map<Eigen::MatrixXd> data, const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps=0.0) {
  
  return knn_generic(NNSearchD::KDTREE_LINEAR_HEAP, data, query, k, eps);
}

//' @description knn_brute checks all point combinations (for validation only)
//' @export
//' @rdname knn
// [[Rcpp::export]]
List knn_brute(const Eigen::Map<Eigen::MatrixXd> data, const Eigen::Map<Eigen::MatrixXd> query, const int k) {
  return knn_generic(NNSearchD::BRUTE_FORCE, data, query, k, 0.0);
}
