#include <Rcpp.h>
#include <RcppEigen.h>
#include <nabo/nabo.h>

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

//' @export
// [[Rcpp::export]]
List knn1(Eigen::Map<Eigen::MatrixXd> M, Eigen::Map<Eigen::VectorXd> q, const int k) {
  
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
