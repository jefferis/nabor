context("WKNN")

test_that("constructing WKNN and getting points", {
  data(kcpoints)
  expect_is(w1<-WKNNF(kcpoints[[1]]),"WKNNF")
  expect_equivalent(w1$getPoints(), kcpoints[[1]])
  w1_notree=WKNNF(kcpoints[[1]], FALSE)
})

library(RANN)

test_that("Basic queries", {
  p1=kcpoints[[1]]
  w1<-WKNNF(p1)
  p2=kcpoints[[2]]
  expect_equal(w1$query(p2, 1, 0), nn2(p1, p2, k=1), tolerance=1e-6)
  w1.notree<-WKNNF(p1,FALSE)
  expect_equal(w1.notree$query(p2, 1, 0), w1$query(p2, 1, 0))
})

test_that("Queries using WKNNF objects", {
  p1=kcpoints[[1]]
  w1=WKNNF(p1)
  p2=kcpoints[[2]]
  w2=WKNNF(p2)
  expect_equal(w1$queryWKNNF(w2$.CppObject, 1, 0), nn2(p1, p2, k=1), tolerance=1e-6)
})

