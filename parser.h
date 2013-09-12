#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>
using namespace std;

enum TokenType {_null = 0, _identifier, _lparen, _rparen, _comma, _assign,
                _space, _plus, _minus, _asterisk, _semicolon, _g, _l, _e, _ge,
                _le, _ne, _project, _rename,_open, _close, _write, _exit,
                _show, _create, _update, _insert, _delete, _varchar, _integer,
                _table, _primary, _key, _set, _where, _into, _values, _from,
                _lit_integer, _literal};

const extern string TokenStrings[];

struct Token{
  size_t index;
  string field;
  TokenType type;
  size_t size() const {return field.size();}
  size_t length() const {return field.length();}
Token(size_t new_index, string new_field, TokenType new_type)
: index(new_index), field(new_field), type(new_type) {}
};


class parser{
 public:
  vector<Token> tokens;
  string str;
  size_t s_index;
  size_t t_index;

  char get(size_t index);


  // public:
  void lex(string input);
};

#endif /* PARSER_H */
