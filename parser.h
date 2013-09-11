#ifndef PARSER_H
#define PARSER_H

#include<string>
using namespace std;

class parser{
  string str;
  size_t marker;

  char get(size_t index);

  bool statement();

  bool query();
  bool rel_name();
  bool identifier();
  bool alpha();
  bool digit();
  bool expr();
  bool atomic_expr();
  bool selection();
  bool condition();
  bool conjunction();
  bool comparison();
  bool op();
  bool operand();
  bool attr_name();
  bool projection();
  bool attr_list();
  bool renaming();
  bool union_rel();
  bool difference();
  bool product();

  bool lparen();
  bool rparen();
  bool quote();
  bool comma();
  bool assign();
  bool space();
  bool plus();
  bool minus();
  bool asterisk();
  bool semicolon();
  bool literal(string lit);
  /*
  bool command();
  bool open();
  bool close();
  bool write();
  bool exit();
  bool show();
  bool create();
  bool update();
  bool insert();
  bool del();
  bool typed_attr_list();
  bool type();
  bool integer();
  */
 public:
  bool parse(string input);
};

#endif /* PARSER_H */
