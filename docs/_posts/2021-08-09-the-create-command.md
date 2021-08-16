---
layout: post
title:  'The "create" command'
date:   2021-08-09 08:06:06 +0200
---

After the "list" command, "create" was the next thing missing in the CLI app.
<!--more-->

## August 9th
### [implement and extend steps for "create an issue" scenario](https://github.com/arnemertz/fix/commit/499bd9d306bffd930b2917f6510ba98fad64f487)

As before, the steps of the "create an issue" scenario had to be implemented before the scenario could point out missing features. The first thing was to implement the step "when we create an issue" which was missing completely. This step uses a [text block as step data](https://behave.readthedocs.io/en/stable/gherkin.html#step-data) which can be extracted from the behave context.

Implementing the step definition posed a minor technical challenge: The title and description of an issue may well contain blanks, so the `start_fix` function could no longer just split the arguments by blanks but had to respect quoted strings as a single argument. Luckily, Python provides that functionality with `shlex.split`.

The second thing to do was an extension to the output expectations: I do not want to provide an exact hash for issue IDs in the feature files, as that would require knowledge of the hash function which is an implementation detail. I do not want to write regular expressions in the feature files either, so I used "[hash]" as a placeholder.

The pexpect library which I am using to check for the program output supports regular expressions. However, I currently use that feature only if there was a "[hash]" placeholder in the expected output. Otherwise, other expected outputs like the usage string that contains "[--help]" would be interpreted as a regex and break existing tests.

With more functionality, the expected outputs will probably become more complicated and the current naive implementation won't hold any longer. However, for now, it is sufficient and I'll cross that bridge when I come to it.

### [add command "create" to CLI app](https://github.com/arnemertz/fix/commit/0ea5805f307ebc804a9250b97e3daf3c6a682b24)

While writing the test for the "create" command, I came across the same issue with splitting by blanks that I had in Python. Instead of digging into ranges again and trying to find a solution that respects quoted strings, I went for the easy solution: I refactored the `run_app` helper function to have an overload that takes the vector of arguments.

This first test calls "create" for a single issue and expects a matching output. The minimal implementation required by TDD may seem disappointing: the CLI app handles the command by exactly printing the matching output, and that's it. However, the code now _does_ handle the create command. In addition, the unit test uses a different title and expects a different output than the behave scenario. So, to make that pass, proper handling of the "create" command is not far now.

### Planning the next changes

Extending the tests for the "create" command will lead to actual domain logic for the first time: The title will have to be parsed and a matching issue ID has to be created. In addition, the [requirements](https://arnemertz.github.io/fix/milestones) call for checks on the length and content of the title and issue. It's hard or at least tedious to check those in behave, but there should be unit tests that make sure the requirements are met.

All these things do not belong in the CLI app. Instead, there will be domain objects that contain the necessary domain logic. These may include a class for issues, but also things like the algorithm used to generate issue IDs. There will also be one or several application services that are responsible for taking the "raw" strings the CLI app extracts from the command line and translate them into domain logic calls.

The upcoming scenarios require some kind of persistence which will be provided to the application services in the form of repositories. For now, I have planned to implement the persistence with a single JSON file.

With those additions, instances of the major components of a ["ports and adapters" architecture](https://alistair.cockburn.us/hexagonal-architecture/) will be in place, as it is often referenced in Domain-Driven Design literature:
- The domain core, containing the domain logic
- An application service, orchestrating calls to the domain core and implementing and providing _ports_ to the required functionality
- The CLI app that uses the port provided by the application service
- A JSON-based repository that implements the repository port required by the application service
