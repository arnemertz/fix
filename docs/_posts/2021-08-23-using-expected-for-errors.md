---
layout: post
title:  "Using expected for errors"
date:   2021-08-23 00:00:00 +0200
---

Since `std::expected` is not part of the standard library in C++20, I use Sy Brand's implementation.
<!--more-->

## August 23rd
### [instroduce tl::expected as return value for possibly failing functions](https://github.com/arnemertz/fix/commit/c15012cdb8663ccd53d7d7b3f51325e9da07f9ed)

Thanks to Conan, adding [Sy Brand's `tl::expected`](https://github.com/TartanLlama/expected) to the project is a one-liner. On the CMake side, it is a dependency of the domain library, albeit a public one since I'll be using it as a return value from the library's API.

I started this commit by fixing an oversight I mentioned in the last diary entry: The return value of `fix_error_category_t::name()` was not implemented with TDD, so I added the necessary test first and then fixed the name.

Next, I added a template alias for `tl::expected<T, std::error_code>`: it's a lot to read, and the second template parameter should never change, so writing `expected<T>` instead in the domain namespace is much clearer. Replacing the return type of `title::create` with `expected<title>` did not necessitate any changes to the tests, but the error case had to be changed from `std::nullopt` to a `std::error_code`. The error code should be of the fix domain category, so it required a new enumerator in `domain_error` - `MISSING_IMPLEMENTATION` clearly was not the correct one. The message for that error code is an empty string for now - no test yet requires otherwise.

Last but not least I added a convenience wrapper to `tl::unexpected`. At first sight, this only gets rid of the `tl::` in the domain code, but it also restricts arguments to `domain_error`. For the `expected` alias I use, `tl::unexpected` can be called with any `std::error_code` and all enums that are convertible into it.


### [improve tests with a matcher for tl::expected](https://github.com/arnemertz/fix/commit/2491b8e61007185c29bbb2da94e97e937ae412eb)

With `expected` introduced as return value, the tests could be extended to not only check for failure but also for a meaningful message associated with that failure. When writing those tests, the most natural and helpful error messages introduced the need to distinguish between titles that are too long or too short. The old "length out of bounds" enumerator had to be replaced by two new ones.

Writing the tests showed a pattern that would be required wherever the correct failure via `expected` has to be tested: store the result object, check that it converts to `false`, check the message of the error code:

```
  const auto result = title::create("");
  CHECK_FALSE(result);
  CHECK(result.error().message() == "title is too short");
```

Having variants of those three lines repeated all over the tests would be tedious and harder to read than I liked, so I looked for ways to simplify the code. The solution to that challenge is [matchers in Catch2](https://github.com/catchorg/Catch2/blob/devel/docs/matchers.md): the macro `CHECK_THAT(arg, matcher)` takes the argument that has to be tested and a matcher object that does the test. So I set up a test case for a new matcher and got to work implementing what was needed.

At first, I tried to use the "new style" matchers mentioned in the link above, until I realized that they do not yet exist in the version of Catch2 that is available via Conan. With those new matchers, the match function testing the argument can be templated, i.e. a single matcher class can check an `expected<void>`, `expected<int>`, `expected<title>`, and so on.

So it had to be either an "old style" matcher with a single match function parameter type suitable for all specializations of `expected`, or a templated matcher where I would have to explicitly state the argument type when creating the matcher, which would not be ideal.

Trying to find a way to solve things with a single matcher class, I went down the wrong road at first: taking `expected<std::any>` as the parameter to the match function does not work, because `expected<void>` can not be converted to `expected<std::any>` with the same error code, but instead it is silently converted to `std::any` which in turn leads to an `expected<std::any>` that has a value, i.e. is not failed.

The solution I settled for in the end is an intermediate inspection type that the matcher function takes as a parameter. The type has a templated conversion constructor that can take any specialization of `expected` and extracts the information needed for the matcher.

It may seem like a lot of work - it took me some time experimenting and failing until the matcher test case passed. However, from now on, all checks for failure do not have the three lines shown above but instead read like this:

```
CHECK_THAT(title::create(""), FailsWithMessage("title is too short"));
```

This is the level of readability I want in my tests. After all, they are not only a means of making sure that the code works but also a [form of documentation](https://arne-mertz.de/2015/05/purposes-of-unit-tests/#Documenting_the_code).
