#ifndef PARSER_H
#define PARSER_H

#include<string>
using namespace std;

enum TokenType {_null = 0, _indentifier, _lparen, _rparen, _quote, _comma,
                _assign, _space, _plus, _minus, _asterisk, _semicolon, _g, _l,
                _e, _ge, _le, _ne}

class parser{
  struct Token{
    size_t index;
    string field;
    size_t size(){return field.size()};
    size_t length(){return field.length()};
  }

  }
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

  void consumeWhitespace();
 public:
  bool parse(string input);
};

#endif /* PARSER_H */
