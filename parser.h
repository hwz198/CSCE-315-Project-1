#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>
using namespace std;

class parser{
  enum TokenType {_null = 0, _indentifier, _lparen, _rparen, _comma, _assign,
                  _space, _plus, _minus, _asterisk, _semicolon, _g, _l, _e, _ge,
                  _le, _ne, _project, _rename,_open, _close, _write, _exit,
                  _show, _create, _update, _insert, _delete, _varchar, _integer,
                  _table, _primary, _key, _set, _where, _into, _values, _from,
                  _relation, _literal};

  struct Token{
    size_t index;
    string field;
    TokenType type;
    size_t size() const {return field.size();}
    size_t length() const {return field.length();}
  Token(size_t new_index, string new_field, TokenType new_type)
  : index(new_index), field(new_field), type(new_type) {}
  };

  vector<Token> tokens;
  string str;
  size_t s_index;
  size_t t_index;

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
  void lex(string input);
  bool parse(string input);
};

#endif /* PARSER_H */
