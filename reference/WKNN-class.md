# Wrapper classes for k-NN searches enabling repeated queries of the same tree

`WKNNF` and `WKNND` are reference classes that wrap C++ classes of the
same name that include a space-efficient k-d tree along with the target
data points. They have `query` methods with exactly the same interface
as the `knn` function. One important point compared with `knn` - they
must be intialised with floating point data and you are responsible for
this - see [`storage.mode`](https://rdrr.io/r/base/mode.html)) and the
example below.

## Details

`WKNNF` expects and returns matrices in R's standard (double, 8 bytes)
data type but uses floats internally. `WKNND` uses doubles throughout.
When retaining large numbers of points, the `WKNNF` objects will have a
small memory saving, especially if tree building is delayed.

The constructor for WKNN objects includes a logical flag indicating
whether to build the tree immediately (default: `TRUE`) or (when
`FALSE`) to delay building the tree until a query is made (this happens
automatically when required).

## Performance

The use of `WKNN` objects will incur a performance penalty for single
queries of trees with \< ~1000 data points. This is because of the
overhead associated with the R wrapper class. It therefore makes sense
to use `knn` in these circumstances.

If you wish to make repeated queries of the same target data, then using
`WKNN` objects can give significant advantages. If you are going to make
repeated queries with the same set of query points (presumably against
different target data), you can obtain benefits in some cases by
converting the query points into WKNNF objects without building the
trees.

## See also

[`knn`](https://jefferis.github.io/nabor/reference/knn.md)

## Examples

``` r
## Basic usage
# load sample data consisting of list of 3 separate 3d pointets
data(kcpoints)
# build a tree and query it with two different sets of points
w1 <- WKNNF(kcpoints[[1]])
w1q2 <- w1$query(kcpoints[[2]], k=5, eps=0, radius=0)
str(w1q2)
#> List of 2
#>  $ nn.idx  : int [1:297, 1:5] 42 42 42 42 42 42 9 9 9 9 ...
#>  $ nn.dists: num [1:297, 1:5] 16.3 10.9 16.2 12.1 10.7 ...
w1q3 <- w1$query(kcpoints[[3]], k=5, eps=0, radius=0)
# note that there will be small difference between WKNNF and knn due to loss 
# of precision in the double to float conversion when a WKNNF tree is 
# built and queried.
stopifnot(all.equal(
 knn(data=kcpoints[[1]], query=kcpoints[[2]], k=5, eps=0, radius=0),
 w1q2, tolerance=1e-6))
 
## storage mode: must be double
m=matrix(1:24, ncol=3)
storage.mode(m)
#> [1] "integer"
# this will generate an error unless we change to a double
w=tools::assertCondition(WKNND(m), "error")
storage.mode(m)="double"
w=WKNND(matrix(m, ncol=3))

## construct wrapper objects but delay tree construction
w1 <- WKNNF(kcpoints[[1]], FALSE)
# query triggers tree construction
w1q2 <- w1$query(kcpoints[[2]], k=5, eps=0, radius=0)
str(w1q2)
#> List of 2
#>  $ nn.idx  : int [1:297, 1:5] 42 42 42 42 42 42 9 9 9 9 ...
#>  $ nn.dists: num [1:297, 1:5] 16.3 10.9 16.2 12.1 10.7 ...

## queries using wrapper objects
wkcpoints <-lapply(kcpoints, WKNNF, FALSE)
# query all 3 point sets against first
# this will trigger tree construction only for pointset 1
qall <- lapply(wkcpoints, 
  function(x) wkcpoints[[1]]$queryWKNN(x$.CppObject, k=5, eps=0, radius=0))
str(qall)
#> List of 3
#>  $ FruMARCM-M001205_seg002:List of 2
#>   ..$ nn.idx  : int [1:284, 1:5] 1 2 3 4 5 6 7 8 9 10 ...
#>   ..$ nn.dists: num [1:284, 1:5] 0 0 0 0 0 0 0 0 0 0 ...
#>  $ GadMARCM-F000122_seg001:List of 2
#>   ..$ nn.idx  : int [1:297, 1:5] 42 42 42 42 42 42 9 9 9 9 ...
#>   ..$ nn.dists: num [1:297, 1:5] 16.3 10.9 16.2 12.1 10.7 ...
#>  $ GadMARCM-F000050_seg001:List of 2
#>   ..$ nn.idx  : int [1:374, 1:5] 16 16 88 16 16 16 16 16 16 16 ...
#>   ..$ nn.dists: num [1:374, 1:5] 14.43 15.13 8.74 11.25 11.69 ...
```
