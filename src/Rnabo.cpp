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

// [[Rcpp::export]]
List knn_cpp(const Eigen::Map<Eigen::MatrixXd> data, const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps=0.0) {
  
  return knn_generic(NNSearchD::KDTREE_LINEAR_HEAP, data, query, k, eps);
}

// [[Rcpp::export]]
List knn_brute_cpp(const Eigen::Map<Eigen::MatrixXd> data, const Eigen::Map<Eigen::MatrixXd> query, const int k) {
  return knn_generic(NNSearchD::BRUTE_FORCE, data, query, k, 0.0);
}
