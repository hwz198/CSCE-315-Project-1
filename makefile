CXX=clang++
CFLAGS=-O0 -gdwarf-2 -Wall -Wno-sign-compare

all: test.out parse_test.out AST_parser_test.out

AST_parser_test.out: AST_parser_test.cpp AST_Parser.o Database.o Parser.o FileIO.o Relation.o Attribute.o Tuple.o
	$(CXX) $(CFLAGS) AST_parser_test.cpp AST_Parser.o Database.o Parser.o FileIO.o Relation.o Attribute.o Tuple.o -o AST_parser_test.out

AST_Parser.o: AST.h AST_Parser.h AST_Parser.cpp Database.o Parser.o FileIO.o Relation.o Attribute.o Tuple.o
	$(CXX) -c $(CFLAGS) AST_Parser.cpp -o AST_Parser.o

parse_test.out: parse_test.cpp Parser.o
	$(CXX) $(CFLAGS) parse_test.cpp Parser.o -o parse_test.out

test.out: test.cpp Database.o
	$(CXX) $(CFLAGS) test.cpp Database.o Parser.o FileIO.o Relation.o Attribute.o Tuple.o -o test.out

Database.o: Database.h Database.cpp Relation.o FileIO.o Parser.o
	$(CXX) -c $(CFLAGS) Database.cpp

Parser.o: Parser.cpp Parser.h AST.h
	$(CXX) -c $(CFLAGS) Parser.cpp -o Parser.o

FileIO.o: FileIO.h FileIO.cpp Relation.o Attribute.o Tuple.o
	$(CXX) -c $(CFLAGS) FileIO.cpp

Relation.o: Relation.h Relation.cpp Attribute.o Tuple.o
	$(CXX) -c $(CFLAGS) Relation.cpp

Attribute.o: Attribute.h Attribute.cpp
	$(CXX) -c $(CFLAGS) Attribute.cpp

Tuple.o: Tuple.h Tuple.cpp
	$(CXX) -c $(CFLAGS) Tuple.cpp

clean:
	rm -rf *o *out
