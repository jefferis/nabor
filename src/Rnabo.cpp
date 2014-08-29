#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

#include "WKNND.h"

// [[Rcpp::export]]
List knn_generic(int st, const Eigen::Map<Eigen::MatrixXd> data, const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps) {
  
  // create WKNND object but don't build tree
  WKNND tree = WKNND(data, false);
  // build tree using appropriate search type
  tree.build_tree(static_cast<Nabo::NNSearchD::SearchType>(st));
  
  return tree.query(query, k, eps);
}
