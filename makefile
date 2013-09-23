CC=g++
CFLAGS=-O0 -gdwarf-2 -Wall -Wno-sign-compare

all: test.out parse_test.out

parse_test.out: parse_test.cpp Parser.o
	$(CC) $(CFLAGS) parse_test.cpp Parser.o -o parse_test.out

test.out: test.cpp Database.o
	$(CC) $(CFLAGS) test.cpp Database.o Parser.o FileIO.o Relation.o Attribute.o Tuple.o -o test.out

Database.o: Database.h Database.cpp Relation.o FileIO.o Parser.o
	$(CC) -c $(CFLAGS) Database.cpp

Parser.o: Parser.cpp Parser.h AST.h
	$(CC) -c $(CFLAGS) Parser.cpp -o Parser.o

FileIO.o: FileIO.h FileIO.cpp Relation.o Attribute.o Tuple.o
	$(CC) -c $(CFLAGS) FileIO.cpp

Relation.o: Relation.h Relation.cpp Attribute.o Tuple.o
	$(CC) -c $(CFLAGS) Relation.cpp

Attribute.o: Attribute.h Attribute.cpp
	$(CC) -c $(CFLAGS) Attribute.cpp

Tuple.o: Tuple.h Tuple.cpp
	$(CC) -c $(CFLAGS) Tuple.cpp

clean:
	rm -rf *o *out
