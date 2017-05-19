This update addresses the note on the current CRAN build relating to 
registration of native routines as well as fixing some README URLs.

## Test environments
* local OS X install, R 3.4.0
* ubuntu 12.04 (on travis-ci), R 3.2.0
* winbuilder (devel)

## R CMD check results
There were no ERRORs or WARNINGs on any platform.

There was 1 NOTE on win-builder release, relating to one issue:

https://win-builder.r-project.org/ypZ5XoozA8Pt/00check.log

Possibly mis-spelled words in DESCRIPTION:
  knn (11:40)
  nn (12:45)

These seem acceptable to me.

## Downstream dependencies
I have also run R CMD check on downstream dependencies of nabor. All packages 
passed (although stplanr had an unrelated NOTE).
