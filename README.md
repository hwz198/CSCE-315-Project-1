CSCE-315-Project-1
==================

Project website: http://students.cse.tamu.edu/pmgrubb/
Project Development Log: https://docs.google.com/document/d/1br3ZOlxMI2DJmGH0HlkowIY-qzD1Fq1WbZCGXc6Eryk/edit?usp=sharing

For more detailed development log, see the git commit log.


Running/Testing
===============

This project is currently incomplete, the parser is not fully integrated into
the database. The database can be tested with build/test.out, and the basic
syntax checking of the parser can be tested with build/parse_test.out.
Integration of the parser can be tested with build/AST_parser_test.out,
which is not automated and takes input and outputs an AST and a boolean as
the whether or not the statement executed sucessfully. The following commands
DO NOT WORK {OPEN, CLOSE, WRITE, EXIT, UPDATE, DELETE}, everything else should
work.

```
make
build/test.out
build/parse_test.out
build/AST_parser_test.out
```
Note that some tests output error messages as they test incorrect calling of functions.
These can be ignored as long as no line says something failed.