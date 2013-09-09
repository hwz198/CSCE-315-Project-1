CC=g++
CFLAGS=-O0 -g

all: test.out

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
