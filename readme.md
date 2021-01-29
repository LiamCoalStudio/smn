Simon Language
==============


What is Simon?
--------------

Simon is a simple language to generate source code for other languages (like C and C++). It also provides a library
called simondev to help you program some essential things that you couldn't do otherwise.

Simon's parser is a little weird right now, but it is usable. If you put in invalid syntax, Simon will usually just go
with it, probably assuming its a function or including the rest of the document in a single statement.

What can you do with Simon
--------------------------

You can:

* Open files
* Print to stdout
* Create classes (only in supporting languages)
* Create interfaces (just like in java, where its basically an unimplemented class) (only in supporting languages)
* Create structs
* Create enums
* Create functions
* Create variables and pointers (pointers only in supporting languages)
* Include modules
* Inline code in another language (only works if the language you are inlining can be converted to or is the language
  that is being compiled for)
* Use libraries.
* Include other files. (currently only files that are in the language you are compiling into)

What modules exist in Simon
---------------------------

There are these modules:

* `simon`: Currently just contains the stack.
* `simon.io`: Contains functions to output to stdout.
* `simon.io.fs`: Contains functions to read from and write to files.
* `simon.math`: Currently just contains the math things for the output language
