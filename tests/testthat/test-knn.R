context("knn")

test_that('knn gives appropriate result structure',{
  d=matrix(rnorm(100*3), nrow=3)
  expect_is(r<-knn(d, d, k=5), 'list')
  expect_is(r$indices, 'matrix')
  expect_equal(dim(r$dists), c(5,100))
  expect_is(r$dists, 'matrix')
})

knn_by_knn1<-function(d, q, k){
  pl=apply(q,2,function(x) knn1(d, x, k=5))
  list(indices=do.call(cbind,lapply(pl,"[[","indices")),
       dists=do.call(cbind,lapply(pl,"[[","dists")))
}

test_that('knn and knn1 agree',{
  set.seed(42)
  d=matrix(rnorm(100*3), nrow=3)
  q=matrix(rnorm(100*3), nrow=3)
  
  expect_equal(knn(d, q, k=5), knn_by_knn1(d, q, k=5))
  
  # but this works for a different number of data columns ...
  d=matrix(rnorm(1000*3), nrow=3)
  expect_equal(knn(d, q, k=5), knn_by_knn1(d, q, k=5))
})

test_that('knn1 and knn_brute agree',{
  set.seed(42)
  d=matrix(rnorm(100*3), nrow=3)
  q=matrix(rnorm(100*3), nrow=3)
  expect_equal(knn_by_knn1(d, q, k=5), knn_brute(d, q, k=5))
  
  # maybe this works for a different number of data columns ...
  d=matrix(rnorm(10*3), nrow=3)
  expect_equal(knn_by_knn1(d, q, k=5), knn_brute(d, q, k=5))
})

test_that('knn and knn_brute agree',{
  set.seed(42)
  d=matrix(rnorm(100*3), nrow=3)
  q=matrix(rnorm(100*3), nrow=3)
  expect_equal(knn(d, q, k=5), knn_brute(d, q, k=5))
  
  # but this works for a different number of data columns ...
  d=matrix(rnorm(10*3), nrow=3)
  expect_equal(knn(d, q, k=5), knn_brute(d, q, k=5))
})


library(RANN)
test_that('knn and RANN:nn2 agree',{
  set.seed(42)
  d=matrix(rnorm(100*3), nrow=3)
  q=matrix(rnorm(100*3), nrow=3)
  expect_is(r1<-knn(d, q, k=5), 'list')
  expect_is(r2<-nn2(t(d), t(q), k=5), 'list')
  expect_equal(r1$indices, t(r2$nn.idx))
  expect_equal(r1$dists, t(r2$nn.dists))
})

test_that('knn1 and RANN:nn2 agree',{
  set.seed(42)
  d=matrix(rnorm(100*3), nrow=3)
  q=matrix(rnorm(100*3), nrow=3)
  bl=apply(q,2,function(x) knn1(d, x, k=5))
  r1=list(indices=do.call(cbind,lapply(bl,"[[","indices")),
           dists=do.call(cbind,lapply(bl,"[[","dists")))

  expect_is(r2<-nn2(t(d), t(q), k=5), 'list')
  expect_equal(r1$indices, t(r2$nn.idx))
  expect_equal(r1$dists, t(r2$nn.dists))
})
