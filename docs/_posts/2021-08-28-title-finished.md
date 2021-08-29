---
layout: post
title:  "Title finished"
date:   2021-08-28 10:43:22 +0200
---

On Saturday, I finished the title class, at least for now.
<!--more-->

## August 28th

### [add character checks for title](https://github.com/arnemertz/fix/commit/c9120acf2f8dc632a594b7caab3ffe462683204d)

With tl::expected and the domain error code in place, there wasn't too much new work left to implement the test case sections about the allowed character set for titles. The tests do not cover every single character, but they express the intent well enough that a straightforward implementation will fit the requirements. That means I could still pass all tests while e.g. forbidding characters that should be allowed, but I'd have to specifically add code for that, which no test gives me a reason to do.

I have ordered the checks for the different forbidden characters from general to specific. First comes the check for non-ASCII characters. ASCII characters are in the value range 0-127. The code in question uses an `int`, i.e. the `char`s in the string are widened to `int`. The reason is that `char` may be signed or unsigned. In the former case, its value can not be larger than `CHAR_MAX`, while in the latter in can not be negative. Widening to `int` avoids warnings about either case.

The second check looks for non-printable characters. [`isprint`](https://en.cppreference.com/w/cpp/string/byte/isprint) returns a non-zero value for spaces, digits, letters, and punctuation, which is almost the allowed character set for titles. This check _has_ to come after the ASCII check for two reasons: arguments to `isprint` have to be presentable as `unsigned char`. In case `char` is signed, the ASCII check eliminates negative values and thus avoids undefined behavior. In case `char` is unsigned, there are non-ASCII characters that may or may not be printable, depending on the locale, which would lead to inconsistent behavior. Having the ASCII check first eliminates that problem as well.

The last check added is for the two special characters that are explicitly not allowed in the requirements.

In addition to the test and implementation code, I also added a bit of code to improve the expressiveness of tests on failure when dealing with `expected`. Until now, a failure of the `FailsWithMessage` matcher produced output like this:
```
  CHECK_THAT(title::create("we \xE2\x99\xA5 unicode. Not."), FailsWithMessage("title may not contain non-ASCII characters"))
with expansion:
  {?} Fails with message 'title may not contain non-ASCII characters'
```

Here, the `{?}` stands for the `expected<title>` object and it does not tell me whether it contains a value or whether the error just produced a different message. Catch2 can not do any better unless I tell it how to serialize that type. Since the serialization is only needed for the tests, the typical ostream `operator<<` would not be the right solution here. Luckily, Catch2 provides a mechanism for cases like this one, namely the specialization of `Catch::StringMaker<T>`. With that in place, the expansion in the test output now looks like either the first or the second of these lines:

```
  unexpected(12: 'title can only contain letters') Fails with message 'title may not contain non-ASCII characters'
  expected({?}) Fails with message 'title may not contain non-ASCII characters'  
```

The first line is shown when the `expected` contains a failure (but has not produced the expected error message). It shows the value of the error enumerator and the start of the message. In the second line, we still see a `{?}`, but this time it's the title object that could not be serialized. For now, it's sufficient for me to know that the `expected` object contains a value, i.e. the expected failure has not happened.


### [enforce use of title::create and store text in title](https://github.com/arnemertz/fix/commit/23212d62fa93789674589f3588c30c10aecd2629)

While I was implementing all the things that were required of the `title::create` function, I realized at some point that nothing prevented me from default constructing a `title`, which clearly should not be allowed. In addition, the tests still only called for a hard-coded string returned by `title::str`.

So I wrote tests to check that titles can only be copied and moved but never constructed except within the `title` class itself. I also extended the test for `title::str()`. To have `str()` return the correct title text, I had to store it, which in turn required an appropriate constructor. Having the constructor disabled default construction and made the corresponding check pass. Making the constructor private made the other check pass.

Since the `std::string` member is copyable and movable, so is `title`, and the two corresponding checks passed right from the beginning. The compiler-generated special members are doing the right thing, [no need to even mention them](https://arne-mertz.de/2015/02/the-rule-of-zero-revisited-the-rule-of-all-or-nothing/).

Last but not least, while `str()` is a name we may know from the standard library, `to_string` is more expressive, so I refactored that name.


### [check that titles are trimmed](https://github.com/arnemertz/fix/commit/bcba2898e525bb66b5f28442db010d10d8a098f1)

Another thing that occurred to me while I was implementing the checks was that the current implementation allowed for a title consisting of a single letter followed by a couple of spaces, enough to pass the length restriction. One might even write a title consisting only of spaces.

My first instinct was to trim the input of the `create` function before any of the checks. On the other hand, silently creating a title that differs from the input seems wrong. So I decided to allow only trimmed input. I also decided to check for _any_ leading or trailing whitespace, not only blanks, because I consider e.g. a title ending with a line break as "not trimmed" and not as "contains forbidden characters".

The implementation I chose for the check is done as "would trimming the text do anything to it?", which, in hindsight, is way too complicated. I could just have checked the first and last character of the text. Lesson learned: reviewing your own code on the next day may yield chances for improvement.


### [refactor title::create](https://github.com/arnemertz/fix/commit/1cd5ea38e7330eb0e5909601f4e9c93f913279da)

Over time, the `title::create` function has grown quite a bit. It now is too long and does several different things in detail, namely checking several different sets of constraints and then creating an actual title object.

The basic structure of refactoring it into several detailed functions was clear, including the names `check_trimmed`, `check_length`, and `check_charset`. The return types of those functions were not as clear, at least not from the beginning.

I started with functions that returned `std::error_code`s. The `create` function then contained several blocks that looked like this:

```
auto const error_code = check_trimmed(text);
if (error_code) {
  return unexpected(error_code);
}
```

It was a bit unwieldy for my taste. Returning an `expected<void>` would lead to similar code. Then I remembered reading that [Sy Brand's `expected` implementation](https://github.com/TartanLlama/expected) has functionality that is not in the `std::expected` proposal that is meant for this exact use case. The resulting code looks quite readable to me:

```
expected<title> title::create(std::string_view text) {
  // clang-format off
  return check_trimmed(text)
      .and_then(check_length)
      .and_then(check_charset)
      .map([](auto text){ return title{text}; });
  // clang-format on
}
```

Except maybe the last line which looks a bit awkward, but I have an idea for a fix for that as well.
