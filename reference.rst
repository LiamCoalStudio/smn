Simon Language
==============

:Author: Liam Cole
:Version: 0.1.1b

``it cat language :3``

Tutorial
========

Installing
----------

#. Clone `this repository`_
#. Enter the directory it cloned to.
#. Run: ``mkdir build && cd build``
#. Run: ``cmake ..``
#. Run: ``cmake --build . -- -j8``
#. Run: ``cmake --build . -- test -j1``
#. Run: ``sudo cmake --install .``

.. _this repository: https://github.com/LiamCoal/smn

Using
-----

Here is some example code::

    /language: cpp/#

    uses simon.io;
    end uses;

    main;
        println "test";
        return 0;
    end func;

Save that to ``test.smn``.

Running ``smn -o test test.smn``, then running ``./test`` should print::

    test

Spec
====

1 simon
-------
``uses simon;``

1.1 Stack Functions
~~~~~~~~~~~~~~~~~~~

The Stack is an array of chars 65536 bytes wide.
It can be used to pass arguments to a self-defined function.

1.1.1 ``start_stack;``
######################

:Description: Starts the Stack.
:Since: 0.1.0


1.1.2 ``end_stack;``
####################

:Description: Stops the Stack.
:Since: 0.1.0


1.1.3 ``push <char>;``
######################

:Description: Pushs a byte onto the stack.
:Since: 0.1.0


1.1.4 ``<char> = pop;``
#######################

:Description: Pops a byte off the stack.
:Since: 0.1.0


1.1.5 ``push <void*>, <long>;``
###############################

:Description: Pushes multiple bytes onto the stack.
:Since: 0.1.0


1.1.6 ``<void*> = pop <long>;``
###############################

:Description: Pops multiple bytes off the stack.
:Since: 0.1.0


2 simon.io
----------
``uses simon.io;``

2.1 File Functions
~~~~~~~~~~~~~~~~~~

:Italic: *Not implemented.*

*2.1.1* ``<ifile> = open_in <str>;``
####################################

:Description: Opens a file in input mode.
:Since: .. TODO Not implemented.


*2.1.2* ``<ofile> = open_out <str>;``
#####################################

:Description: Opens a file in output mode.
:Since: .. TODO Not implemented.


*2.1.3* ``<iofile> = open_io <str>;``
#####################################

:Description: Opens a file in both input and output mode.
:Since: .. TODO Not implemented.


*2.1.4* ``write <_stream_>, <void*>, <long>;``
##############################################

:Description: Writes some data to a file.
:Since: .. TODO Not implemented.


*2.1.5* ``<void*> = read <_stream_>, <long>;``
##############################################
