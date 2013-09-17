CSCE-315-Project-1
==================

Project website: http://students.cse.tamu.edu/pmgrubb/
Project Development Log: https://docs.google.com/document/d/1br3ZOlxMI2DJmGH0HlkowIY-qzD1Fq1WbZCGXc6Eryk/edit?usp=sharing

For more detailed development log, see the git commit log.

We should put something here that explains how to run the project (once its doneish).


Running/Testing
===============

Currently the project only consists of a DBMS engine, with no way of input.
To test to existing DBMS engine code and parser, run the following commands

```
make all
./test.out
./parse_test.out
```
Note that some tests output error messages as they test incorrect calling of functions.
These can be ignored as long as no line says something failed.