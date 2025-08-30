Outsourced
==========
Fake Source engine for unit testing Source mods and plugins.


How to use
----------
Import outsourced as a git submodule:
```
git submodule add https://github.com/tschumann/outsourced
```

Then include `outsourced.cpp` and `outsourced.h` as part of the project.

Include `outsourced.h` in your test files.

This uses the Metamod: Source macros of `SOURCE_ENGINE` and `SE_<BRANCHNAME>`
