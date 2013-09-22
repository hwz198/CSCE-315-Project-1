#ifndef AST_H
#define AST_H
#include<string>
using namespace std;

enum TokenType {_null = 0, _identifier, _lparen, _rparen, _comma, _assign,
                _space, _plus, _minus, _asterisk, _semicolon, _g, _l, _e, _ge,
                _le, _ne, _select, _project, _rename,_open, _close, _write,
                _exit_key, _show, _create, _update, _insert, _delete, _varchar,
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



struct AST {
  enum Tag {UNDEF = 0, IDENTIFIER, ASSIGN, BINARYOP, SELECT, PROJECT, RENAME, ATTR_NAME,
            LITERAL, ATTR_LIST, OPEN, CLOSE, WRITE, EXIT, SHOW,
            CREATE, UPDATE, INSERT, DELETE, TYPED_ATTR_LIST,
            TYPE}
    tag;

AST(Tag t) : tag(t) {}
  virtual ~AST() {}
};

struct IdentifierAST : AST{
  Token identifier;

 IdentifierAST(Token id) : AST(IDENTIFIER), identifier(id) {}
};

struct AssignAST : AST{
  Token assign;
  AST *right, *left;

 AssignAST(Token as, AST* r, AST* l) : AST(ASSIGN), assign(as), right(r), left(l) {}
};

struct BinaryOpAST : AST{
  TokenType op;
  AST *left, *right;

 BinaryOpAST(TokenType o, AST* l, AST* r) : AST(BINARYOP), op(o), left(l), right(r) {}
};

struct SelectAST : AST{
  AST *condition, *relation;

 SelectAST(AST* c, AST* r) : AST(SELECT), condition(c), relation(r) {}
};

struct ProjectAST : AST{
  AST *attr_list, *relation;

 ProjectAST(AST* a, AST* r) : AST(PROJECT), attr_list(a), relation(r) {}
};

struct RenameAST : AST{
  AST *attr_list, *relation;

 RenameAST(AST* a, AST* r) : AST(RENAME), attr_list(a), relation(r) {}
};

struct AttrNameAST : AST{
  Token attribute;

 AttrNameAST(Token a) : AST(ATTR_NAME), attribute(a) {}
};

struct LiteralAST : AST{
  Token literal;

 LiteralAST(Token l) : AST(LITERAL), literal(l) {}
};

struct AttrListAST : AST{
  AST* attr_name;
  AST* next;

 AttrListAST(AST* a, AST* n) : AST(ATTR_LIST), attr_name(a), next(n) {}
};

struct OpenAST : AST{
  Token relation;

 OpenAST(Token r) : AST(OPEN), relation(r) {}
};

struct CloseAST : AST{
  Token relation;

 CloseAST(Token r) : AST(CLOSE), relation(r) {}
};

struct WriteAST : AST{
  Token relation;

 WriteAST(Token r) : AST(WRITE), relation(r) {}
};

struct ExitAST : AST{
 ExitAST() : AST(EXIT) {}
};

struct ShowAST : AST{
  Token relation;

 ShowAST(Token r) : AST(SHOW), relation(r) {}
};

struct CreateAST : AST{
  Token relation_name;
  AST *typed_attr_list, *key_list;

 CreateAST(Token r, AST* a, AST* k)
   : AST(CREATE), relation_name(r), typed_attr_list(a), key_list(k) {}
};

struct UpdateAST : AST{
  Token relation_name;
  AST *update_list, *condition; //TODO: what is update_list

 UpdateAST(Token r, AST* u, AST* c)
   : AST(UPDATE), relation_name(r), update_list(u), condition(c) {};
};

struct InsertAST : AST{
  Token relation_name;
  AST *from;

 InsertAST(Token r, AST* f) : AST(INSERT), relation_name(r), from(f) {}
};

struct DeleteAST : AST{
  Token relation_name;
  AST *condition;

 DeleteAST(Token r, AST* c) : AST(DELETE), relation_name(r), condition(c) {}
};

struct TypedAttrListAST : AST{
  Token attribute;
  AST *type, *next;

  TypedAttrListAST(Token a, AST* t, AST* n)
    : AST(TYPED_ATTR_LIST), attribute(a), type(t), next(n) {}
};

struct TypeAST : AST{
  Token type;
  int size;

 TypeAST(Token t, int s) : AST(TYPE), type(t), size(s) {}
};

#endif /* AST_H */
