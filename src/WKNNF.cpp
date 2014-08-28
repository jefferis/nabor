#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

RCPP_EXPOSED_CLASS(WKNNF)

class WKNNF {
  public:
  WKNNF(const Eigen::Map<Eigen::MatrixXd> data, bool buildtree=true) : tree(0) {
    data_pts = data.cast<float>();
    data_pts.transposeInPlace();
    if(buildtree) build_tree();
  }
    
  ~WKNNF() {
    delete_tree();
  }
  
  void build_tree() {
    if(tree==0) {
      tree = NNSearchF::createKDTreeLinearHeap(data_pts);
    }
  }

  void delete_tree() {
    if(tree!=0) {
      delete tree;
      tree=0;
    }
  }

  List query(const Eigen::Map<Eigen::MatrixXd> query, const int k, const double eps=0.0) {

    MatrixXf queryf = query.cast<float>();
    queryf.transposeInPlace();

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
    
    return Rcpp::List::create(Rcpp::Named("indices")=indices,
      Rcpp::Named("dists")=dists);
  }
  
  private:
  Eigen::MatrixXf data_pts;
  NNSearchF* tree;
};

RCPP_MODULE(class_WKNNF) {
  class_<WKNNF>( "WKNNF" )
  .constructor<Eigen::Map<Eigen::MatrixXd> >()
  .constructor<Eigen::Map<Eigen::MatrixXd>,bool>()
  .method( "query", &WKNNF::query )
  ;
}
