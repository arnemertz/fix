---
layout: post
title:  "Define first milestone"
date:   2021-07-31 13:57:05 +0200
---

Today, I defined the [first milestone]({% link _pages/milestones.md %}) for Fix and started work on the CLI application.

### [Document first milestone](https://github.com/arnemertz/fix/commit/18916d2cc360a3617d6adf97956827c690de826d)

In the new milestone document, I set a goal of what I want to implement first.
That first milestone may not seem too ambitious, but I'd rather have many small goals than a few big ones: I found that reaching multiple smaller achievements keeps me more motivated over time.

This small goal includes a bunch of hidden things. I'll have to set up libraries, the basic structure of central classes for the CLI application, the data storage, etc.

In the end, the milestone should be enough to start "[dogfooding](https://en.wikipedia.org/wiki/Eating_your_own_dog_food)": With the ability to create and close issues, I can put down individual steps for the next milestone in Fix itself. It sure will be awkward with that little functionality, but that way I can see what bothers me most and set my next goals accordingly.


### [Add feature file for basic CLI behavior](https://github.com/arnemertz/fix/commit/5044cf73abbb5229e7df9d3c8845a6c3f9f29177)

The first feature file for actual behavior I want, yay! Before I go into the implementation of actual Fix behavior regarding issues, I want to make sure that the CLI application fails gracefully when it gets bad input.

The step definitions for the feature exist, although I can not guarantee that they are bug-free yet, as all the tests fail early and never reach the later steps. They will be fixed later on. 

