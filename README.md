# nabor
[![Build Status](https://travis-ci.org/jefferis/nabor.svg)](https://travis-ci.org/jefferis/nabor) 

R package **nabor** wraps [libnabo](https://github.com/ethz-asl/libnabo), 
a fast K Nearest Neighbour library for low-dimensional spaces implemented in templated C++.
In comparison with the widely used [ANN](http://www.cs.umd.edu/~mount/ANN) library (wrapped by the
[RANN](http://cran.r-project.org/web/packages/RANN/index.html) R package), **libnabo** is reported
to be 5% to 20% faster with more compact data structures.

## Quick start
```r
# install (see below for details)
if (!require("devtools")) install.packages("devtools")
devtools::install_github("jefferis/nabor")

# use
library(nabor)

# help
?nabor
?knn

# run examples
example(knn)
example(WKNN)

# run tests
library(testthat)
test_package("nabor")

# cite
citation("nabor")
```

## nabo vs RANN
For R users this package provides a function, `knn`, that is a drop in replacement for
the `nn2` function in the [RANN](http://cran.r-project.org/web/packages/RANN/index.html) 
R package. I have seen speedups of 2-3x fold for queries of interest (a few thousand
points in 3d) when comparing nabor::knn and RANN::nn2. See `?knn` for details.

Furthermore **nabor** provides a mechanism for reusing wrapping a libnabo k-d tree
and associated points for multiple queries. This achieved by using RcppModules to wrap
a C++ class in an R reference class. See `?WKNN` for details.

## Installation
Currently there isn't a released version on [CRAN](http://cran.r-project.org/)
so you must install from source.

### Prerequisites
The **nabor** package is known to compile from source with the standard 
toolchains for R under MacOS X, Windows and Linux.
See http://www.rstudio.com/products/rpackages/devtools/ for details of the
developer toolchains needed for your platform.

### Bleeding Edge
Once you have the prerequisites mentioned aboved you can use the **devtools**
package to install the development version of the package:

```r
if (!require("devtools")) install.packages("devtools")
devtools::install_github("jefferis/nabor")
```
### Dependencies
The **nabor** package includes libnabo and all of its dependencies (boost, via 
package **BH**) and Eigen (via package **RcppEigen**) and therefore does not
depend on any system libraries.

## Acknowlegements
**libnabo** and therefore the **nabor** R package are released under the 
[BSD 3 clause license](http://www.r-project.org/Licenses/BSD_3_clause). If you
make use of **nabor** please cite the original authors:

```
> citation('nabor')

Elseberg J, Magnenat S, Siegwart R and Nüchter A (2012). “Comparison of nearest-neighbor-search
strategies and implementations for efficient shape registration.” _Journal of Software Engineering for
Robotics (JOSER)_, *3*(1), pp. 2-12. ISSN 2035-3928.

A BibTeX entry for LaTeX users is

  @Article{elsebergcomparison,
    title = {Comparison of nearest-neighbor-search strategies and implementations for efficient shape registration},
    author = {J. Elseberg and S. Magnenat and R. Siegwart and A. N{\"u}chter},
    journal = {Journal of Software Engineering for Robotics (JOSER)},
    pages = {2--12},
    volume = {3},
    number = {1},
    year = {2012},
    issn = {2035-3928},
  }

```

nabor also makes use of the tremendous [Rcpp](http://cran.r-project.org/web/packages/Rcpp/index.html)
and [RcppEigen](http://cran.r-project.org/web/packages/RcppEigen/index.html) packages –
kudos to their authors!
