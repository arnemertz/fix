---
layout: post
title:  "The empty list scenario"
date:   2021-08-06 18:59:25 +0200
---

Today was about the first functional scenario: getting a list of 0 issues.
<!--more-->

## August 6th 2021
### [behave: implement steps for empty list scenario](https://github.com/arnemertz/fix/commit/027039edfe3fef39e1cdf7627f799ef9efa36261)

The "list issues for an empty repository" scenario was still failing due to steps not being implemented.
Behave is somewhat helpful in that regard as it emits messages like this one:

```
You can implement step definitions for undefined steps with these snippets:
 
@given(u'an empty issue repository')
def step_impl(context):
    raise NotImplementedError(u'STEP: Given an empty issue repository')
```

I took these hints and implemented the three missing steps.
One was the "terminates with exit code OK" step which had a clash with the "terminates with exit code 0" step I had written before.
Currently, both steps coexist thanks to pattern matching, but I like the "OK" one more as it describes the semantics, not the technical detail.

The "When we list all issues" step implementation is straight-forward.
It calls "fix list" and that way defines the command line argument that the app will have to handle.

The "Given an empty issue repository" step might be a bit surprising: it does exactly nothing.
The question might be "then why do unnecessary work and write the sentence in the feature file and the step definition?"

The answer is that "When we list all issues it prints 0 issues" is only true for an empty repository, it's not a general case.
There surely will be scenarios that start with a non-empty repository, and those will have a matching step.

Another answer is one that does not really count: we might have to actually implement this step in the future if Fix can only work with an existing repository.
It does not count because that's in the future - we should never write code because of "might"s and "maybe"s.

That's the "YAGNI" principle: _You Ain't Gonna Need It_.
It does not mean we should not keep in mind likely code changes - we should write code that is extensible, but we should not extend it right now unless we need the extension now.


### [feature: list 0 issues](https://github.com/arnemertz/fix/commit/ee3a0bb134f5deeaca91b8c7b096a6fc5e5742a7)

Now that the steps are defined, the app has to implement the feature.
The current failure was that it was complaining that "'list' is not a fix command".

The implementation is short, albeit disappointing: First, write a test that demands the exact output we defined in the scenario.
Then, write the least possible lines of code that make the test pass - nothing fancy.

What about refactoring? After all, that's the next step after making the test pass, right?
I'm coming to that in a second. It's getting late, just let me get sidetracked with a little tooling I wanted to have all week.


### [tooling: add script for dev-diary posts](https://github.com/arnemertz/fix/commit/6b67af8c4ccca9fac23e13629e7ada1c697ec85d)

After writing the dev diary for almost two weeks now, it got a bit tedious of listing the commits for each day, copying together the links to the individual commits, and so on.
As you can see from the diff, the individual posts also had slightly different formats regarding the dates, so I wanted to automate as much as possible.

The result is, that at the end of each day I run the script, and it creates a new markdown file for the dev diary post.
All I have to do is write the prose and find a title - the dates are formatted as I want them, the links are there, etc.

During the week I may do some work on the project in the morning, not knowing whether I find time to do more in the evening.
That's OK, I can just run the script in the morning and again in the evening, it will append to an existing file.
All I have to do is remove duplicate links.

Call me lazy - in cases like this I am, and it's a good thing.
I even went one step further right now and automated the commit message for the dev diary posts with git aliases:

```
[alias]
    commit-dev-diary = "!f() { git add docs/_posts/$1* && git commit -m \"dev-diary: add entries for $1\"; }; f"
    ddyesterday = !"git commit-dev-diary $(date -I --date=yesterday)\"
    ddtoday = !"git commit-dev-diary $(date -I)\"
```

This kind of little improvement is what makes work actually fun for me.
Not only did I reduce the time I have to spend with the technical aspect of the dev diary I also learned a thing or two about bash scripting (in this instance, the `date` command and heredocs).
Being a C++ specialist is interesting, but it also takes a good measure of generalist knowledge to get the work done effectively.


### Upcoming refactorings

There are a handful of things I left to be refactored due to my short tooling detour:

- `cli::app` unit tests. There's a pattern emerging how the app class is tested: create a stringstream to capture the output.
Assemble a vector of arguments, run it, check the output and return code. 
The stringstream handling and the vector are mostly boilerplate.
The most expressive way to write unit tests would be passing a simple string with space-separated arguments to a function and get something back that has the output string and exit code.

- Argument processing in `cli::app`. Working with the argument vector and handling the different inputs and commands has become unwieldy even before there is any actual functionality to speak of.
There are several command-line argument processing libraries that may help. I have set my eyes on [docopt](https://github.com/docopt/docopt.cpp) since it looks as if it's going to help a lot with printing the usage strings etc.

- The behave step checking for numeric exit codes is redundant.
As discussed earlier, I like the semantic exit codes more, so I'll get rid of the numeric one.
