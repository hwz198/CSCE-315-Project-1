#include "AST_Assembly.h"
#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;

AST* AST_Assembly::parse(string input){
  t_index = 0;
  if(lex(input)){
    size_t first_index = t_index;
    AST* statement;
    if((statement = query()) && semicolon()){
      if(t_index == tokens.size()){
        return statement;
      }
    }
    t_index = first_index;
    if((statement = command()) && semicolon()){
      if(t_index == tokens.size()){
        return statement;
      }
    }
    t_index = first_index;
  }
  return NULL;
}

char AST_Assembly::get(size_t index){
  if(index < str.size()){
    return str[index];
  }
  return (char)0;
}

Token AST_Assembly::t_get(size_t index){
  if(index < tokens.size()){
    return tokens[index];
  }
  return Token(0, "", _null);
}

AST* AST_Assembly::query(){
  AST* relAST = rel_name();
  Token assign_tok = assign();
  AST* exprAST = expr();
  if(relAST && assign_tok.type() != _null && exprAST){
    return new AssignAST(assign_tok, relAST, exprAST);
  }
  return NULL;
}

AST* AST_Assembly::rel_name(){
  return identifier();
}

AST* AST_Assembly::identifier(){
  if(t_get(t_index).type() == _identifier){
    IdentifierAST* idenAST = new IdentifierAST(t_get(t_index));
    t_index++;
    return idenAST;
  }
  return NULL;
}

AST* AST_Assembly::expr(){
  size_t first_index = t_index;
  AST* exprAST = selection();
  if(exprAST){
    return exprAST;
  }
  t_index = first_index;
  exprAST = projection();
  if(exprAST){
    return exprAST;
  }
  t_index = first_index;
  exprAST = renaming();
  if(exprAST){
    return exprAST;
  }
  t_index = first_index;
  exprAST = union_rel();
  if(exprAST){
    return exprAST;
  }
  t_index = first_index;
  exprAST = difference();
  if(exprAST){
    return exprAST;
  }
  t_index = first_index;
  exprAST = product();
  if(exprAST){
    return exprAST;
  }
  t_index = first_index;
  exprAST = atomic_expr();
  if(exprAST){
    return exprAST;
  }
  t_index = first_index;
  return NULL;
}

AST* AST_Assembly::atomic_expr(){
  size_t first_index = t_index;
  AST* atomicAST = rel_name();
  if(atomicAST){
    return atomicAST;
  }
  t_index = first_index;
  if(lparen() && (atomicAST = expr()) && rparen()){
    return atomicAST;
  }
  t_index = first_index;
  return NULL;
}

AST* AST_Assembly::selection(){
  AST* cond;
  AST* atomicAST;
  if(select() && lparen() && (cond = condition())
     && rparen() && (atomicAST = atomic_expr())){
    return new SelectAST(cond, atomicAST);
  }
  return NULL;
}

bool AST_Assembly::select(){
  if(t_get(t_index).type() == _select){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::lparen(){
  if(t_get(t_index).type() == _lparen){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::rparen(){
  if(t_get(t_index).type() == _rparen){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::condition(){
  AST* leftAST = conjunction();
  if(leftAST){
    size_t first_index = t_index;
    AST* rightAST;
    while(binary_or() && (rightAST = conjunction())){
      /* every time the loop evals, t_index will change, this is the point
         to set it back to, technically calculated before the failing eval */
      first_index = t_index;
      leftAST = new BinaryOpAST(_or, leftAST, rightAST);
    }
    t_index = first_index;
    return leftAST;
  }
  return NULL;
}

AST* AST_Assembly::conjunction(){
  AST* leftAST = comparison();
  if(leftAST){
    size_t first_index = t_index;
    AST* rightAST;
    while(binary_and() && (rightAST = comparison())){
      /* every time the loop evals, t_index will change, this is the point
         to set it back to, technically calculated before the last eval */
      first_index = t_index;
      leftAST = new BinaryOpAST(_and, leftAST, rightAST);
    }
    t_index = first_index;
    return leftAST;
  }
  return NULL;
}

bool AST_Assembly::binary_or(){
  if(t_get(t_index).type() == _or){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::binary_and(){
  if(t_get(t_index).type() == _and){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::comparison(){
  size_t first_index = t_index;
  AST *left, *right;
  TokenType o;
  if((left = operand()) && (o = op()) && (right = operand())){
    return new BinaryOpAST(o, left, right);
  }
  t_index = first_index;
  if(lparen() && (left = condition()) && rparen()){
    return left;
  }
  t_index = first_index;
  return NULL;
}

TokenType AST_Assembly::op(){
  TokenType o = t_get(t_index).type();
  if(o == _e || o == _ne
     || o == _g || o == _l
     || o == _ge || o == _le){
    t_index++;
    return o;
  }
  return _null;
}

AST* AST_Assembly::operand(){
  size_t first_index = t_index;
  AST* operAST = attr_name();
  if(operAST){
    return operAST;
  }
  t_index = first_index;
  operAST = literal();
  if(operAST){
    return operAST;
  }
  t_index = first_index;
  return NULL;
}

AST* AST_Assembly::attr_name(){
  return identifier();
}

AST* AST_Assembly::literal(){
  if(t_get(t_index).type() == _literal
     || t_get(t_index).type() == _lit_integer){
    AST* litAST = new LiteralAST(t_get(t_index));
    t_index++;
    return litAST;
  }
  return NULL;
}

AST* AST_Assembly::projection(){
  AST *listAST, *atomicAST;
  if(project() && lparen() && (listAST = attr_list())
     && rparen() && (atomicAST = atomic_expr())){
    return new ProjectAST(listAST, atomicAST);
  }
  return NULL;
}

bool AST_Assembly::project(){
  if(t_get(t_index).type() == _project){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::attr_list(){
  size_t first_index = t_index;
  AST* baseAST = attr_name();
  if(baseAST){
    AST* nextAST = NULL;
    if(comma()){
      nextAST = attr_list();
      if(!nextAST){ //stray comma
        t_index = first_index;
        return NULL;
      }
    }
    return new AttrListAST(baseAST, nextAST);
  }
  return NULL;
}

AST* AST_Assembly::renaming(){
  AST *listAST, *atomicAST;
  if(rename() && lparen() && (listAST = attr_list())
     && rparen() && (atomicAST = atomic_expr())){
    return new RenameAST(listAST, atomicAST);
  }
  return NULL;
}

bool AST_Assembly::rename(){
  if(t_get(t_index).type() == _rename){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::union_rel(){
  AST *left, *right;
  if((left = atomic_expr()) && plus() && (right = atomic_expr())){
    return new BinaryOpAST(_plus, left, right);
  }
  return NULL;
}

bool AST_Assembly::plus(){
  if(t_get(t_index).type() == _plus){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::difference(){
  AST *left, *right;
  if((left = atomic_expr()) && minus() && (right = atomic_expr())){
    return new BinaryOpAST(_minus, left, right);
  }
  return NULL;
}

bool AST_Assembly::minus(){
  if(t_get(t_index).type() == _minus){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::product(){
  AST *left, *right;
  if((left = atomic_expr()) && asterisk() && (right = atomic_expr())){
    return new BinaryOpAST(_asterisk, left, right);
  }
  return NULL;

}

bool AST_Assembly::asterisk(){
  if(t_get(t_index).type() == _asterisk){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::semicolon(){
  if(t_get(t_index).type() == _semicolon){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::comma(){
  if(t_get(t_index).type() == _comma){
    t_index++;
    return true;
  }
  return false;
}

Token AST_Assembly::assign(){
  if(t_get(t_index).type() == _assign){
    Token t = t_get(t_index);
    t_index++;
    return t;
  }
  return Token(0, "", _null);
}

AST* AST_Assembly::command(){
  size_t first_index = t_index;
  AST* comAST = open_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  comAST = close_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  comAST = write_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  comAST = exit_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  comAST = show_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  comAST = create_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  comAST = update_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  comAST = insert_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  comAST = delete_cmd();
  if(comAST){
    return comAST;
  }
  t_index = first_index;
  return NULL;
}

AST* AST_Assembly::open_cmd(){
  AST *relAST;
  if(open() && (relAST = rel_name())){
    return new OpenAST(relAST);
  }
  return NULL;
}

bool AST_Assembly::open(){
  if(t_get(t_index).type() == _open){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::close_cmd(){
  AST *relAST;
  if(close() && (relAST = rel_name())){
    return new CloseAST(relAST);
  }
  return NULL;
}

bool AST_Assembly::close(){
  if(t_get(t_index).type() == _close){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::write_cmd(){
  AST *relAST;
  if(write() && (relAST = rel_name())){
    return new WriteAST(relAST);
  }
  return NULL;
}

bool AST_Assembly::write(){
  if(t_get(t_index).type() == _write){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::exit_cmd(){
  if(exit()){
    return new ExitAST;
  }
  return NULL;
}

bool AST_Assembly::exit(){
  if(t_get(t_index).type() == _exit_key){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::show_cmd(){
  AST *relAST;
  if(show() && (relAST = atomic_expr())){
    return new ShowAST(relAST);
  }
  return NULL;
}

bool AST_Assembly::show(){
  if(t_get(t_index).type() == _show){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::create_cmd(){
  AST *relAST, *typedAST, *keyAST;
  if(create() && table() && (relAST = rel_name()) && lparen()
     && (typedAST = typed_attr_list()) && rparen() && primary() && key()
     && lparen() && (keyAST = attr_list()) && rparen()){
    return new CreateAST(relAST, typedAST, keyAST);
  }
  return NULL;
}

bool AST_Assembly::create(){
  if(t_get(t_index).type() == _create){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::table(){
  if(t_get(t_index).type() == _table){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::primary(){
  if(t_get(t_index).type() == _primary){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::key(){
  if(t_get(t_index).type() == _key){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::update_cmd(){
  AST *rel, *attr, *lit;
  size_t first_index = t_index;
  if(update() && (rel = rel_name()) && set()
     && (attr = attr_name()) && equals() && (lit = literal())){
    UpdateListAST* listAST = new UpdateListAST(attr, lit, NULL);
    size_t second_index = t_index;
    while(comma() && (attr = attr_name()) && equals() && (lit = literal())){
      listAST = new UpdateListAST(attr, lit, listAST);
      second_index = t_index;
    }
    t_index = second_index;
    AST *cond;
    if(where() && (cond = condition())){
      return new UpdateAST(rel, listAST, cond);
    }
  }
  t_index = first_index;
  return NULL;
}

bool AST_Assembly::update(){
  if(t_get(t_index).type() == _update){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::set(){
  if(t_get(t_index).type() == _set){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::where(){
  if(t_get(t_index).type() == _where){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::insert_cmd(){
  AST *rel, *list;
  size_t first_index = t_index;
  if(insert() && into() && (rel = rel_name()) && values()
     && from() && lparen() && (list = literal_list()) && rparen()){
    return new InsertAST(rel, list);
  }
  t_index = first_index;
  if(insert() && into() && (rel = rel_name()) && values()
     && from() && relation() && (list = expr())){
    return new InsertAST(rel, list);
  }
  t_index = first_index;
  return NULL;
}

AST* AST_Assembly::literal_list(){
  size_t first_index = t_index;
  AST* baseAST = literal();
  if(baseAST){
    AST* nextAST = NULL;
    if(comma()){
      nextAST = literal_list();
      if(!nextAST){ //stray comma
        t_index = first_index;
        return NULL;
      }
    }
    return new LiteralListAST(baseAST, nextAST);
  }
  return NULL;
}

bool AST_Assembly::insert(){
  if(t_get(t_index).type() == _insert){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::into(){
  if(t_get(t_index).type() == _into){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::values(){
  if(t_get(t_index).type() == _values){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::from(){
  if(t_get(t_index).type() == _from){
    t_index++;
    return true;
  }
  return false;
}

bool AST_Assembly::relation(){
  if(t_get(t_index).type() == _relation){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::delete_cmd(){
  AST *rel, *cond;
  if(delete_keyword() && from() && (rel = rel_name())
     && where() && (cond = condition())){
    return new DeleteAST(rel, cond);
  }
  return NULL;
}

bool AST_Assembly::delete_keyword(){
  if(t_get(t_index).type() == _delete){
    t_index++;
    return true;
  }
  return false;
}

AST* AST_Assembly::typed_attr_list(){
  size_t first_index = t_index;
  AST *attr = attr_name();
  AST *t = type();
  if(attr && t){
    AST* nextAST = NULL;
    //AST *list = new TypedAttrListAST(attr, t, NULL);
    if(comma()){
      nextAST = typed_attr_list();
      if(!nextAST){ //stray comma
        t_index = first_index;
        return NULL;
      }
    }
    return new TypedAttrListAST(attr, t, nextAST);
  }
  return NULL;
}

AST* AST_Assembly::type(){
  size_t first_index = t_index;
  Token var = varchar();
  bool lp = lparen();
  Token sz = lit_integer();
  bool rp = rparen();
  if(var.type() != _null && lp && sz.type() != _null && rp){
    return new TypeAST(var, atoi(sz.field().c_str()));
  }
  t_index = first_index;
  Token i = integer();
  if(i.type() == _integer){
    return new TypeAST(i, -1);
  }
  t_index = first_index;
  return NULL;
}

Token AST_Assembly::varchar(){
  if(t_get(t_index).type() == _varchar){
    Token t = t_get(t_index);
    t_index++;
    return t;
  }
  return Token(0, "", _null);
}

Token AST_Assembly::lit_integer(){
  if(t_get(t_index).type() == _lit_integer){
    Token t = t_get(t_index);
    t_index++;
    return t;
  }
  return Token(0, "", _null);
}

Token AST_Assembly::integer(){
  if(t_get(t_index).type() == _integer){
    Token t = t_get(t_index);
    t_index++;
    return t;
  }
  return Token(0, "", _null);
}


bool AST_Assembly::equals(){
  if(t_get(t_index).type() == _equals){
    t_index++;
    return true;
  }
  return false;
}



bool AST_Assembly::lex(string input){
  tokens.clear();
  str = input;
  s_index = 0;
  while(s_index < str.size()){
    if(isspace(get(s_index))){
      //tokens.push_back(Token(s_index, str.substr(s_index, 1), _space));
      s_index++;
      continue;
    }
    if(get(s_index) == '('){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _lparen));
      s_index++;
      continue;
    }
    if(get(s_index) == ')'){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _rparen));
      s_index++;
      continue;
    }
    if(get(s_index) == ','){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _comma));
      s_index++;
      continue;
    }
    if(get(s_index) == '('){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _lparen));
      s_index++;
      continue;
    }
    if(get(s_index) == '<' && get(s_index+1) == '-'){
      tokens.push_back(Token(s_index, str.substr(s_index, 2), _assign));
      s_index += 2;
      continue;
    }
    if(get(s_index) == '+'){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _plus));
      s_index++;
      continue;
    }
    if(get(s_index) == '-' && !isdigit(get(s_index+1))){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _minus));
      s_index++;
      continue;
    }
    if(get(s_index) == '*'){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _asterisk));
      s_index++;
      continue;
    }
    if(get(s_index) == ';'){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _semicolon));
      s_index++;
      continue;
    }
    if(get(s_index) == '>'){
      if(get(s_index+1) == '='){
        tokens.push_back(Token(s_index, str.substr(s_index, 2), _ge));
        s_index += 2;
        continue;
      } else {
        tokens.push_back(Token(s_index, str.substr(s_index, 1), _g));
        s_index++;
        continue;
      }
    }
    if(get(s_index) == '<'){
      if(get(s_index+1) == '='){
        tokens.push_back(Token(s_index, str.substr(s_index, 2), _le));
        s_index += 2;
        continue;
      } else {
        tokens.push_back(Token(s_index, str.substr(s_index, 1), _l));
        s_index++;
        continue;
      }
    }
    if(get(s_index) == '!' && get(s_index+1) == '='){
      tokens.push_back(Token(s_index, str.substr(s_index, 2), _ne));
      s_index += 2;
      continue;
    }
    if(get(s_index) == '=' && get(s_index+1) == '='){
      tokens.push_back(Token(s_index, str.substr(s_index, 2), _e));
      s_index += 2;
      continue;
    }
    if(get(s_index) == '|' && get(s_index+1) == '|'){
      tokens.push_back(Token(s_index, str.substr(s_index, 2), _or));
      s_index += 2;
      continue;
    }
    if(get(s_index) == '&' && get(s_index+1) == '&'){
      tokens.push_back(Token(s_index, str.substr(s_index, 2), _and));
      s_index += 2;
      continue;
    }
    if(get(s_index) == '='){
      tokens.push_back(Token(s_index, str.substr(s_index, 1), _equals));
      s_index++;
      continue;
    }
    if(str.substr(s_index, 7) == "project"
       /* also check that keyword isnt part of identifier
          and thus isnt followed by alpha or digit */
       && !((get(s_index+7) >= 'a' && get(s_index+7) <= 'z')
            || (get(s_index+7) >= 'A' && get(s_index+7) <= 'Z')
            || (get(s_index+7) >= '0' && get(s_index+7) <= '9')
            || (get(s_index+7) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 7), _project));
      s_index += 7;
      continue;
    }
    if(str.substr(s_index, 6) == "select"
       /* also check that keyword isnt part of identifier
          and thus isnt followed by alpha or digit */
       && !((get(s_index+6) >= 'a' && get(s_index+6) <= 'z')
            || (get(s_index+6) >= 'A' && get(s_index+6) <= 'Z')
            || (get(s_index+6) >= '0' && get(s_index+6) <= '9')
            || (get(s_index+6) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 6), _select));
      s_index += 6;
      continue;
    }
    if(str.substr(s_index, 6) == "rename"
       && !((get(s_index+6) >= 'a' && get(s_index+6) <= 'z')
            || (get(s_index+6) >= 'A' && get(s_index+6) <= 'Z')
            || (get(s_index+6) >= '0' && get(s_index+6) <= '9')
            || (get(s_index+6) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 6), _rename));
      s_index += 6;
      continue;
    }
    if(str.substr(s_index, 4) == "OPEN"
       && !((get(s_index+4) >= 'a' && get(s_index+4) <= 'z')
            || (get(s_index+4) >= 'A' && get(s_index+4) <= 'Z')
            || (get(s_index+4) >= '0' && get(s_index+4) <= '9')
            || (get(s_index+4) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 4), _open));
      s_index += 4;
      continue;
    }
    if(str.substr(s_index, 5) == "CLOSE"
       && !((get(s_index+5) >= 'a' && get(s_index+5) <= 'z')
            || (get(s_index+5) >= 'A' && get(s_index+5) <= 'Z')
            || (get(s_index+5) >= '0' && get(s_index+5) <= '9')
            || (get(s_index+5) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 5), _close));
      s_index += 5;
      continue;
    }
    if(str.substr(s_index, 5) == "WRITE"
       && !((get(s_index+5) >= 'a' && get(s_index+5) <= 'z')
            || (get(s_index+5) >= 'A' && get(s_index+5) <= 'Z')
            || (get(s_index+5) >= '0' && get(s_index+5) <= '9')
            || (get(s_index+5) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 5), _write));
      s_index += 5;
      continue;
    }
    if(str.substr(s_index, 4) == "EXIT"
       && !((get(s_index+4) >= 'a' && get(s_index+4) <= 'z')
            || (get(s_index+4) >= 'A' && get(s_index+4) <= 'Z')
            || (get(s_index+4) >= '0' && get(s_index+4) <= '9')
            || (get(s_index+4) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 4), _exit_key));
      s_index += 4;
      continue;
    }
    if(str.substr(s_index, 4) == "SHOW"
       && !((get(s_index+4) >= 'a' && get(s_index+4) <= 'z')
            || (get(s_index+4) >= 'A' && get(s_index+4) <= 'Z')
            || (get(s_index+4) >= '0' && get(s_index+4) <= '9')
            || (get(s_index+4) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 4), _show));
      s_index += 4;
      continue;
    }
    if(str.substr(s_index, 6) == "CREATE"
       && !((get(s_index+6) >= 'a' && get(s_index+6) <= 'z')
            || (get(s_index+6) >= 'A' && get(s_index+6) <= 'Z')
            || (get(s_index+6) >= '0' && get(s_index+6) <= '9')
            || (get(s_index+6) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 6), _create));
      s_index += 6;
      continue;
    }
    if(str.substr(s_index, 6) == "UPDATE"
       && !((get(s_index+6) >= 'a' && get(s_index+6) <= 'z')
            || (get(s_index+6) >= 'A' && get(s_index+6) <= 'Z')
            || (get(s_index+6) >= '0' && get(s_index+6) <= '9')
            || (get(s_index+6) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 6), _update));
      s_index += 6;
      continue;
    }
    if(str.substr(s_index, 6) == "INSERT"
       && !((get(s_index+6) >= 'a' && get(s_index+6) <= 'z')
            || (get(s_index+6) >= 'A' && get(s_index+6) <= 'Z')
            || (get(s_index+6) >= '0' && get(s_index+6) <= '9')
            || (get(s_index+6) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 6), _insert));
      s_index += 6;
      continue;
    }
    if(str.substr(s_index, 6) == "DELETE"
       && !((get(s_index+6) >= 'a' && get(s_index+6) <= 'z')
            || (get(s_index+6) >= 'A' && get(s_index+6) <= 'Z')
            || (get(s_index+6) >= '0' && get(s_index+6) <= '9')
            || (get(s_index+6) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 6), _delete));
      s_index += 6;
      continue;
    }
    if(str.substr(s_index, 7) == "VARCHAR"
       && !((get(s_index+7) >= 'a' && get(s_index+7) <= 'z')
            || (get(s_index+7) >= 'A' && get(s_index+7) <= 'Z')
            || (get(s_index+7) >= '0' && get(s_index+7) <= '9')
            || (get(s_index+7) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 7), _varchar));
      s_index += 7;
      continue;
    }
    if(str.substr(s_index, 7) == "INTEGER"
       && !((get(s_index+7) >= 'a' && get(s_index+7) <= 'z')
            || (get(s_index+7) >= 'A' && get(s_index+7) <= 'Z')
            || (get(s_index+7) >= '0' && get(s_index+7) <= '9')
            || (get(s_index+7) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 7), _integer));
      s_index += 7;
      continue;
    }
    if(str.substr(s_index, 5) == "TABLE"
       && !((get(s_index+5) >= 'a' && get(s_index+5) <= 'z')
            || (get(s_index+5) >= 'A' && get(s_index+5) <= 'Z')
            || (get(s_index+5) >= '0' && get(s_index+5) <= '9')
            || (get(s_index+5) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 5), _table));
      s_index += 5;
      continue;
    }
    if(str.substr(s_index, 7) == "PRIMARY"
       && !((get(s_index+7) >= 'a' && get(s_index+7) <= 'z')
            || (get(s_index+7) >= 'A' && get(s_index+7) <= 'Z')
            || (get(s_index+7) >= '0' && get(s_index+7) <= '9')
            || (get(s_index+7) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 7), _primary));
      s_index += 7;
      continue;
    }
    if(str.substr(s_index, 3) == "KEY"
       && !((get(s_index+3) >= 'a' && get(s_index+3) <= 'z')
            || (get(s_index+3) >= 'A' && get(s_index+3) <= 'Z')
            || (get(s_index+3) >= '0' && get(s_index+3) <= '9')
            || (get(s_index+3) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 3), _key));
      s_index += 3;
      continue;
    }
    if(str.substr(s_index, 3) == "SET"
       && !((get(s_index+3) >= 'a' && get(s_index+3) <= 'z')
            || (get(s_index+3) >= 'A' && get(s_index+3) <= 'Z')
            || (get(s_index+3) >= '0' && get(s_index+3) <= '9')
            || (get(s_index+3) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 3), _set));
      s_index += 3;
      continue;
    }
    if(str.substr(s_index, 5) == "WHERE"
       && !((get(s_index+5) >= 'a' && get(s_index+5) <= 'z')
            || (get(s_index+5) >= 'A' && get(s_index+5) <= 'Z')
            || (get(s_index+5) >= '0' && get(s_index+5) <= '9')
            || (get(s_index+5) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 5), _where));
      s_index += 5;
      continue;
    }
    if(str.substr(s_index, 4) == "INTO"
       && !((get(s_index+4) >= 'a' && get(s_index+4) <= 'z')
            || (get(s_index+4) >= 'A' && get(s_index+4) <= 'Z')
            || (get(s_index+4) >= '0' && get(s_index+4) <= '9')
            || (get(s_index+4) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 4), _into));
      s_index += 4;
      continue;
    }
    if(str.substr(s_index, 6) == "VALUES"
       && !((get(s_index+6) >= 'a' && get(s_index+6) <= 'z')
            || (get(s_index+6) >= 'A' && get(s_index+6) <= 'Z')
            || (get(s_index+6) >= '0' && get(s_index+6) <= '9')
            || (get(s_index+6) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 6), _values));
      s_index += 6;
      continue;
    }
    if(str.substr(s_index, 4) == "FROM"
       && !((get(s_index+4) >= 'a' && get(s_index+4) <= 'z')
            || (get(s_index+4) >= 'A' && get(s_index+4) <= 'Z')
            || (get(s_index+4) >= '0' && get(s_index+4) <= '9')
            || (get(s_index+4) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 4), _from));
      s_index += 4;
      continue;
    }
    if(str.substr(s_index, 8) == "RELATION"
       && !((get(s_index+8) >= 'a' && get(s_index+8) <= 'z')
            || (get(s_index+8) >= 'A' && get(s_index+8) <= 'Z')
            || (get(s_index+8) >= '0' && get(s_index+8) <= '9')
            || (get(s_index+8) == '_'))) {
      tokens.push_back(Token(s_index, str.substr(s_index, 8), _relation));
      s_index += 8;
      continue;
    }
    if((get(s_index) >= 'a' && get(s_index) <= 'z')
       || (get(s_index) >= 'A' && get(s_index) <= 'Z')){
      size_t first_index = s_index;
      s_index++;
      while((get(s_index) >= 'a' && get(s_index) <= 'z')
            || (get(s_index) >= 'A' && get(s_index) <= 'Z')
            || (get(s_index) >= '0' && get(s_index) <= '9')
            || (get(s_index) == '_')){
        /*
          cout << s_index << endl;
          cout << get(s_index) << endl;
        */
        s_index++;
      }
      tokens.push_back(Token(first_index,
                             str.substr(first_index, s_index - first_index),
                             _identifier));
      continue;
    }
    if(get(s_index) == '\"'){
      size_t first_index = s_index;
      s_index++;
      while(get(s_index) != '\"'){
        s_index++;
      }
      s_index++; //catch quote that escaped while loop
      tokens.push_back(Token(first_index,
                             str.substr(first_index, s_index - first_index),
                             _literal));
      continue;
    }
    if((get(s_index) >= '0' && get(s_index) <= '9')){
      size_t first_index = s_index;
      s_index++;
      while(get(s_index) >= '0' && get(s_index) <= '9'){
        s_index++;
      }
      tokens.push_back(Token(first_index,
                             str.substr(first_index, s_index - first_index),
                             _lit_integer));
      continue;
    }
    if((get(s_index) >= '0' && get(s_index) <= '9') || (get(s_index) == '-')){
      size_t first_index = s_index;
      s_index++;
      while(get(s_index) >= '0' && get(s_index) <= '9'){
        s_index++;
      }
      tokens.push_back(Token(first_index,
                             str.substr(first_index, s_index - first_index),
                             _lit_integer));
      continue;
    }
    //char t = 'a'; //gdb breakpoint
    return 0; //reached if all ifs failed
    /*
      cout << s_index << endl;
      cout << get(s_index) << endl;
      char t;
      cin >> t;
    */
  }
  return true;
}
