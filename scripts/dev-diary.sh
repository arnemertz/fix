#! /usr/bin/bash

ISO_DATE=$(date -I)
POST_DATE=$(date "+%F %T %z")
if [ -n "$1" ]; then
  ISO_DATE=$(date -I --date="$1")
  POST_DATE=$(date "+%F %T %z" --date="$1")
fi

REPO_DIR=$(git rev-parse --show-toplevel)
POSTS_DIR=${REPO_DIR}/docs/_posts
POST=$(find "${POSTS_DIR}" -name "${ISO_DATE}*.md")

if [ -z "${POST}" ]; then
  POST="${POSTS_DIR}/${ISO_DATE}-dev-diary.md"
fi

if [ ! -f "${POST}" ]; then
  cat << EOF > "${POST}"
---
layout: post
title:  "Give me a title"
date:   ${POST_DATE}
---

Excerpt placeholder
<!--more-->

## $(date "+%B %-dth" --date="${ISO_DATE}" | sed 's/1th/1st/; s/2th/2nd/; s/3th/3rd/')
EOF
fi

git log --format=format:'%x23%x23%x23 [%s](https://github.com/arnemertz/fix/commit/%H)%n%n' --since="${ISO_DATE} 03:00" --reverse >> "${POST}"
