context("knn")

set.seed(42)
d=matrix(rnorm(100*3), ncol=3)
q=matrix(rnorm(100*3), ncol=3)

test_that('knn gives appropriate result structure',{
  expect_is(r<-knn(d, d, k=5), 'list')
  expect_is(r$nn.idx, 'matrix')
  expect_equal(dim(r$nn.idx), c(nrow(d), 5))
  expect_equal(dim(r$nn.dists), c(nrow(d), 5))
  expect_is(r$nn.dists, 'matrix')
  
  expect_is(r2<-knn(d, q, k=5), 'list')
  expect_equal(dim(r$nn.idx), c(nrow(q), 5))
  expect_equal(dim(r$nn.dists), c(nrow(q), 5))
})

test_that('knn and knn_brute agree',{
  expect_equal(knn(d, q, k=5), knn_brute(d, q, k=5))
})

library(RANN)
test_that('knn and RANN:nn2 agree',{
  expect_equal(knn(d, q, k=5), nn2(data=d, query=q, k=5))
})

test_that('knn_brute and RANN:nn2 agree',{
  expect_equal(knn_brute(d, q, k=5), nn2(data=d, query=q, k=5))
})
