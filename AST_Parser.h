#ifndef AST_PARSER_H
#define AST_PARSER_H

#include "AST.h"
#include "Database.h"
#include <string>
using namespace std;

struct Value{
  enum {INTEGER, STRING} kind;
  string s;
  int i;
};

class AST_Parser{
  Database* db;
  Database* views;

  bool assign();
  string identifier(AST*);
  Relation expr(AST*);
  bool binaryop(AST*, Tuple const& t, vector<Attribute> const&);
  Token literal(AST*);
  Value ident_or_literal(AST*, Tuple const&, vector<Attribute> const&);
  bool perform_op(Value, Value, TokenType);
  Attribute make_attr(AST*, string);

 public:
  bool parse(AST* p_ast);
 AST_Parser(Database* d, Database* v) : db(d), views(v) {}
};

#endif
