---
layout: post
title:  "Tooling: clang-format and CTest"
date:   2021-08-03 18:05:05 +0200
---

Before I merge the initial features of the CLI app back to the main branch, I want to improve the tooling a bit.

## 2021-08-03
### [tooling: rework and apply clang-format configuration](https://github.com/arnemertz/fix/commit/e6d64ec9fd6ede769ab5b5ecd4015ba6f45a1838)

The clang-format configuration I had come up with during the setup did not seem to work very well.
CLion would not apply the formatting in the way I _thought_ I had configured, and clang-format 12 which I am using in the [docker4c](https://github.com/arnemertz/docker4c) container threw errors while parsing the configuration.

The new configuration seems to do what I'd like, even though I fell victim to a bug in CLion's documentation for the brace wrapping.

### [tooling: add unit tests and behave tests to CTest suite](https://github.com/arnemertz/fix/commit/6f62e7053587059a790d4d9eaf97da4a4491a826)

I had a go at experimenting with CTest which I have not actively used so far.
The result is a test suite that includes the unit tests as well as the Behave tests, the latter separated into stable and "work in progress".

I'm quite pleased with how it turned out, as I now can launch all tests from CLion with one click and get to the location of test failures inside the feature file as well.
![screenshot of behave and ctest integration in CLion]({{site.baseurl}}{% link /assets/img/behave_ctest_integration.png %})