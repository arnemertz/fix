---
layout: post
title:  "Refactoring session"
date:   2021-08-07 18:58:01 +0200
---

Today's session was spent with the refactorings that have accumulated over the last two days.
<!--more-->

## August 7th

### [refactor behave: use semantic exit codes](https://github.com/arnemertz/fix/commit/0d5288e8658f2046b5921e4e1e230eb6dd0c4b81)

This one was rather a warm-up:
- inline the call to `check_exit_code_num` in `check_exit_code_alpha`
- change `check_exit_code_num` to always fail
- find all failing scenarios and replace 0 with `OK`, 1 with `ERROR`
- add `ERROR` to the translations map in `check_exit_code_alpha`

Run tests after every one of these steps - they're fast enough.
Yes, after the first step, the whole thing could have been solved by search & replace.
However, I'm practicing techniques here, and especially in larger codebases, this way is more controlled than letting S&R loose on everything.

### [refactor tests: add split function for CLI app arguments](https://github.com/arnemertz/fix/commit/97bf363952a2ccedd6f1a9fe085fa6c65514f163)

The key element of this refactoring was getting familiar with ranges.
And finding out that clang 12 does not yet support them, hence the use of ranges-v3.

The `split` function implementation, in general, holds little surprises:
- split the parameter `string_view` into a range of subranges
- convert the subranges to `string_view`s
- convert the range of `string_view`s to a `vector` of `string_view`s

A surprise to me was the slightly ugly line necessary for the conversion from split view subranges to `string_view`.
The canonical way would be to create the `string_view` from the `begin` and `end` iterators.
However, in the libstdc++ 10 library I am using, `string_view`'s iterator pair constructor checks a few concepts on the iterators to make sure they point to contiguous memory.
That information gets lost during the split, and the `split_view::inner_iterator` that is returned by `begin` and `end` does not satisfy the constraint.

With the `split` function in place, I used it to replace the manually constructed vectors of multiple arguments.


### [refactor tests: move app execution boilerplate into separate function](https://github.com/arnemertz/fix/commit/80aa50432b781512ad61ded4b8344b7fc31fd44f)

With the `split` function it was now possible to further simplify the test cases.
The CLI app's only responsibility, for now, is to take the command line input and produce output and an exit code. To not clutter the test cases with technical details, I wanted to have a way to convert easily readable input into the two outputs in as little code as possible.

With the `run_result` struct and the `run_app` function that seems to be achieved.
For now, at least: The app will have dependencies in the future, and factoring them into the tests will change how the scaffolding for the test cases has to look.

One last detail in this commit is the new `.clang-tidy` configuration for the CLI tests.
_After_ I had started refactoring the test cases to look more readable, clang-tidy began to complain about the complexity. Talk about irony.
The error messages hinted at the Catch2 macros.
It seems they expand into relatively deeply nested conditionals which triggered the warning.

Since I do not plan to write complicated code in the unit tests, I opted to disable that specific warning completely for them.


### [refactor: introduce docopt](https://github.com/arnemertz/fix/commit/5dee68f31cc5755a0880352a4a4cae6e465b640b)

Even though it does not look like much, this one was what cost me more time than the other refactorings combined.
It took multiple steps to get to this commit:

First, [docopt](https://github.com/docopt/docopt.cpp/blob/master/docopt.cpp) had to be installed.
Thanks to Conan, the installation was one line plus linking it into the CLI app.
Then the integration into the run method had to start.

It started with only parsing the arguments and doing nothing with the results.
`docopt_parse` throws up to four different exceptions, so I wrote a try with the necessary catch blocks:

```
try {
    auto const& parsed_args = docopt::docopt_parse(std::string(USAGE), argv, true, false, true);
    (void)parsed_args;
  } catch (docopt::DocoptExitHelp const&) {
  } catch (docopt::DocoptExitVersion const&) {
  } catch (docopt::DocoptLanguageError const& error) {
  } catch (docopt::DocoptArgumentError& argError) {
  }
```

An `ArgumentError` is thrown whenever the arguments and options do not fit the given usage pattern.
This was the case for the "no arguments" test case, so I moved the treatment for `args.empty()` into the last catch block.

There is one other test case that triggered the exception.
The usage pattern, according to the syntax docopt uses, allowed only one argument for the command.
The test case passing `fruits: apple banana cherries` has multiple arguments, so the usage pattern had to be changed to `[<args>...]` everywhere.

An `ExitHelp` exception is thrown when docopt encounters the `--help` or `-h` option and because the first boolean argument is `true` - otherwise it would throw an `ArgumentError` in my case: 
According to the usage pattern, `--help` alone is not allowed - the `<command>` is not optional.

So I moved the treatment for the `--help` option to the catch block.
Now there were two empty catch blocks left: `ExitVersion` would never be thrown because the second boolean parameter of `docopt_parse` is false.
Since a `--version` option is not a use case right now, I removed the catch block.

I removed the `LanguageError` catch block as well: That exception is thrown when the usage string can not be parsed.
I don't want to catch an exception because a broken program can not be treated in this case.
I _want_ the exception to be thrown and all tests to fail, should I mess up the usage pattern.

After the exceptions were handled, what remained were the "list" command and the "unknown command" test cases.
Those were still outside of the try block and queried `args[0]`, so I moved them into the block and refactored them to use `parsed_args`.

According to the usage pattern, there always is a `<command>`, and since it is free text and a single command, it is a string.
Therefore there is no exception handling for the line `auto const& command = parsed_args.at("<command>").asString();` even though both `at()` and `asString()` theoretically can throw exceptions.
I can't imagine how they would be thrown, or else I would have written test cases for that situation and exception handling to pass the tests.
If they _do_ throw one day, I want to know: let it crash so I can fix it.

There are a few minor things I observed during this refactoring that nag me a bit:
- `app::run` now immediately takes the `vector` of `string_view` it gets and converts it into a `vector` of `string` for docopt.
There is no more reason for the function to require `string_view`s, i.e. the signature can be changed.
(Docopt is unlikely to change its signature soon due to backward compatibility with C++11)
- Whenever I changed the usage pattern in `app.cpp` I had to change it for the unit test, and sometimes for the behave tests as well.
It is questionable whether the tests should be that restrictive.
I'll observe this during the next days and weeks - if I have to touch it more often and change the test expectations every time, I will probably loosen them, e.g. just look for "usage: " and "Available commands"
