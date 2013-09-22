CC=clang++
CFLAGS=-O0 -gdwarf-2

all: test.out parse_test.out

parse_test.out: parse_test.cpp parser.o
	$(CC) $(CFLAGS) parse_test.cpp parser.o -o parse_test.out

parser.o: parser.cpp parser.h AST.h
	$(CC) -c $(CFLAGS) parser.cpp -o parser.o

test.out: test.cpp Database.o
	$(CC) $(CFLAGS) test.cpp Database.o Relation.o Attribute.o Tuple.o -o test.out

Database.o: Database.h Database.cpp Relation.o
	$(CC) -c $(CFLAGS) Database.cpp

Relation.o: Relation.h Relation.cpp Attribute.o Tuple.o
	$(CC) -c $(CFLAGS) Relation.cpp

Attribute.o: Attribute.h Attribute.cpp
	$(CC) -c $(CFLAGS) Attribute.cpp

Tuple.o: Tuple.h Tuple.cpp
	$(CC) -c $(CFLAGS) Tuple.cpp

clean:
	rm -rf *o *out
