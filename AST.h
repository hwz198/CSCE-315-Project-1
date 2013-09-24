#ifndef AST_H
#define AST_H
#include<string>
#include<iostream>
using namespace std;

enum TokenType {_null = 0, _identifier, _lparen, _rparen, _comma, _assign,
                _space, _plus, _minus, _asterisk, _semicolon, _g, _l, _e, _ge,
                _le, _ne, _select, _project, _rename,_open, _close, _write,
                _exit_key, _show, _create, _update, _insert, _delete, _varchar,
                _integer, _table, _primary, _key, _set, _where, _into, _values,
                _from, _relation, _lit_integer, _literal, _or, _and, _equals};

//decode enums
const string TokenStrings[] = {"null", "identifier", "lparen", "rparen",
                               "comma", "assign", "space", "plus", "minus",
                               "asterisk", "semicolon", "g", "l", "e", "ge",
                               "le", "ne", "select", "project", "rename","open",
                               "close", "write", "exit", "show", "create",
                               "update", "insert", "delete", "varchar",
                               "integer", "table", "primary", "key", "set",
                               "where", "into", "values", "from", "relation",
                               "lit_integer", "literal", "or", "and", "equals"};

const string TagStrings[] = {"UNDEF", "IDENTIFIER", "ASSIGN", "BINARYOP",
                             "SELECT", "PROJECT", "RENAME", "ATTR_NAME",
                             "LITERAL", "LIT_LIST", "ATTR_LIST", "OPEN",
                             "CLOSE", "WRITE", "EXIT", "SHOW", "CREATE",
                             "UPDATE", "UPDATE_LIST", "INSERT", "DELETE",
                             "TYPED_ATTR_LIST", "TYPE"};

class Token{
  size_t m_index;
  string m_field;
  TokenType m_type;
 public:
  size_t size() const {return m_field.size();}
  size_t length() const {return m_field.length();}
  TokenType type() const {return m_type;}
  size_t index() const {return m_index;}
  string field() const {return m_field;}
 Token(size_t new_index, string new_field, TokenType new_type)
   : m_index(new_index), m_field(new_field), m_type(new_type) {}
};

inline ostream& operator<<(ostream& os, Token t){
  return os << t.field();
}


struct AST {
  enum Tag {UNDEF = 0, IDENTIFIER, ASSIGN, BINARYOP, SELECT, PROJECT, RENAME, ATTR_NAME,
            LITERAL, LIT_LIST, ATTR_LIST, OPEN, CLOSE, WRITE, EXIT, SHOW,
            CREATE, UPDATE, UPDATE_LIST, INSERT, DELETE, TYPED_ATTR_LIST,
            TYPE}
    tag;

AST(Tag t) : tag(t) {}
  virtual ~AST() {}
  virtual void print(ostream&) const = 0;
};

inline ostream& operator<<(ostream& os, const AST* a){
  if(a == NULL){
    return os << "NULL";
  }
  a->print(os);
  return os;
}


template<AST::Tag T> //generalization for output
struct TokenAST : AST{
  Token center;

 TokenAST(Token c) : AST(T), center(c) {}
  void print(ostream& os) const {os << "[." << TagStrings[T] << " " << center << " ]";}
};

template<AST::Tag T> //generalization for output
struct SingleAST : AST{
  AST *center;

 SingleAST(AST* c) : AST(T), center(c) {}
  void print(ostream& os) const {os << "[." << TagStrings[T] << " " << center << " ]";}
};

template<AST::Tag T> //generalization for output
struct DoubleAST : AST{
  AST *left, *right;

 DoubleAST(AST* l, AST* r) : AST(T), left(l), right(r) {}
  void print(ostream& os) const {os << "[." << TagStrings[T] << " " << left << " " << right << " ]";}
};

template<AST::Tag T> //generalization for output
struct TripleAST : AST{
  AST *left, *center, *right;

 TripleAST(AST* l, AST* c, AST* r) : AST(T), left(l), center(c), right(r) {}
  void print(ostream& os) const {os << "[." << TagStrings[T] << " " << left << " " << center << " " << right << " ]";}
};


struct IdentifierAST : TokenAST<AST::IDENTIFIER>{
 IdentifierAST(Token id) : TokenAST(id) {}
};

struct AssignAST : AST{
  Token assign;
  AST *left, *right;

  void print(ostream& os) const {os << "[." << TagStrings[ASSIGN] << " " << left << " " << right << " ]";}

 AssignAST(Token as, AST* l, AST* r) : AST(ASSIGN), assign(as), left(l), right(r) {}
};

struct BinaryOpAST : AST{
  TokenType op;
  AST *left, *right;

  void print(ostream& os) const {os << "[." << TokenStrings[op] << " " << left << " " << right << " ]";}

 BinaryOpAST(TokenType o, AST* l, AST* r) : AST(BINARYOP), op(o), left(l), right(r) {}
};

struct SelectAST : DoubleAST<AST::SELECT>{
 SelectAST(AST* condition, AST* relation) : DoubleAST(condition, relation) {}
};

struct ProjectAST : DoubleAST<AST::PROJECT>{
 ProjectAST(AST* attr_list, AST* relation) : DoubleAST(attr_list, relation) {}
};

struct RenameAST : DoubleAST<AST::RENAME>{
 RenameAST(AST* attr_list, AST* relation) : DoubleAST(attr_list, relation) {}
};

/*
struct AttrNameAST : TokenAST<AST::ATTR_NAME>{
 AttrNameAST(Token attribute) : TokenAST(attribute) {}
};
*/

struct LiteralAST : TokenAST<AST::LITERAL>{
 LiteralAST(Token literal) : TokenAST(literal) {}
};

struct LiteralListAST : DoubleAST<AST::LIT_LIST>{
 LiteralListAST(AST* literal, AST* next) : DoubleAST(literal, next) {}
};

struct AttrListAST : DoubleAST<AST::ATTR_LIST>{
 AttrListAST(AST* attr_name, AST* next) : DoubleAST(attr_name, next) {}
};

struct OpenAST : SingleAST<AST::OPEN>{
 OpenAST(AST* relation) : SingleAST(relation) {}
};

struct CloseAST : SingleAST<AST::CLOSE>{
 CloseAST(AST* relation) : SingleAST(relation) {}
};

struct WriteAST : SingleAST<AST::WRITE>{
 WriteAST(AST* relation) : SingleAST(relation) {}
};

struct ExitAST : AST{
  void print(ostream& os) const {os << "EXIT";}
 ExitAST() : AST(EXIT) {}
};

struct ShowAST : SingleAST<AST::SHOW>{
 ShowAST(AST* relation) : SingleAST(relation) {}
};


struct CreateAST : TripleAST<AST::CREATE>{
 CreateAST(AST* relation_name, AST* typed_attr_list, AST* key_list)
   : TripleAST(relation_name, typed_attr_list, key_list) {}
};

struct UpdateAST : TripleAST<AST::UPDATE>{
 UpdateAST(AST* relation_name, AST* update_list, AST* condition)
   : TripleAST(relation_name, update_list, condition) {}
};

struct UpdateListAST : TripleAST<AST::UPDATE_LIST>{
 UpdateListAST(AST* attribute, AST* literal, AST* next)
   : TripleAST(attribute, literal, next) {}
};

struct InsertAST : DoubleAST<AST::INSERT>{
 InsertAST(AST* relation_name, AST* from) : DoubleAST(relation_name, from) {}
};

struct DeleteAST : DoubleAST<AST::DELETE>{
 DeleteAST(AST* relation_name, AST* condition)
   : DoubleAST(relation_name, condition) {}
};

struct TypedAttrListAST : TripleAST<AST::TYPED_ATTR_LIST>{
 TypedAttrListAST(AST* attribute, AST* type, AST* next)
   : TripleAST(attribute, type, next) {}
};

struct TypeAST : TokenAST<AST::TYPE>{
  int size;

 TypeAST(Token type, int s) : TokenAST(type), size(s) {}
  void print(ostream& os) const {os << "[." << TagStrings[AST::TYPE] << " " << center << size << " ]";}
};

#endif /* AST_H */
