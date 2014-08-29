#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

List knn_generic(Nabo::NNSearchD::SearchType st, const Eigen::Map<Eigen::MatrixXd> data, const Eigen::Map<Eigen::MatrixXd> query, const int k ) {
  
  // transpose to d dims x N points
  MatrixXd datat = data.transpose();
  // transpose to d dims x N points
  MatrixXd queryt = query.transpose();

  // create a kd-tree for data
  // note that we are specifying the dimension and search type
  NNSearchD* nns = NNSearchD::create(datat, data.rows(), st);
  
  // result matrices
  MatrixXi indices(k, queryt.cols());
  MatrixXd dists2(k, queryt.cols());

  nns->knn(queryt, indices, dists2, k, NNSearchD::SORT_RESULTS | NNSearchD::ALLOW_SELF_MATCH);
  
  // transpose and 1-index for R
  indices.transposeInPlace();
  indices.array()+=1;
  
  // transpose and unsquare distances for R
  MatrixXd dists = dists2.cwiseSqrt().transpose();
    
  // cleanup kd-tree
  delete nns;
  
  return Rcpp::List::create(Rcpp::Named("nn.idx")=indices,
                            Rcpp::Named("nn.dists")=dists);
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
  
  return knn_generic(NNSearchD::KDTREE_LINEAR_HEAP, data, query, k);
}

//' @description knn_brute checks all point combinations (for validation only)
//' @export
//' @rdname knn
// [[Rcpp::export]]
List knn_brute(const Eigen::Map<Eigen::MatrixXd> data, const Eigen::Map<Eigen::MatrixXd> query, const int k) {
  return knn_generic(NNSearchD::BRUTE_FORCE, data, query, k);
}
