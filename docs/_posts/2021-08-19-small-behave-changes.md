---
layout: post
title:  "Small behave changes"
date:   2021-08-19 07:14:33 +0200
---

A little clean-up work and the last step for the list/create feature file.
<!--more-->

## August 19th

### [implement missing step for current feature](https://github.com/arnemertz/fix/commit/2e8354014a600c92d20b5c843e17a78c6fa89295)

As discussed in the last dev diary entry, I implemented the step definitions needed to run the rest of the scenarios in the current feature file. As it turned out, there was only one step left to implement, and it was a combination of two existing steps.

I also fixed that the step definitions bypassed the `fix_cli` module at one point which I also shortly discussed last time. As of now, all remaining scenarios in the feature file are tagged `@wip`.

If you wonder about the change in the definition of the `behave_wip_tests`: the `-w` option of behave executes tests that are tagged `@wip` and has reduced output, but it also stops at the first error. That was enough until now, but to see the missing step definitions, I wanted to execute all tests with the tag and see all errors.

The new options are relatively close to what `-w` does but behave does not stop on the first error. The `-k` option omits the listing of scenarios that have been skipped due to the tag selection: I would not want the output of a handful of WIP scenarios to be hidden among listings of scenarios that are not interesting.
