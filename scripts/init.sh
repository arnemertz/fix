#! /usr/bin/bash

git config alias.dev-diary '!f() { DATE=$(date -I --date="$1"); git add docs/_posts/${DATE}* && git commit -m "dev-diary: add entries for ${DATE}";
 }; f'
git config alias.ddy 'dev-diary yesterday'
