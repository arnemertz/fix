---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
title: documentation
---

# Dev Diary
  {% for post in site.posts %}
  - [{{ post.title }}]({{ site.baseurl }}{{ post.url }})
  {% endfor %}