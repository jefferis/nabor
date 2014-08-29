# nabo
[![Build Status](https://travis-ci.org/jefferis/nabo.svg)](https://travis-ci.org/jefferis/nabo) 

R package **nabo** wraps the [libnabo](https://github.com/ethz-asl/libnabo), 
a fast K Nearest Neighbour library for low-dimensional spaces.

## Quick start
```r
# install (see below for details)
if (!require("devtools")) install.packages("devtools")
devtools::install_github("jefferis/nabo")

# use
library(nabo)

# help
?nabo
?knn

# run examples
example(knn)
example(WKNN)

# run tests
library(testthat)
test_package("nabo")

# cite
citation("nabo")
```
## Installation
Currently there isn't a released version on [CRAN](http://cran.r-project.org/)
so you must install from source.

### Prerequisites
The **nabo** package is known to compile from source with the standard 
toolchains for R under MacOS X, Windows and Linux.
See http://www.rstudio.com/products/rpackages/devtools/ for details of the
developer toolchains needed for your platform.

### Bleeding Edge
Once you have the prerequisites mentioned aboved you can use the **devtools**
package to install the development version of the package:

```r
if (!require("devtools")) install.packages("devtools")
devtools::install_github("jefferis/nabo")
```
### Dependencies
The **nabo** package includes libnabo and all of its dependencies (boost, via 
package **BH**) and Eigen (via package **RcppEigen**) and therefore does not
depend on any system libraries.

## Acknowlegements
**libnabo** and therefore the **nabo** R package are released under the 
[BSD 3 clause license](http://www.r-project.org/Licenses/BSD_3_clause). If you
make use of **nabo** please cite the original authors:

```r
> citation('nabo')

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
