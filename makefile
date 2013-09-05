CC=g++
CFLAGS=

Database.o: Database.h Database.cpp Relation.o
	$(CC) -c $(CFLAGS) Database.cpp

Relation.o: Relation.h Relation.cpp Attribute.o Tuple.o
	$(CC) -c $(CFLAGS) Relation.cpp

Attribute.o: Attribute.h Attribute.cpp
	$(CC) -c $(CFLAGS) Attribute.cpp

Tuple.o: Tuple.h Tuple.cpp
	$(CC) -c $(CFLAGS) Tuple.cpp

clean:
	rm -rf *o
