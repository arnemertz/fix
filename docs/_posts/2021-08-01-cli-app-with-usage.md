---
layout: post
title:  "CLI app with usage output"
date:   2021-08-01 13:57:05 +0200
---

The first TDD session, and seeing how far we have come in passing the first BDD scenarios. Fix shows usage information, no more "hello world!"

## 2021-08-01
### [add cli application class](https://github.com/arnemertz/fix/commit/d5ddcb40de729d4bdc5b24014b3c989ec0f5c22f)

A few things have happened in this commit: At first, I added the `test/fix_cli` directory and `app_test.cpp` inside it. This already reflects a few decisions:
I usually want to have tests and the actual source to be structured similarly, so there will be a directory `src/fix_cli`.

It will contain a library with the same name that implements the classes concerned with the CLI for Fix. The reason is that classes and code that are in a library can be tested by linking that library into the test executable. Code that is directly compiled into the actual executable is harder to test, if at all.

The `fix_cli` library will contain _only_ the CLI-related classes. Any class that deals with the actual domain of Fix goes into another library. The CLI classes do not belong in the same library as they are only one of several possible means to access the domain.

After setting up the CMake structure for the app test, I wrote the first test case. You'll notice that it largely corresponds to the first two scenarios in the feature file I added in the last commit. Except that it also checks that the `-h` option prints the usage message. Small deviations from the feature definition like this are OK as long as it does not complicate the code too much and there's a good reason (users will probably expect both `--help` and `-h` options to work as everywhere else).

The test wouldn't compile even after including all needed standard library headers because `fix::cli::app` did not exist. So, I added an empty class and went through the routine of setting up the CMake structure for the `fix_cli` library and added it as a dependency to the `fix_cli_tests` executable.

Compilation failed because there was no known conversion from `std::stringstream` to `app`. So add the constructor. I could have been overly dogmatic with the TDD approach and use `std::stringstream` as the argument because that's what the test uses. However, I know I want the class to work with `std::cout` and the `std::stringstream` is only a tool to capture the output, so I used `std::ostream` for the constructor parameter instead.

And yes, there are other ways to achieve this without injecting the stream into the class, e.g. swapping the stream buffer like I did [here](https://github.com/arnemertz/hello_cmake/blob/b13ab878d09e04b50b895a855b4eef938654e65a/testmain.cpp), but the outcome is the same.

Back to making the test green - after adding a constructor (that does nothing at all with its parameter), compilation fails due to the unknown `run` method. I added one, taking a `std::vector<std::string_view>` (because I knew that's what I'd need in the end) and doing nothing with it. That's the spirit of TDD: do the minimal amount of work to make things compile, i.e. a bunch of empty constructors and functions. The function has a `// NOLINT` comment for now, because clang-tidy complains about the unnamed argument (it would complain about an unused one if I named it) and about the fact that `run` could be made static.

Now the test compiles, but it fails miserably (who would've thought) because there's no output. The minimum effort to pass it is to print the usage message into the stream right in the constructor. It looks a bit wrong, we'd expect to have a reference to the stream as member and do the output properly in the run function, maybe after checking the options. But that's not needed to make the tests pass, so I won't do it just yet.


### [integrate the new CLI app in the Fix executable](https://github.com/arnemertz/fix/commit/e21ec4c45b43efaed0d62451e93ababc6f0dd6cb)

Now that we have the app class that outputs usage information, it's time to see how far we are with the BDD tests. The central part of the commit is the integration of the app into the `main` function. That function is as good as done now, except for a small change that we'll see shortly.

With the change to the main function, the fmt library is no longer needed. It may come back later, but if it does, I always can look back in the git history to see how the integration is done, should I forget. It is good style to clean up things that are no longer needed.

The other changes you'll see in this commit are changes regarding behave: I removed an obsolete step definition and fixed some errors in the python code itself. Those errors had shown up earlier already and I should have fixed them right when I wrote them, but I expected the scenarios to fail and therefore did not look closely why they failed.

The last piece of this commit is the tags in the feature file and the script to run the behave tests: I'll mark any feature or scenario that is not fully implemented with `@skip` and mark those I am currently working on as `@wip` (work in progress). Those that are not skipped are implemented and should not fail unless I change something in the functionality they describe. The script runs all tests that are not skipped and all that are work in progress.

The current status of the BDD tests is that "Show usage when called with help option" passes, while "Show usage when called without arguments" fails in the last line - the program always terminates with exit code 0. That will be the next step to fix.

