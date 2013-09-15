#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>
using namespace std;

enum TokenType {_null = 0, _identifier, _lparen, _rparen, _comma, _assign,
                _space, _plus, _minus, _asterisk, _semicolon, _g, _l, _e, _ge,
                _le, _ne, _select, _project, _rename,_open, _close, _write,
                _exit, _show, _create, _update, _insert, _delete, _varchar,
                _integer, _table, _primary, _key, _set, _where, _into, _values,
                _from, _relation, _lit_integer, _literal, _or, _and, _equals};

const extern string TokenStrings[]; //used to "decode" enums

class Token{
  size_t m_index;
  string m_field;
  TokenType m_type;
 public:
  size_t size() const {return m_field.size();}
  size_t length() const {return m_field.length();}
  TokenType type() const {return m_type;}
  size_t index() const {return m_index;}
Token(size_t new_index, string new_field, TokenType new_type)
: m_index(new_index), m_field(new_field), m_type(new_type) {}
};


class parser{
 public:
  vector<Token> tokens;
  string str;
  size_t s_index;
  size_t t_index;

  char get(size_t index);
  Token t_get(size_t index);

  bool statement();

  bool query();
  bool rel_name();
  bool identifier();
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

  bool command();
  bool open_cmd();
  bool open();
  bool close_cmd();
  bool close();
  bool write_cmd();
  bool write();
  bool exit_cmd();
  bool exit();
  bool show_cmd();
  bool show();
  bool create_cmd();
  bool create();
  bool table();
  bool primary();
  bool key();
  bool update_cmd();
  bool update();
  bool set();
  bool where();
  bool insert_cmd();
  bool insert();
  bool into();
  bool values();
  bool from();
  bool relation();
  bool delete_cmd();
  bool delete_keyword();
  bool typed_attr_list();
  bool type();
  bool varchar();
  bool lit_integer();
  bool integer();

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
  bool literal();
  bool select();
  bool project();
  bool rename();
  bool binary_or();
  bool binary_and();
  bool equals();

  // public:
  void lex(string input);
  bool parse(string input);
};

#endif /* PARSER_H */
