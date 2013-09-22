#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>
#include "AST.h"
using namespace std;

class parser{
 public:
  vector<Token> tokens;
  string str;
  size_t s_index;
  size_t t_index;

  char get(size_t index);
  Token t_get(size_t index);

  AST* statement();

  AST* query();
  AST* rel_name();
  AST* identifier();
  AST* expr();
  AST* atomic_expr();
  AST* selection();
  AST* condition();
  AST* conjunction();
  AST* comparison();
  TokenType op();
  AST* operand();
  AST* attr_name();
  AST* projection();
  AST* attr_list();
  AST* renaming();
  AST* union_rel();
  AST* difference();
  AST* product();
  /*
  AST* command();
  AST* open_cmd();
  AST* open();
  AST* close_cmd();
  AST* close();
  AST* write_cmd();
  AST* write();
  AST* exit_cmd();
  AST* exit();
  AST* show_cmd();
  AST* show();
  AST* create_cmd();
  AST* create();
  AST* table();
  AST* primary();
  AST* key();
  AST* update_cmd();
  AST* update();
  AST* set();
  AST* where();
  AST* insert_cmd();
  AST* insert();
  AST* into();
  AST* values();
  AST* from();
  AST* relation();
  AST* delete_cmd();
  AST* delete_keyword();
  AST* typed_attr_list();
  AST* type();
  AST* varchar();
  AST* lit_integer();
  AST* integer();
  */
  bool lparen();
  bool rparen();
  AST* quote();
  bool comma();
  Token assign();
  AST* space();
  bool plus();
  bool minus();
  bool asterisk();
  bool semicolon();
  AST* literal();
  bool select();
  bool project();
  bool rename();
  bool binary_or();
  bool binary_and();
  bool equals();

  // public:
  bool lex(string input);
  AST* parse(string input);
};

#endif /* PARSER_H */
