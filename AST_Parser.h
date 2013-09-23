#ifndef AST_PARSER_H
#define AST_PARSER_H

#include "AST.h"
#include "Database.h"

class AST_Parser{
  Database* db;
  Database* views;

  bool assign();
  string identifier(AST*);
  Relation expr(AST*);
  bool binaryop(AST*, Tuple const& t);

 public:
  bool parse(AST* p_ast);
 AST_Parser(Database* d, Database* v) : db(d), views(v) {}

  
};

#endif
