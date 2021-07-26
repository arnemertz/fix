---
layout: post
title:  "Dev diary 2021-07-25"
date:   2021-07-25 18:16:05 +0200
---
Today's work was mostly preparation for the actual start of the project - or restart, I should say. 

## [add initial project structure](https://github.com/arnemertz/fix/commit/d98d4e901ee5092476ea5df95e0e006e609d1bc1)

I copied a bunch of configuration files from my docker4c_test project, which is in turn based on Jason Turner's [cpp_starter_project](https://github.com/lefticus/cpp_starter_project). I trimmed a few things from the CMake files, e.g. I won't be using GUI stuff for now, and went through clang-format line by line to adapt it to my style. 

I removed all the code and replaced the main program with a simple hello world application. Unit tests are gone, too, all that remains is the catch_main library.

There will be some more setup to be done in the next couple of days, e.g. adding libraries, setting up the behave testing framework, etc. I'll not set those up right now, but when I need them for the first time.

## [install jekyll](https://github.com/arnemertz/fix/commit/b950b058031d5c711e8d8cdc0cebd286f6bb43bd)

The one thing I need right now is Jekyll, as I want to have the dev diary and additional documents served on GitHub pages in addition to publishing them on the blog. I spent way too much time trying to get a local preview of the pages. It seems I have overlooked something in the docs or something changed recently - none of the GitHub pages themes can be found.

I'll leave it as it is for now and open an issue on one of the theme pages as I followed their documentation to the letter. I'll still have to figure out how to structure the GitHub page, so it might take some time until there's more than an empty page.



