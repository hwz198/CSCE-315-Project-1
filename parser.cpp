#include "parser.h"
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

const string TokenStrings[] = {"null = 0", "identifier", "lparen", "rparen",
                               "comma", "assign", "space", "plus", "minus",
                               "asterisk", "semicolon", "g", "l", "e", "ge",
                               "le", "ne", "select", "project", "rename","open",
                               "close", "write", "exit", "show", "create",
                               "update", "insert", "delete", "varchar",
                               "integer", "table", "primary", "key", "set",
                               "where", "into", "values", "from", "relation",
                               "lit_integer", "literal", "or", "and", "equals"};

AST* parser::parse(string input){
  t_index = 0;
  if(lex(input)){
    size_t first_index = t_index;
    AST* q;
    if((q = query()) && semicolon()){
      if(t_index == tokens.size()){
        return q;
      }
    }
    t_index = first_index;
    /*
    if(command() && semicolon()){
      if(t_index == tokens.size()){
        return true;
      }
    }
    t_index = first_index;
    */
  }
  return NULL;
}

char parser::get(size_t index){
  if(index < str.size()){
    return str[index];
  }
  return (char)0;
}

Token parser::t_get(size_t index){
  if(index < tokens.size()){
    return tokens[index];
  }
  return Token(0, "", _null);
}

AST* parser::query(){
  AST* relAST = rel_name();
  Token assign_tok = assign();
  AST* exprAST = expr();
  if(relAST && assign_tok.type() != _null && exprAST){
    return new AssignAST(assign_tok, relAST, exprAST);
  }
  return NULL;
}

AST* parser::rel_name(){
  return identifier();
}

AST* parser::identifier(){
  if(t_get(t_index).type() == _identifier){
    IdentifierAST* idenAST = new IdentifierAST(t_get(t_index));
    t_index++;
    return idenAST;
  }
  return NULL;
}

AST* parser::expr(){
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

AST* parser::atomic_expr(){
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

AST* parser::selection(){
  AST* cond;
  AST* atomicAST;
  if(select() && lparen() && (cond = condition())
     && rparen() && (atomicAST = atomic_expr())){
    return new SelectAST(cond, atomicAST);
  }
  return NULL;
}

bool parser::select(){
  if(t_get(t_index).type() == _select){
    t_index++;
    return true;
  }
  return false;
}

bool parser::lparen(){
  if(t_get(t_index).type() == _lparen){
    t_index++;
    return true;
  }
  return false;
}

bool parser::rparen(){
  if(t_get(t_index).type() == _rparen){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::condition(){
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

AST* parser::conjunction(){
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

bool parser::binary_or(){
  if(t_get(t_index).type() == _or){
    t_index++;
    return true;
  }
  return false;
}

bool parser::binary_and(){
  if(t_get(t_index).type() == _and){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::comparison(){
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

TokenType parser::op(){
  TokenType o = t_get(t_index).type();
  if(o == _e || o == _ne
     || o == _g || o == _l
     || o == _ge || o == _le){
    t_index++;
    return o;
  }
  return _null;
}

AST* parser::operand(){
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

AST* parser::attr_name(){
  return identifier();
}

AST* parser::literal(){
  if(t_get(t_index).type() == _literal
     || t_get(t_index).type() == _lit_integer){
    AST* litAST = new LiteralAST(t_get(t_index));
    t_index++;
    return litAST;
  }
  return NULL;
}

AST* parser::projection(){
  AST *listAST, *atomicAST;
  if(project() && lparen() && (listAST = attr_list())
     && rparen() && (atomicAST = atomic_expr())){
    return new ProjectAST(listAST, atomicAST);
  }
  return NULL;
}

bool parser::project(){
  if(t_get(t_index).type() == _project){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::attr_list(){
  AST* baseAST = attr_name();
  if(baseAST){
    size_t first_index = t_index;
    AST* nextAST;
    while(comma() && (nextAST = attr_name())){
      first_index = t_index;
      baseAST = new AttrListAST(baseAST, nextAST);
    }
    t_index = first_index;
    return new AttrListAST(baseAST, NULL);
  }
  return NULL;
}

AST* parser::renaming(){
  AST *listAST, *atomicAST;
  if(rename() && lparen() && (listAST = attr_list())
     && rparen() && (atomicAST = atomic_expr())){
    return new RenameAST(listAST, atomicAST);
  }
  return NULL;
}

bool parser::rename(){
  if(t_get(t_index).type() == _rename){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::union_rel(){
  AST *left, *right;
  if((left = atomic_expr()) && plus() && (right = atomic_expr())){
    return new BinaryOpAST(_plus, left, right);
  }
  return NULL;
}

bool parser::plus(){
  if(t_get(t_index).type() == _plus){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::difference(){
  AST *left, *right;
  if((right = atomic_expr()) && minus() && (left = atomic_expr())){
    return new BinaryOpAST(_minus, left, right);
  }
  return NULL;
}

bool parser::minus(){
  if(t_get(t_index).type() == _minus){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::product(){
  AST *left, *right;
  if((right = atomic_expr()) && asterisk() && (left = atomic_expr())){
    return new BinaryOpAST(_asterisk, left, right);
  }
  return NULL;

}

bool parser::asterisk(){
  if(t_get(t_index).type() == _asterisk){
    t_index++;
    return true;
  }
  return false;
}

bool parser::semicolon(){
  if(t_get(t_index).type() == _semicolon){
    t_index++;
    return true;
  }
  return false;
}

bool parser::comma(){
  if(t_get(t_index).type() == _comma){
    t_index++;
    return true;
  }
  return false;
}

Token parser::assign(){
  if(t_get(t_index).type() == _assign){
    t_index++;
    return t_get(t_index);
  }
  return Token(0, "", _null);
}

/*
AST* parser::command(){
  size_t first_index = t_index;
  if(open_cmd()){
    return true;
  }
  t_index = first_index;
  if(close_cmd()){
    return true;
  }
  t_index = first_index;
  if(write_cmd()){
    return true;
  }
  t_index = first_index;
  if(exit_cmd()){
    return true;
  }
  t_index = first_index;
  if(show_cmd()){
    return true;
  }
  t_index = first_index;
  if(create_cmd()){
    return true;
  }
  t_index = first_index;
  if(update_cmd()){
    return true;
  }
  t_index = first_index;
  if(insert_cmd()){
    return true;
  }
  t_index = first_index;
  if(delete_cmd()){
    return true;
  }
  t_index = first_index;
  return false;
}

AST* parser::open_cmd(){
  return open() && rel_name();
}

AST* parser::open(){
  if(t_get(t_index).type() == _open){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::close_cmd(){
  return close() && rel_name();
}

AST* parser::close(){
  if(t_get(t_index).type() == _close){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::write_cmd(){
  return write() && rel_name();
}

AST* parser::write(){
  if(t_get(t_index).type() == _write){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::exit_cmd(){
  return exit();
}

AST* parser::exit(){
  if(t_get(t_index).type() == _exit_key){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::show_cmd(){
  return show() && atomic_expr();
}

AST* parser::show(){
  if(t_get(t_index).type() == _show){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::create_cmd(){
  return create() && table() && rel_name() && lparen() && typed_attr_list()
    && rparen() && primary() && key() && lparen() && attr_list() && rparen();
}

AST* parser::create(){
  if(t_get(t_index).type() == _create){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::table(){
  if(t_get(t_index).type() == _table){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::primary(){
  if(t_get(t_index).type() == _primary){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::key(){
  if(t_get(t_index).type() == _key){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::update_cmd(){
  size_t first_index = t_index;
  if(update() && rel_name() && set() && attr_name() && equals() && literal()){
    size_t second_index = t_index;
    while(comma() && attr_name() && equals() && literal()){
      second_index = t_index;
    }
    t_index = second_index;
    if(where() && condition()){
      return true;
    }
  }
  t_index = first_index;
  return false;
}

AST* parser::update(){
  if(t_get(t_index).type() == _update){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::set(){
  if(t_get(t_index).type() == _set){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::where(){
  if(t_get(t_index).type() == _where){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::insert_cmd(){
  size_t first_index = t_index;
  if(insert() && into() && rel_name() && values()
     && from() && lparen() && literal()){
    size_t second_index = t_index;
    while(comma() && literal()){
      second_index = t_index;
    }
    t_index = second_index;
    if(rparen()){
      return true;
    }
  }
  t_index = first_index;
  if(insert() && into() && rel_name() && values()
     && from() && relation() && expr()){
    return true;
  }
  t_index = first_index;
  return false;
}

AST* parser::insert(){
  if(t_get(t_index).type() == _insert){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::into(){
  if(t_get(t_index).type() == _into){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::values(){
  if(t_get(t_index).type() == _values){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::from(){
  if(t_get(t_index).type() == _from){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::relation(){
  if(t_get(t_index).type() == _relation){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::delete_cmd(){
  return delete_keyword() && from() && rel_name() && where() && condition();
}

AST* parser::delete_keyword(){
  if(t_get(t_index).type() == _delete){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::typed_attr_list(){
  if(attr_name() && type()){
    size_t first_index = t_index;
    while(comma() && attr_name() && type()){
      first_index = t_index;
    }
    t_index = first_index;
    return true;
  }
  return false;
}

AST* parser::type(){
  size_t first_index = t_index;
  if(varchar() && lparen() && lit_integer() && rparen()){
    return true;
  }
  t_index = first_index;
  if(integer()){
    return true;
  }
  t_index = first_index;
  return false;
}

AST* parser::varchar(){
  if(t_get(t_index).type() == _varchar){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::lit_integer(){
  if(t_get(t_index).type() == _lit_integer){
    t_index++;
    return true;
  }
  return false;
}

AST* parser::integer(){
  if(t_get(t_index).type() == _integer){
    t_index++;
    return true;
  }
  return false;
}
*/

bool parser::equals(){
  if(t_get(t_index).type() == _equals){
    t_index++;
    return true;
  }
  return false;
}



bool parser::lex(string input){
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
      tokens.push_back(Token(s_index, str.substr(s_index, 2), _or));
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
    char t = 'a'; //gdb breakpoint
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
