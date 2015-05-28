## Test environments
* local OS X install, R 3.2.0
* ubuntu 12.04 (on travis-ci), R 3.2.0
* winbuilder (devel and release)

## R CMD check results
There were no ERRORs or WARNINGs on any platform.

There was 1 NOTE on win-builder release, relating to two issues:

http://win-builder.r-project.org/J3C38xF8CKYt/00check.log

1. Possibly mis-spelled words in DESCRIPTION:
  knn (11:40)
  nn (12:45)

These seem acceptable to me.

2. The Title field should be in title case, current version then in title case:
'Wraps 'libnabo', a Fast K Nearest Neighbour Library for Low Dimensions'
'Wraps 'Libnabo', a Fast K Nearest Neighbour Library for Low Dimensions'

This seems to be a false positive where the comma after the closing single quote
of 'libnabo', confuses tools::toTitleCase. Compare:

```
tools::toTitleCase("'libnabo'")
tools::toTitleCase("'libnabo',")
```

## Downstream dependencies
I have also run R CMD check on downstream dependencies of nat. All packages 
passed.
