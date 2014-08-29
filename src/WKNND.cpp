#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"
#include "WKNND.h"

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

RCPP_EXPOSED_CLASS(WKNND)

WKNND::WKNND(const Eigen::Map<Eigen::MatrixXd> data, bool buildtree) : tree(0) {
  data_pts = data.transpose();
  if(buildtree) build_tree();
}

void WKNND::build_tree(NNSearchD::SearchType treetype) {
  if(tree==0) {
    tree = NNSearchD::create(data_pts, data_pts.rows(), treetype);
  }
}

void WKNND::delete_tree() {
  if(tree!=0) {
    delete tree;
    tree=0;
  }
}

List WKNND::query(const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps) {
  MatrixXd queryd = query.transpose();
  return queryD(queryd, k, eps);
}

List WKNND::queryWKNND(const WKNND& query, const int k, const double eps) {
  return queryD(query.data_pts, k, eps);
}

List WKNND::queryD(const Eigen::MatrixXd& queryd, const int k, const double eps) {
  MatrixXi indices(k, queryd.cols());
  MatrixXd dists2(k, queryd.cols());
  
  // build tree if required
  build_tree();
  tree->knn(queryd, indices, dists2, k, eps, NNSearchD::SORT_RESULTS | NNSearchD::ALLOW_SELF_MATCH);
  
  // transpose and 1-index for R
  indices.transposeInPlace();
  indices.array()+=1;
  
  // transpose and unsquare distances for R
  MatrixXd dists = dists2.cwiseSqrt().transpose();
  
  return Rcpp::List::create(Rcpp::Named("nn.idx")=indices,
  Rcpp::Named("nn.dists")=dists);
}

Eigen::MatrixXd WKNND::getPoints() {
  // transpose for R
  MatrixXd points = data_pts.transpose();
  return points;
}


RCPP_MODULE(class_WKNND) {
  class_<WKNND>( "WKNND" )
  .constructor<Eigen::Map<Eigen::MatrixXd> >()
  .constructor<Eigen::Map<Eigen::MatrixXd>,bool>()
  .method( "query", &WKNND::query )
  .method( "queryWKNND", &WKNND::queryWKNND )
  .method( "getPoints", &WKNND::getPoints )
  ;
}
