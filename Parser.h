#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>
#include "AST.h"
using namespace std;

class Parser{
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

  AST* command();
  AST* open_cmd();
  bool open();
  AST* close_cmd();
  bool close();
  AST* write_cmd();
  bool write();
  AST* exit_cmd();
  bool exit();
  AST* show_cmd();
  bool show();
  AST* create_cmd();
  bool create();
  bool table();
  bool primary();
  bool key();
  AST* update_cmd();
  bool update();
  bool set();
  bool where();
  AST* insert_cmd();
  bool insert();
  bool into();
  bool values();
  bool from();
  bool relation();
  AST* delete_cmd();
  bool delete_keyword();
  AST* typed_attr_list();
  AST* type();
  Token varchar();
  Token lit_integer();
  Token integer();

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
  AST* literal_list();
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
