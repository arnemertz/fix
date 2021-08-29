---
layout: post
title:  "Roadblock: WSL malfunction"
date:   2021-08-27 06:58:49 +0200
---

Infrastructure matters, and it's frustrating when it just stops working.
<!--more-->

## August 25th-27th

### Who needs a network anyway?

On Wednesday morning, I started the day by writing up the dev diary for Monday. `git commit`. `git push` - nope, I got errors. Poking around a bit revealed that while Windows still had an internet connection, WSL did not. "Network is unreachable". Not a DNS issue, I could not even ping localhost.

So, instead of writing the next tests and code, I spent hours googling for a solution. There are dozens of issues for that error message at the WSL GitHub repo, with small tidbits of information hidden between solutions for different problems. No writeup. None of the tidbits worked for me, short of resetting Windows.

So that's what I did. I spent some hours resetting Windows and reinstalling the most important programs. About as much fun as counting the seeds on a strawberry, especially since I already had to install Windows from scratch on my work machine on Tuesday.


### [add git aliases for the dev diary](https://github.com/arnemertz/fix/commit/29a2c9b2e1b89e1f1c34c7e878c2a2392687cf53)

Annoyed as I was, I had, of course, no secured anything in WSL except for the dev diary entry I could not push. No big deal since everything I needed was in my GitHub repositories. Almost. Installing WSL2 with Ubuntu, Docker Desktop for Windows, and CLion was not a big issue.

I cloned the [docker4c repository](https://github.com/arnemertz/docker4c) for the build toolchain and the [fix repository](https://github.com/arnemertz/fix) itself and built the docker container. Something had changed in the script provided by LLVM to install clang & Co., but since clang-12 now can be installed directly in Ubuntu with apt, that was [easily fixed](https://github.com/arnemertz/docker4c/commit/faa989ecd3ad7b35d1cf3cf421c584405d4ad877).

I copied the saved dev diary entry back into the fix repository and used my git alias to commit it. `dev-diary is not a git command`. Dang. The alias was saved in the local git config and had disappeared with the reinstallation. Since it took some time to piece it together again, I added the init script to set up the aliases whenever I clone the repo somewhere.

So, now I have my workflow for the dev diary back to what it was: I typically write it first thing in the next morning. So what I did today was:

```
✔ ~/git/fix [main|⚑ 1]
06:58 $ ./scripts/dev-diary.sh yesterday
✔ ~/git/fix [main|…1⚑ 1]
06:58 $ code docs/
```

When I am done with this entry, there will be two more commands:
```
$ git ddy       # or git dev-diary yesterday
$ git push
```

And back to the code.
