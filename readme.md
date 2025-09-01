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

This uses `SE_<BRANCHNAME>` macros to determine which engine branch is in use. They don't fully match the Metamod: Source macros but are instead defined in `PossibleSDKs` in https://github.com/tschumann/dirtbot/blob/master/AMBuildScript
