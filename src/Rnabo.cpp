#include <Rcpp.h>
#include <RcppEigen.h>
#include <nabo/nabo.h>

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

//' Find K nearest neighbours for a single query point
//' 
//' @details note that libnabo returns squared distances by default, but we 
//'   unsquare them.
//' @param M dxM matrix of M target points with dimension d
//' @param q a length d vector defining a query point
//' @param k an integer number of nearest neighbours to find
//' @param eps An approximate error bound. The default of 0 implies exact
//'   matching.
//' @return A list with elements \code{indices} (1-indexed indices) and 
//'   \code{dists} (distances)
//' @export
// [[Rcpp::export]]
List knn1(const Eigen::Map<Eigen::MatrixXd> M, const Eigen::Map<Eigen::VectorXd> q, const int k, const double eps=0.0) {
  
  // create a kd-tree for M, note that M must stay valid during the lifetime of the kd-tree
  NNSearchD* nns = NNSearchD::createKDTreeLinearHeap(M);
  
  VectorXi indices(k);
  VectorXd dists2(k);
  nns->knn(q, indices, dists2, k, eps, NNSearchD::ALLOW_SELF_MATCH);
  
  // 1-index for R
  indices = (indices.array()+1).matrix();
  // unsquare distances
  dists2 = (dists2.array().sqrt()).matrix();

  // cleanup kd-tree
  delete nns;
  
  return Rcpp::List::create(Rcpp::Named("indices")=indices,
                            Rcpp::Named("dists")=dists2);
}
//' Find K nearest neighbours for multiple query points
//' @param q dxN matrix of N query points with dimension d (nb \code{M} and 
//'   \code{q} must have same dimension)
//' @inheritParams knn1
//' @return A list with elements \code{indices} (1-indexed indices) and 
//'   \code{dists} (distances), both of which are k x N matrices
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
                            Rcpp::Named("dists")=dists2);
}

// [[Rcpp::export]]
List knn_brute(const Eigen::Map<Eigen::MatrixXd> M, const Eigen::Map<Eigen::MatrixXd> q, const int k) {
  
  // create a kd-tree for M, note that M must stay valid during the lifetime of the kd-tree
  NNSearchD* nns = NNSearchD::createBruteForce(M);
  
  MatrixXi indices;
  MatrixXd dists2;
  indices.resize(k, q.cols());
  dists2.resize(k, q.cols());

  nns->knn(q, indices, dists2, k, NNSearchD::SORT_RESULTS | NNSearchD::ALLOW_SELF_MATCH);
  
  // 1-index for R
  indices = (indices.array()+1).matrix();
  // unsquare distances
  dists2 = (dists2.array().sqrt()).matrix();
  // cleanup kd-tree
  delete nns;
  
  return Rcpp::List::create(Rcpp::Named("indices")=indices,
                            Rcpp::Named("dists")=dists2);
}
