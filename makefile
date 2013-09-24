CXX=clang++
CFLAGS=-O0 -gdwarf-2 -Wall -Wno-sign-compare

all: test.out AST_assembly_test.out AST_traversal_test.out

AST_traversal_test.out: AST_traversal_test.cpp AST_Traversal.o Database.o AST_Assembly.o FileIO.o Relation.o Attribute.o Tuple.o
	$(CXX) $(CFLAGS) AST_traversal_test.cpp AST_Traversal.o Database.o AST_Assembly.o FileIO.o Relation.o Attribute.o Tuple.o -o AST_traversal_test.out

AST_Traversal.o: AST.h AST_Traversal.h AST_Traversal.cpp Database.o AST_Assembly.o FileIO.o Relation.o Attribute.o Tuple.o
	$(CXX) -c $(CFLAGS) AST_Traversal.cpp -o AST_Traversal.o

AST_assembly_test.out: AST_assembly_test.cpp AST_Assembly.o
	$(CXX) $(CFLAGS) AST_assembly_test.cpp AST_Assembly.o -o AST_assembly_test.out

test.out: test.cpp Database.o
	$(CXX) $(CFLAGS) test.cpp Database.o AST_Assembly.o FileIO.o Relation.o Attribute.o Tuple.o -o test.out

Database.o: Database.h Database.cpp Relation.o FileIO.o AST_Assembly.o
	$(CXX) -c $(CFLAGS) Database.cpp

AST_Assembly.o: AST_Assembly.cpp AST_Assembly.h AST.h
	$(CXX) -c $(CFLAGS) AST_Assembly.cpp -o AST_Assembly.o

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
