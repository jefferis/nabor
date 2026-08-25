# Find K nearest neighbours for multiple query points

Find K nearest neighbours for multiple query points

## Usage

``` r
knn(data, query = data, k, eps = 0, searchtype = 1L, radius = 0)
```

## Arguments

- data:

  Mxd matrix of M target points with dimension d

- query:

  Nxd matrix of N query points with dimension d (nb `data` and `query`
  must have same dimension). If missing defaults to `data` i.e. a
  self-query.

- k:

  an integer number of nearest neighbours to find

- eps:

  An approximate error bound. The default of 0 implies exact matching.

- searchtype:

  A character vector or integer indicating the search type. The default
  value of `1L` is equivalent to "auto". See details.

- radius:

  Maximum radius search bound. The default of 0 implies no radius bound.

## Value

A list with elements `nn.idx` (1-indexed indices) and `nn.dists`
(distances), both of which are N x k matrices. See details for the
results obtained with1 invalid inputs.

## Details

If `searchtype="auto"`, the default, knn uses a k-d tree with a linear
heap when `k < 30` nearest neighbours are requested (equivalent to
`searchtype="kd_linear_heap"`), a k-d tree with a tree heap otherwise
(equivalent to `searchtype="kd_tree_heap"`). `searchtype="brute"` checks
all point combinations and is intended for validation only.

Integer values of searchtype should be the 1-indexed position in the
vector `c("auto", "brute", "kd_linear_heap", "kd_tree_heap")`, i.e. a
value between 1L and 4L.

The underlying [libnabo](https://github.com/norlab-ulaval/libnabo) does
not have a signalling value to identify indices for invalid query points
(e.g. those containing an `NA`). In this situation, the index returned
by libnabo will be 0 and `knn` will therefore return an index of 1.
However the distance will be `Inf` signalling a failure to find a
nearest neighbour.

When radius\>0.0 and no point is found within the search bound, the
index returned will be 0 but the reported distance will be Inf (in
contrast RANN::nn2 returns 1.340781e+154).

## Examples

``` r
## Basic usage
# load sample data consisting of list of 3 separate 3d pointets
data(kcpoints)

# Nearest neighbour in first pointset of all points in second pointset 
nn1 <- knn(data=kcpoints[[1]], query=kcpoints[[2]], k=1)
str(nn1)
#> List of 2
#>  $ nn.idx  : int [1:297, 1] 42 42 42 42 42 42 9 9 9 9 ...
#>  $ nn.dists: num [1:297, 1] 16.3 10.9 16.2 12.1 10.7 ...

# 5 nearest neighbours
nn5 <-knn(data=kcpoints[[1]], query=kcpoints[[2]], k=5)
str(nn5)
#> List of 2
#>  $ nn.idx  : int [1:297, 1:5] 42 42 42 42 42 42 9 9 9 9 ...
#>  $ nn.dists: num [1:297, 1:5] 16.3 10.9 16.2 12.1 10.7 ...

# Self match within first pointset, all distances will be 0
nnself1 <- knn(data=kcpoints[[1]], k=1)
str(nnself1)
#> List of 2
#>  $ nn.idx  : int [1:284, 1] 1 2 3 4 5 6 7 8 9 10 ...
#>  $ nn.dists: num [1:284, 1] 0 0 0 0 0 0 0 0 0 0 ...

# neighbour 2 will be the nearest point 
nnself2 <- knn(data=kcpoints[[1]], k=2)

## Advanced usage
# nearest neighbour with radius bound
nn1.rad <- knn(data=kcpoints[[1]], query=kcpoints[[2]], k=1, radius=5)
str(nn1.rad)
#> List of 2
#>  $ nn.idx  : int [1:297, 1] 0 0 0 0 0 0 0 0 0 0 ...
#>  $ nn.dists: num [1:297, 1] Inf Inf Inf Inf Inf ...

# approximate nearest neighbour with 10% error bound
nn1.approx <- knn(data=kcpoints[[1]], query=kcpoints[[2]], k=1, eps=0.1)
str(nn1.approx)
#> List of 2
#>  $ nn.idx  : int [1:297, 1] 42 42 42 42 42 42 9 9 9 9 ...
#>  $ nn.dists: num [1:297, 1] 16.3 10.9 16.2 12.1 10.7 ...

# 5 nearest neighbours, brute force search
nn5.b <-knn(data=kcpoints[[1]], query=kcpoints[[2]], k=5, searchtype='brute')
stopifnot(all.equal(nn5.b, nn5))

# 5 nearest neighbours, brute force search (specified by int)
nn5.b2 <-knn(data=kcpoints[[1]], query=kcpoints[[2]], k=5, searchtype=2L)
stopifnot(all.equal(nn5.b2, nn5.b))
```
