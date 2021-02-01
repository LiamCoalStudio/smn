Simon Language
==============


What is Simon?
--------------

Simon is a simple language to generate source code for other languages (like C and C++). It also provides a library
called `simondev` that adds a bunch of useful functions.

Errors and warnings (produced by code) are a work in progress feature.

What can you do with Simon
--------------------------

You can:

* Open files
* `print` to stdout
* Create `class`es (since 0.1.4)
* Create `interface`s (just like in java, where its basically an unimplemented class) (since 0.1.4)
* Create `struct`s (since 0.2.0)
* Create `enum`s (since 0.2.0)
* Create `func`tions
* Create variables
* Create pointers (since 0.1.1)
* `uses` modules
* Inline code in another `/language/ .. /` (only works if the language you are inlining can be converted to or is the language
  that is being compiled for)
* Use another `library`. (as of 0.2.2)
* `.include` other files. (as of 0.6.0)
* Create `test`s. (as of 0.6.0)
* `run_tests` (as of 0.6.0)
* Create `module`s. (as of 0.5.0 (i forgot to put it in the release notes though))

What modules exist in `simondev`
--------------------------------

There are these modules:

* `simon`: Currently just contains the stack.
* `simon.io`: Contains functions to output to stdout.
* `simon.math`: Currently just contains the math things for the output language + `pi` and `e`
