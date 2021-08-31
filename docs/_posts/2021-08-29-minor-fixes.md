---
layout: post
title:  "Minor Fixes"
date:   2021-08-29 07:46:43 +0200
---

Only a few minor fixes
<!--more-->

## August 29th


### [fix minor review findings in title](https://github.com/arnemertz/fix/commit/e02053d8decc57eda0d3505a0333a407f1120ec8)

After writing the previous diary entry on Sunday, I only fixed the two findings I had while reviewing the code. The first one is small: it gives the lambda that does the actual creation of the title object a name. It's not as much of an improvement as I'd have liked, but it's the best I could come up with. The alternatives did not quite cut it:

- We can not take the address of a constructor and pass it as a callable, so there has to be some indirection if I want to fully use the chain call feature (i.e. `map` in this case)
- A normal function, e.g. in an anonymous namespace does not work, since it would have to use a private constructor. Only member functions can do that.
- I could have made `make_title` a static member function, but that would only be more code and unnecessarily add that detail to the header, which feels even more awkward than the named lambda. I wish modules would already work out of the box with CMake and everything.
- Not using `map` here would not make the code much more readable.

The second finding was that trimming the text and comparing lengths to check whether it has been trimmed was overkill. Checking whether the first or last character is a whitespace is more readable as it directly conveys the meaning of what "not trimmed" means.

The added check for an empty text is necessary here in any case. Yes, I could have moved the `check_trimmed` call after the `check_length` call and then it would exit early on empty strings, but making the implementation undefined behavior or not depending on the call order is a bad idea. There's no need to cut corners here.
