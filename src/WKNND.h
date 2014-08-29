#ifndef WKNND_H
#define WKNND_H

#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

class WKNND {
  public:
  WKNND(const Eigen::Map<Eigen::MatrixXd> data, bool buildtree=true);
  
  ~WKNND() { delete_tree(); }
  
  void build_tree(NNSearchD::SearchType treetype=NNSearchD::KDTREE_LINEAR_HEAP);

  void delete_tree();

  List query(const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps=0.0);
  
  List queryWKNND(const WKNND& query, const int k, const double eps=0.0);
  
  List queryD(const Eigen::MatrixXd& queryd, const int k, const double eps=0.0);
  
  Eigen::MatrixXd getPoints();
  
  private:
  Eigen::MatrixXd data_pts;
  NNSearchD* tree;
};
#endif
