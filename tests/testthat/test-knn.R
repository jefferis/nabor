context("knn")
if(require("RANN")){
test_that('knn and RANN:nn2 agree',{
  set.seed(42)
  d=matrix(rnorm(10000*3), nrow=3)
  q=matrix(rnorm(10000*3), nrow=3)
  expect_equivalent(knn(d, q, k=1), lapply(nn2(t(d), t(q), k=1), t))
})
}
