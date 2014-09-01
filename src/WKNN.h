#ifndef WKNND_H
#define WKNND_H

#include <Rcpp.h>
#include <RcppEigen.h>
#include "nabo.h"

// [[Rcpp::depends(RcppEigen)]]
using namespace Rcpp;
using namespace Nabo;
using namespace Eigen;

template<typename T>
struct WKNN {
  public:
  WKNN(const Eigen::Map<Eigen::MatrixXd> data, bool buildtree=true);
  
  ~WKNN() { delete_tree(); }
  
  void build_tree(typename NearestNeighbourSearch<T>::SearchType treetype=NearestNeighbourSearch<T>::KDTREE_LINEAR_HEAP);

  void delete_tree();

  List query(const Eigen::Map<Eigen::MatrixXd > query, const int k, const double eps=0.0);
  
  List queryWKNN(const WKNN& query, const int k, const double eps=0.0);
  
  List queryD(const Eigen::Matrix<T, Dynamic, Dynamic>& queryd, const int k, const double eps=0.0);
  
  Eigen::MatrixXd getPoints();
  
  private:
  Eigen::Matrix<T, Dynamic, Dynamic> data_pts;
  NearestNeighbourSearch<T>* tree;
};

//typedef NearestNeighbourSearch<float> NNSearchF;
	//! nearest neighbour search with scalars of type double
typedef WKNN<double> WKNND;

#endif
