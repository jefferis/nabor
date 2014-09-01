#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"
#include "WKNNF.h"

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

RCPP_EXPOSED_CLASS(WKNNF)

WKNNF::WKNNF(const Eigen::Map<Eigen::MatrixXd> data, bool buildtree) : tree(0) {
  data_pts = data.cast<float>();
  data_pts.transposeInPlace();
  if(buildtree) build_tree();
}

void WKNNF::build_tree(NNSearchF::SearchType treetype) {
  if(tree==0) {
    tree = NNSearchF::create(data_pts, data_pts.rows(), treetype);
  }
}

void WKNNF::delete_tree() {
  if(tree!=0) {
    delete tree;
    tree=0;
  }
}

List WKNNF::query(const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps) {
  
  MatrixXf queryf = query.cast<float>();
  queryf.transposeInPlace();
  return queryF(queryf, k, eps);
}

List WKNNF::queryWKNNF(const WKNNF& query, const int k, const double eps) {
  
  return queryF(query.data_pts, k, eps);
}

List WKNNF::queryF(const Eigen::MatrixXf& queryf, const int k, const double eps) {
  
  MatrixXi indices(k, queryf.cols());
  MatrixXf dists2(k, queryf.cols());
  
  // build tree if required
  build_tree();
  tree->knn(queryf, indices, dists2, k, eps, NNSearchF::SORT_RESULTS | NNSearchF::ALLOW_SELF_MATCH);
  
  // transpose and 1-index for R
  indices.transposeInPlace();
  indices.array()+=1;
  
  // transpose and unsquare distances for R
  dists2.transposeInPlace();
  MatrixXd dists = dists2.cwiseSqrt().cast<double>();
  
  return Rcpp::List::create(Rcpp::Named("nn.idx")=indices,
  Rcpp::Named("nn.dists")=dists);
}

Eigen::MatrixXd WKNNF::getPoints() {
  // transpose for R
  MatrixXd points = data_pts.transpose().cast<double>();
  return points;
}

RCPP_MODULE(class_WKNNF) {
  class_<WKNNF>( "WKNNF" )
  .constructor<Eigen::Map<Eigen::MatrixXd> >()
  .constructor<Eigen::Map<Eigen::MatrixXd>,bool>()
  .method( "query", &WKNNF::query )
  .method( "queryWKNNF", &WKNNF::queryWKNNF )
  .method( "getPoints", &WKNNF::getPoints )
  ;
}
