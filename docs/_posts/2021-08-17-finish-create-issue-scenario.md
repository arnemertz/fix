---
layout: post
title:  'Finish "create issue" scenario'
date:   2021-08-17 08:46:56 +0200
---

After today, the "create" issue scenario is working, and the CLI app does no longer contain functionality that does not belong there.
<!--more-->

## August 17th
### [Parse create command options](https://github.com/arnemertz/fix/commit/4724eacdd0a7a8a23917581f6f5f6febd46f17b2)

The main part of this commit is in the CLI app: Until now, the app passed a title to `application_service::create` that happened to get the correct result for the single unit test case. A second test case required to actually parse the `--title` and `--descr` (or `-t` and `-d`) options that were passed in the unit and behave tests all along.

To achieve that, I used docopt again, with a dedicated usage string for the "create" command. I see a pattern emerging in the future: most commands will have a usage string, the argument vector will be parsed by docopt, and the extracted arguments or options will be passed to a method of the application service.

It's [too early](https://arne-mertz.de/2015/01/over-generalization/) to write a generic solution for that, though, since there is only one command with that pattern yet. The actual implementation of the list command should be moved to the application service, but since "list" does not have arguments or options yet, I'd be generalizing 50% of the cases.


### [Move list functionality to application service](https://github.com/arnemertz/fix/commit/81ce3424fb50371c0fd81ab8b6eac3440dc8724b)

Speaking of which. The implementation of the "list" command, albeit rudimentary, is the only piece of domain logic left in the CLI app. This commit solves that by adding the `list` method to the application service and then calling it from the app.

Of course, I started by writing the test case again. It did go from compile error to green test in one keystroke because CLion was helpful enough to generate the method with the correct `return 0` statement. To go by the books, I'd have had to change the return value or the expected value in the test to see it fail. Because, who can say for sure that a test is executed when you've never seen it fail? I'm pretty confident that it does get executed though, so I skipped that part. A tiny bit of pragmatism never hurts.

After having the test case, refactoring the CLI app was next, by calling `application_service::list`. While determining the number of issues belongs to the domain logic, the output format string does not. It is specific to the command-line interface, so it stays in the app.


### [Factor out methods for commands in CLI app](https://github.com/arnemertz/fix/commit/3a72ef9d6544540ab9a0f5b4998ac79596cce196)

Parsing the arguments to the "create" command, creating and calling the application service, and processing the return values has put quite some code into the `run_command` method in the CLI app. In addition, the method now does several things: the logic for the two commands and the logic to select which command to execute. So it's time to refactor.

The refactoring is one of the easiest to do: move the body of each if block into its own function. There could be an argument made for separating the argument parsing and the logic of the `create` method. If you look at the code, you already see the blank line that separates the method into two distinct blocks.

For now, I'll leave the two together for two reasons: the first is that the method is good enough as it is, for now, there are more important things to work on. Pragmatism trumps dogmatism, at least in my book. The second reason is that, as mentioned above, I expect more commands to emerge with a similar pattern. I like to see the code that makes up the pattern in one place and be able to extract the code easily when I come to refactor it.


### [implement steps for "created issues are listed" scenario](https://github.com/arnemertz/fix/commit/ec7cc44381ebb5e64bdc8ff47a417f2a4f73d1a0)

With the code being good enough (for my taste), it's time to move on to the next behave scenario. As usual, the first thing to do is to implement the missing step definitions to make it run and produce actual errors I can work on in the C++ implementation.

The first step is a variation of a step that already existed (creating an issue), so the common functionality is factored out into a separate function. The second step, printing a list of issues, is new. The table in the scenario is stored in the context that behave passes to the step definition.

The implementation of the step defines some of the behavior the CLI app has to implement: it first expects a title line with the column headings "ID", "STATUS", "TITLE", separated by arbitrary non-word characters. That way the test won't fail immediately when I decide to add some pretty-printing to the table, e.g. by separating the columns with pipe symbols. Then the content of the table is expected in the same order as the column headings, including the `[hash]` placeholder, and again separated by non-word characters.

In hindsight, there are two things I could have done better in this commit: The regular expressions are a bit unwieldy and would benefit from a short explanatory comment, as most regular expressions do. The other thing is that the whole python file delegates anything that has to do with I/O to the `fix_cli` module, except the line that checks for the column headings. The functionality needed does not yet exist in that module, but that's no reason to become sloppy.

I'll sneak the regex comments in with the commit for this dev diary entry. The refactoring will be part of one of the next commits.

### A slight change of process

Until now, I have been implementing things depth-first: Implement the behave step definitions for one scenario. Implement the CLI app functionality to make the step pass, refactor, go on to the next scenario. Until now that has been relatively fast switching between two layers (behave and the CLI app), but in the future, there will be more. I just introduced the application layer, the next scenario will require an infrastructure layer for the repository and storage, and the first domain classes will be created.

Continuing by single scenarios would mean constantly switching between all those layers. Instead, I want to go breadth-first: write all step definitions needed for the whole feature file, then all needed functionality in the domain library, then the infrastructure layer, then the CLI app. In the end, tie everything together and see that the behave tests pass.

In other words, I want to implement what is needed for one feature one layer at a time, not one scenario at a time. Whether the implementations in the layers will occur in the exact sequence I wrote above is not that important and remains to be seen.