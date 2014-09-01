#ifndef WKNNF_H
#define WKNNF_H

#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

class WKNNF {
  public:
  WKNNF(const Eigen::Map<Eigen::MatrixXd> data, bool buildtree=true);
  
  ~WKNNF() { delete_tree(); }
  
  void build_tree(NNSearchF::SearchType treetype=NNSearchF::KDTREE_LINEAR_HEAP);

  void delete_tree();

  List query(const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps=0.0);
  
  List queryWKNNF(const WKNNF& query, const int k, const double eps=0.0);
  
  List queryF(const Eigen::MatrixXf& queryf, const int k, const double eps=0.0);
  
  Eigen::MatrixXd getPoints();
  
  private:
  Eigen::MatrixXf data_pts;
  NNSearchF* tree;
};
#endif
