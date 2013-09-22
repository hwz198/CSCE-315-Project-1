#ifndef AST_H
#define AST_H

struct AST {
  enum Tag {IDENTIFIER, ASSIGN, BINARYOP, SELECT, PROJECT, RENAME, ATTR_NAME,
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
  AST* right, left;

 AssignAST(Token as, AST* r, AST* l) : AST(ASSIGN), assign(as), right(r), left(l) {}
};

struct BinaryOpAST : AST{
  Token op;
  AST* left, right;

 BinaryOpAST(Token o, AST* l, AST* r) : AST(BINARYOP), op(o), left(l), right(r) {}
};

struct SelectAST : AST{
  AST* condition, relation;

 SelectAST(AST* c, AST* r) : AST(SELECT), condition(c), relation(r) {}
};

struct ProjectAST : AST{
  AST* attr_list, relation;

 ProjectAST(AST* a, AST* r) : AST(PROJECT), attr_list(a), relation(r) {}
};

struct RenameAST : AST{
  AST* attr_list, relation;

 Rename(AST* a, AST* r) : AST(RENAME), attr_list(a), relation(r) {}
};

struct AttrNameAST : AST{
  Token attribute;

 AttrNameAST(AST* a) : AST(ATTR_NAME), attribute(a) {}
};

struct LiteralAST : AST{
  Token literal;

 LiteralaST(AST* l) : AST(LITERAL), literal(l) {}
};

struct AttrListAST : AST{
  Token attribute;
  AST* next;

 AttrListAST(Token a, AST* n) : AST(ATTR_LIST), attribute(a), next(n) {}
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
  AST* typed_attr_list, key_list;

 CreateAST(Token r, AST* a, AST* k)
   : AST(CREATE), relation_name(r), typed_attr_list(a), key_list(k) {}
};

struct UpdateAST : AST{
  Token relation_name;
  AST* update_list, condition; //TODO: what is update_list

 UpdateAST(Token r, AST* u, AST* c)
   : relation_name(r), update_list(u), condition(c) {};
};

struct InsertAST : AST{
  Token relation_name;
  AST* from;

 InsertAST(Token r, AST* f) : AST(INSERT), relation_name(r), from(f) {}
};

struct DeleteAST : AST{
  Token relation_name;
  AST* condition;

 DeleteAST(Token r, AST* c) : AST(DELETE) relation_name(R), condition(c) {}
};

struct TypedAttrListAST : AST{
  Token attribute;
  AST* type;
  AST* next;

  TypedAttrListAST(Token a, Token t, AST* n)
    : AST(TYPED_ATTR_LIST), attribute(a), type(t), next(n) {}
};

struct TypeAST : AST{
  Token type;
  int size;

 TypeAST(Token t, int s) : AST(TYPE), type(t), size(s) {}
};

#endif /* AST_H */
