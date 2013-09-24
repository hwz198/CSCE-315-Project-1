#include "Database.h"
#include "AST_Assembly.h"
#include "AST_Traversal.h"

class Parser{
  Database db;
  Database views;
  AST_Assembly A;
  AST_Traversal T;
 public:
 Parser() : db(Database()), views(Database()),
    A(AST_Assembly()), T(AST_Traversal(&db, &views)) {};
  bool parse(string);
};
