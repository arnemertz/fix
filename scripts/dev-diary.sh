#! /usr/bin/bash

REPO_DIR=$(git rev-parse --show-toplevel)
POSTS_DIR=${REPO_DIR}/docs/_posts
ISO_DATE=$(date -I)
POST=$(find "${POSTS_DIR}" -name "${ISO_DATE}*.md")

if [ -z "${POST}" ]; then
  POST="${POSTS_DIR}/${ISO_DATE}-dev-diary.md"
fi

if [ ! -f "${POST}" ]; then
  cat << EOF > "${POST}"
---
layout: post
title:  "Give me a title"
date:   $(date "+%F %T %z")
---

Excerpt placeholder
<!--more-->

## $(date "+%B %-dth %Y" | sed 's/1th/1st/; s/2th/2nd/; s/3th/3rd/')
EOF
fi

git log --format=format:'%x23%x23%x23 [%s](https://github.com/arnemertz/fix/commit/%H)%n%n' --since="03:00" --reverse >> "${POST}"
