---
layout: post
title:  "Enable use of std::error_code"
date:   2021-08-21 14:37:09 +0200
---

On the way to `std::expect<T, std::error_code>`.
<!--more-->

## August 21st

### [add domain_error enum with std::error_code support](https://github.com/arnemertz/fix/commit/73469cb2c5286a6424f60cb0bd2aea2570a5c62c)

Since I want to use `std::expect`, I had to decide what the error type should be. A plain enum would work, or even just integers, or strings. The latter does not seem a good choice to me, and integers would be either magic numbers or a bunch of predefined constants. That is not really different from enums, except enums are a bit safer in terms of only allowing predefined values.

Then again, if an error is not a domain error but e.g. a file system error or similar, I do not want to mess with `std::expect` with different error types. That is where `std::error_code` comes in. It provides the combination of an enumerator and an error category, the latter includes conversion of the enumerators to printable error messages.

I won't go into much detail about what I did here because I mostly tagged along with [this blog post](https://akrzemi1.wordpress.com/2017/07/12/your-own-error-code/) by Andrzej Krzemieński to implement the necessary steps to use `std::error_code` together with the `domain_error` enum. However, I let the implementation be driven by TDD again - mostly: 

Creating the `std::error_code` from the enum already requires the header parts you see below the "wiring to enable..." comment. The implementation of the `make_error_code` function already pretty much requires all you see in the source file. The only thing I see in hindsight that is not test-driven is the implementation of the `name` method of the fix error category. I should fix that soon.

Having these few lines is all that is needed to return `std::expect<T, std::error_code>` from my domain functions instead of `std::optional`. All that is needed is adding enumerators to the enum as needed, and implementing the conversion into readable error messages.
