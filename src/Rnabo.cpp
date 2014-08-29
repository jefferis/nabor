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
  
  // establish search type
  Nabo::NNSearchD::SearchType nabo_st;
  if(st==1L){
    // incoming st==1 implies auto, so choose according to value of k
    nabo_st = k < 30 ? NNSearchD::KDTREE_LINEAR_HEAP : NNSearchD::KDTREE_TREE_HEAP;
  } else {
    // if we receive 2L from R => BRUTE_FORCE etc
    nabo_st = static_cast<Nabo::NNSearchD::SearchType>(st-2L);
  }
  
  // build tree using appropriate search type
  tree.build_tree(nabo_st);
  
  return tree.query(query, k, eps);
}
