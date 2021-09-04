---
layout: post
title:  "Description class"
date:   2021-09-03 13:06:14 +0200
---

Compared to the title, the description class is really simple
<!--more-->

## September 3rd
### [add description class](https://github.com/arnemertz/fix/commit/b756c6ec34aecf0102b21b967e80964452a8de59)

There's not much going on with the description class: it is not more than a wrapper around a `std::string` without any checks. Contrary to the stated requirements, it uses a narrow byte string (aka `std::string`) instead of a UTF-8 string I would use for Unicode. The reason is that I have not yet read up enough on how to deal with Unicode to confidently make decisions about the proper types and how to handle Unicode text.

I'll probably switch to UTF-8 (aka. `std::u8string`) when I have done my homework. I'd really like to hear your thoughts about what's the right choice here.

The development of the class has been pretty much by the book in terms of TDD. You could add the content of the test file from top to bottom line by line and would probably end up with essentially the same code.
