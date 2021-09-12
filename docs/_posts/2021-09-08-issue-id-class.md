---
layout: post
title:  "Issue ID class"
date:   2021-09-08 14:04:15 +0200
---

Start of the issue IDs, namely a new place for the generation algorithm
<!--more-->

## September 8th
### [add issue_id class with generation algorithm](https://github.com/arnemertz/fix/commit/7f71f58add7ae4f2b901463f02652cfc4c0785ae#diff-d0617f8f3dac69e34d4708effb379c7466a30616487d1914b71cd3fafb5a7763)

After the description class, the Issue ID was the next piece missing in the puzzle. As usual, I started with the unit test. For now, they only encompass tests for the construction and the existing algorithm for the generator function.

The algorithm is the one I previously had implemented in the application service. It does not belong there as application services should not contain proper domain logic, so the generator function is the better place for it.

Why did I call the function `generate` and not `create` like in the `title` class? Well, I use `create` merely as a replacement for constructors that can fail, since I opted for `expect` error reporting instead of exceptions. The `generate` function on the other hand does not simply create an object that contains the provided data as in the case of the `title` class. It uses its arguments and some domain logic to determine the actual data needed to create the issue ID.

One bit that implementing the class has revealed was that the application service did not account for the possibility of invalid input when creating an issue. `application_service::create` simply returns a string and I had not yet planned what would happen if the provided title was not valid.

For that reason, there still is a TODO in the function. I yet have to decide which error reporting mechanism to use in the interface of the application service. One choice could be to forward the `expected` error codes, another to translate them to the error reporting mechanism of choice of the CLI application, namely exceptions.
