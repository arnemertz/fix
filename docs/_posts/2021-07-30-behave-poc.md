---
layout: post
title:  "POC for behave"
date:   2021-07-30 09:00:05 +0200
---

Just to check that behave works as intended before I dive into writing the first actual feature files for Fix.
<!--more-->

## July 30th
### [Add POC for behave](https://github.com/arnemertz/fix/commit/3c95a8b3ecb4b81e7a6eb582ade015086bc81d77)

To test that [behave](https://behave.readthedocs.io/en/stable/) with [pexpect](https://pexpect.readthedocs.io/en/stable/) is suitable for testing Fix in a BDD manner, I wrote this tiny feature and the necessary step definitions. Those 3 lines document the current full functionality of Fix as it is nothing but a hello world example.

The important part here was to see that the executable can be started and its output and return code captured. The path to the executable is hard-coded to the CMake build directory generated by CLion for now. At a later point, there will probably be an install step in CMake and/or a parametrization of the BDD tests with the directory where it can find the executable.

The logic of starting Fix and where it is located will probably be put into a proper class at a later point. As it is now, there is not enough functionality to make that necessary, so refactoring to that direction would be premature at this point. (And I want to get started with the actual project soon)
