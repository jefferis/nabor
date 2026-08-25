# Wrapper for libnabo K Nearest Neighbours C++ library

R package **nabor** wraps the
[libnabo](https://github.com/norlab-ulaval/libnabo) library, a fast K
Nearest Neighbour library for low-dimensional spaces written in
templated C++. The package provides both a standalone function (see
[`knn`](https://jefferis.github.io/nabor/reference/knn.md) for basic
queries along an option to produce an object containing the k-d tree
search (see
[`WKNN`](https://jefferis.github.io/nabor/reference/WKNN-class.md))
structure when making multiple queries against the same target points.

## Details

libnabo uses the same approach as the ANN library (wrapped in R package
`RANN`) but is generally faster and with a smaller memory footprint.
Furthermore since it is templated on the underlying scalar type for
coordinates (among other things), we have provided both float and double
coordinate implementations of the classes wrapping the search tree
structures. See the github repository and Elsenberg et al paper below
for details.

## References

Elseberg J, Magnenat S, Siegwart R and Nuechter A (2012). "Comparison of
nearest-neighbor-search strategies and implementations for efficient
shape registration." \_Journal of Software Engineering for Robotics
(JOSER)\_, \*3\*(1), pp. 2-12. ISSN 2035-3928.

## See also

[`knn`](https://jefferis.github.io/nabor/reference/knn.md),
[`WKNN`](https://jefferis.github.io/nabor/reference/WKNN-class.md)
