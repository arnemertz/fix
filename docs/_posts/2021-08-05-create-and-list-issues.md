---
layout: post
title:  "Creating and listing issues"
date:   2021-08-05 18:00:00 +0200
---

The creation of issues is hard to test without being able to list them, and listing issues can only be done if we can create some.
Therefore, in this step, I'll implement the basics of both features in lockstep.

## 2021-08-05
### [behave: create and list issues](https://github.com/arnemertz/fix/commit/067e814d65c9882eed110429520648223cc56b2c)

The five scenarios in this commit describe two new functionalities in Fix - namely the creation of an issue and listing all issues.
They do not describe how the CLI for these features has to be implemented.

In fact, from now on the CLI app will serve primarily as a test driver so I can access the Fix domain library from the behave tests.
Only when I encounter issues in the CLI app that need to be addressed, I will add tests to drive a fix of those issues.

While the first scenario is one that you'd probably expect for any container or repository ("when it's fresh, it's empty"), the others are not too fine-grained.
For example, you'll note that there is no test that describes that after the creation of one issue there should be that one issue in the list.

Those details can be derived from the other scenarios and should emerge from a straight-forward implementation.
If they don't, there will be unit tests for the details, but I want to avoid testing all of the requirements on both test levels.

The last two scenarios deal with the issue ID I explain in the [milestone description]({{site.baseurl}}{% link _pages/about.md %}) why I don't want to use consecutive numbers.
However, two issues with the same first words in the title that are otherwise different should have different IDs, while creating two issues with the exact same content should get rejected.

The expected error message "issue already exists" implies that the generated hash should be always the same for issues with identical content, i.e. simply generating 28 random bits won't do.
