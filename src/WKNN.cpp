#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"
#include "WKNN.h"

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

RCPP_EXPOSED_CLASS_NODECL(WKNND)

template <typename T>
  data_pts = data.template cast<T>();
  data_pts = data.transpose();
WKNN<T>::WKNN(const Eigen::Map<Eigen::MatrixXd> data, bool buildtree) : tree(0) {
  if(buildtree) build_tree();
}

template <typename T>
void WKNN<T>::build_tree(typename NearestNeighbourSearch<T>::SearchType treetype) {
  if(tree==0) {
    tree = NearestNeighbourSearch<T>::create(data_pts, data_pts.rows(), treetype);
  }
}

template <typename T>
void WKNN<T>::delete_tree() {
  if(tree!=0) {
    delete tree;
    tree=0;
  }
}

template <typename T>
  return queryD(query.template cast<T>().transpose(), k, eps);
List WKNN<T>::query(const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps) {
}

template <typename T>
List WKNN<T>::queryWKNN(const WKNN& query, const int k, const double eps) {
  return queryD(query.data_pts, k, eps);
}

template <typename T>
List WKNN<T>::queryD(const Eigen::Matrix<T, Dynamic, Dynamic>& queryd, const int k, const double eps) {
  MatrixXi indices(k, queryd.cols());
  Eigen::Matrix<T, Dynamic, Dynamic> dists2(k, queryd.cols());
  
  // build tree if required
  build_tree();
  tree->knn(queryd, indices, dists2, k, eps, NearestNeighbourSearch<T>::SORT_RESULTS | NearestNeighbourSearch<T>::ALLOW_SELF_MATCH);
  
  // transpose and 1-index for R
  indices.transposeInPlace();
  indices.array()+=1;
  
  // transpose and unsquare distances for R
  Eigen::MatrixXd dists = dists2.cwiseSqrt().transpose().template cast<double>();
  
  return Rcpp::List::create(Rcpp::Named("nn.idx")=indices,
  Rcpp::Named("nn.dists")=dists);
}

template <typename T>
Eigen::MatrixXd WKNN<T>::getPoints() {
  // transpose for R
  MatrixXd points = data_pts.transpose().template cast<double>();
  return points;
}

// Explicit template instantiation for linker
template struct WKNN<double>;

RCPP_MODULE(class_WKNND) {
  class_<WKNND>( "WKNND" )
  .constructor<Eigen::Map<Eigen::MatrixXd> >()
  .constructor<Eigen::Map<Eigen::MatrixXd>,bool>()
  .method( "query", &WKNND::query )
  .method( "queryWKNN", &WKNND::queryWKNN )
  .method( "getPoints", &WKNND::getPoints )
  ;
}