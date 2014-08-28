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

  private:
  Eigen::MatrixXf data_pts;
  NNSearchF* tree;
};

RCPP_MODULE(class_WKNNF) {
  class_<WKNNF>( "WKNNF" )
  .constructor<Eigen::Map<Eigen::MatrixXd> >()
  .constructor<Eigen::Map<Eigen::MatrixXd>,bool>()
  ;
}
