---
layout: post
title:  "The Title domain class"
date:   2021-08-20 18:01:26 +0200
---

Today I started to implement the first actual domain class.
<!--more-->

## August 20th

### [outline for issue title tests](https://github.com/arnemertz/fix/commit/5c239a270cafe766fca8db6b3e57cbcb01edcdb2)

In the big picture, I am still working on creating issues. To create an issue, we need titles and descriptions, among other things. But wait, are those not just strings? They are not. "@{&%#\\\\n`\``what" is a string but not a valid title, nor is the empty string. The [requirements](https://arnemertz.github.io/fix/milestones) say that a title has to be 6-120 characters long and has a certain character set.

In addition, a title is not the same as a description, so the two can't be the same type. Nor can they be the same type as any other "string-y" objects in the domain. Having separate types for separate concepts is not only good practice in Domain-Driven Design. Having [strong types](https://arne-mertz.de/2016/11/stronger-types/) is good practice, in general, to avoid mixing up variables of different semantics.

Having normal strings as input there needs to be a point where they are converted into a title object. All the constraints have to be checked there so we can not end up with an invalid title. The classic solution to this conundrum is to throw an exception from the constructor if the arguments do not fit the requirements. There are other options though, especially for code where exception handling is not wanted or available.

One of those options is having a static factory method that checks the arguments and then creates the object or returns a failure. To ensure that objects are created via that factory method, constructors are made private. The "object or failure" can be modeled by using pointers, `std::optional`, `std::variant`, and similar mechanisms. One of those is the [proposed `std::expected`](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0323r10.html) which I aim for.

But I am getting ahead of myself. This commit mainly introduces the test outline for the restrictions on length and character set of the title class. For now, it is a bunch of empty Catch2 `SECTION`s that describe the requirements they will check. If you're wondering why they are not called "test create" or similar as so often, have a look at Kevlin Henney's brilliant talk about [Good Unit Tests](https://www.youtube.com/watch?v=azoucC_fwzw).

To trigger the creation of the class and the factory method, a single test calls the method and expects it to fail. I _could_ have returned the error reporting type I want to use right from the beginning, but for now, I opted for bool as that's sufficient to pass the single test.

To not inflate the scope of tests, I opted to restrict the title character set to ASCII for now. The product owner agrees.


### [implement length checks for title](https://github.com/arnemertz/fix/commit/b6100462569af5a9ab9d1997382f11e0d7b685d2)

Implementing the length checks is rather straight-forward. I did not go for the dogmatic approach to write one test at a time and make it pass. Instead, I first wrote all the checks in the test case and then implemented the rather simple check to make them pass.

Let's have a quick look at the checks and sections:
- The "too short" check is exactly one character shorter than the minimum length, and the first case in the "allowed range" check is exactly of minimum length.
- The "too long" check is exactly one character longer than the maximum length, and the second case in the "allowed range" check is exactly of maximum length.

It is considered good testing practice to have checks at the edges of ranges where behavior changes. After all, one-off errors are among the most common bugs in software. (In hindsight, instead of "short" I should have used a string that explicitly has length `MIN_LENGTH-1`, in case the minimum length changes one day)

In principle, the "empty string" case is part of the "too short" case, but it gets an explicit mention because of string/string_views's default constructor.


### [add non-exceptional error handling for title::create](https://github.com/arnemertz/fix/commit/137bd912884fa2bac28239d34507df99aa19a4e2)

To get away from the bool return type and towards one of the "object or failure" return types mentioned earlier, I wrote a test case that needed an actual title object to be returned. Since the tests do not have access to the title constructor, I needed to do something with the title, and the best candidate for that was the conversion back to a string, as we'll need it anyway in the future.

The return type I use for now is `std::optional`. It is sufficient to hold either a value or signal a failure. Switching to `std::expected` later will not be a problem as the interface that I have used so far is identical in both types. The motivation for `std::expected` will be to have distinct failures for the different actions that can fail and for the different ways these actions can fail.
