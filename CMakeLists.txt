cmake_minimum_required (VERSION 2.6)
project (csce315db)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb -Wall -Wno-sign-compare")

add_executable(test.out test.cpp Tuple.cpp Attribute.cpp Relation.cpp FileIO.cpp
  Parser.cpp Database.cpp)

add_executable(parse_test.out parse_test.cpp Parser.cpp)

add_executable(AST_parser_test.out AST_parser_test.cpp AST_Parser.cpp Tuple.cpp Attribute.cpp
  Relation.cpp FileIO.cpp Parser.cpp Database.cpp)
