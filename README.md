CSCE-315-Project-1
==================

Project website: http://students.cse.tamu.edu/pmgrubb/
Project Development Log: https://docs.google.com/document/d/1br3ZOlxMI2DJmGH0HlkowIY-qzD1Fq1WbZCGXc6Eryk/edit?usp=sharing

For more detailed development log, see the git commit log.


Running/Testing
===============

This project currently consists of a DBMS which one interacts with via a parser.
This parser is executed in parser_test.cpp, which runs in a loop and continually
accepts input lines, and outputs a 1 or 0 indicating success or failure of
parsing the input. Example inputs are provided in parser_test.in

To compile and run various tests
```
make
./test.out
./AST_assembly_test.out
./AST_traversal_test.out
./parser_test.out
```
* **test.out** Automatically tests basic DBMS functionality
* **AST_assembly_test.out** Automatically tests basic syntax checking and AST assembly
* **AST_traversal_test.out** Continually takes in statements and outputs if parsing was successful and a tikz-qtree syntax representation of the resulting AST.
* **parser_test.out** Continually takes in and executes statements and outputs whether or not execution was successful.

Note that some tests output error messages as they test incorrect calling of functions.
These can be ignored as long as no line says something failed.