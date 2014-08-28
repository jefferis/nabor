#include <Rcpp.h>
#include <RcppEigen.h>
#include <nabo/nabo.h>

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

//' @export
// [[Rcpp::export]]
List knn1(const Eigen::Map<Eigen::MatrixXd> M, const Eigen::Map<Eigen::VectorXd> q, const int k) {
  
  // create a kd-tree for M, note that M must stay valid during the lifetime of the kd-tree
  NNSearchD* nns = NNSearchD::createKDTreeLinearHeap(M);
  
  VectorXi indices(k);
  VectorXd dists2(k);
  nns->knn(q, indices, dists2, k);
  
  // cleanup kd-tree
  delete nns;
  
  return Rcpp::List::create(Rcpp::Named("indices")=indices,
                            Rcpp::Named("dists2")=dists2);
}

//' @export
// [[Rcpp::export]]
List knn(const Eigen::Map<Eigen::MatrixXd> M, const Eigen::Map<Eigen::MatrixXd> q, const int k, const double eps=0.0) {
  
  // create a kd-tree for M, note that M must stay valid during the lifetime of the kd-tree
  NNSearchD* nns = NNSearchD::createKDTreeLinearHeap(M);
  
  MatrixXi indices;
  MatrixXd dists2;
  indices.resize(k, q.cols());
  dists2.resize(k, q.cols());

  nns->knn(q, indices, dists2, k, eps, NNSearchD::SORT_RESULTS | NNSearchD::ALLOW_SELF_MATCH);
  
  // 1-index for R
  indices = (indices.array()+1).matrix();
  // unsquare distances
  dists2 = (dists2.array().sqrt()).matrix();
  // cleanup kd-tree
  delete nns;
  
  return Rcpp::List::create(Rcpp::Named("indices")=indices,
                            Rcpp::Named("dists2")=dists2);
}
