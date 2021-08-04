---
layout: post
title:  "Return code for CLI app"
date:   2021-08-02 17:57:05 +0200
---

Finalizing the first two BDD scenarios, Fix now returns a proper exit code.

## 2021-08-02
### [Return exit code from app::run and main](https://github.com/arnemertz/fix/commit/41475f88e7e52391c710719c85759ae2e0612acb)

Yesterday's remaining task was to get the correct exit code from the Fix executable to pass the current WIP scenarios.
This is best achieved by having the `app::run` method return an exit code and forward that as exit code from `main`.

It starts with the unit test again: `app_test` now requires that `app::run` returns the correct exit codes.
To fix the compiler error, `run` first has to return anything comparable to an exit code, and `int` is the obvious choice as that's what `main` returns.

To fix the failing unit tests, we have to check the arguments passed to `run` - as it happens, we can just check whether there actually is an argument to pass the tests.
This looks too simple, even wrong - but the tests are green, so it is sufficient.
More tests are coming up in our feature file that should take care of this problem.

To my surprise, returning the exit code from `main` did not fix the failing scenario:
Behave still told me that the exit code was not the same as the one I expected - but it did not tell me which either value was.

This was the reason for the `assert_equals` function you see in the step definition file.
There are several python testing frameworks out there that provide this kind of functionality, but only one I found has them as free function.
All of them contain way more functionality than I need, so I opted for writing this function by hand for now.

The culprit turned out to be that while the unit tests pass only the arguments to the CLI app, the `main` function passed the name of the program itself as well.
After fixing that, all WIP scenarios are green. 


### [Refactor: move assert_equals into own python module](https://github.com/arnemertz/fix/commit/d4e959fe36fa3c753cf5c9cb3247589fe7c6a2d4)

Besides a few whitespace fixes and the removal of the `@wip` and `@skip` tags from the now-passing scenarios, the commit message already says it all:
The `assert_equals` function does not directly belong to the CLI step definitions, it will most likely be used all over the tests, and there are bound to be more similar functions.
Moving it into its own module is a logical step. Let's move on to the next BDD scenarios.
