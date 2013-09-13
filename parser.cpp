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

bool parser::parse(string input){
  t_index = 0;
  lex(input);
  size_t first_index = t_index;
  if(query() && semicolon()){
    return true;
  }
  t_index = first_index;
  if(command() && semicolon()){
    return true;
  }
  t_index = first_index;
  return false;
}

void parser::lex(string input){
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
      tokens.push_back(Token(s_index, str.substr(s_index, 4), _exit));
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
    /*
      cout << s_index << endl;
      cout << get(s_index) << endl;
      char t;
      cin >> t;
    */
  }
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

bool parser::query(){
  return rel_name() && assign() && expr();
}

bool parser::rel_name(){
  return identifier();
}

bool parser::identifier(){
  if(t_get(t_index).type() == _identifier){
    t_index++;
    return true;
  }
  return false;
}

bool parser::expr(){
  size_t first_index = t_index;
  if(selection()){
    return true;
  }
  t_index = first_index;
  if(projection()){
    return true;
  }
  t_index = first_index;
  if(renaming()){
    return true;
  }
  t_index = first_index;
  if(union_rel()){
    return true;
  }
  t_index = first_index;
  if(difference()){
    return true;
  }
  t_index = first_index;
  if(product()){
    return true;
  }
  t_index = first_index;
  if(atomic_expr()){
    return true;
  }
  t_index = first_index;
  return false;
}

bool parser::atomic_expr(){
  size_t first_index = t_index;
  if(rel_name()){
    return true;
  }
  t_index = first_index;
  if(lparen() && expr() && rparen()){
    return true;
  }
  t_index = first_index;
  return false;
}

bool parser::selection(){
  return select() && lparen() && condition() && rparen() && atomic_expr();
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

bool parser::condition(){
  if(conjunction()){
    size_t first_index = t_index;
    while(binary_or() && conjunction()){
      /* every time the loop evals, t_index will change, this is the point
         to set it back to, technically calculated before the last eval */
      first_index = t_index;
    }
    t_index = first_index;
    return true;
  }
  return false;
}

bool parser::conjunction(){
  if(comparison()){
    size_t first_index = t_index;
    while(binary_and() && comparison()){
      /* every time the loop evals, t_index will change, this is the point
         to set it back to, technically calculated before the last eval */
      first_index = t_index;
    }
    t_index = first_index;
    return true;
  }
  return false;
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

bool parser::comparison(){
  size_t first_index = t_index;
  if(operand() && op() && operand()){
    return true;
  }
  t_index = first_index;
  if(lparen() && condition() && rparen()){
    return true;
  }
  t_index = first_index;
  return false;
}

bool parser::op(){
  if(t_get(t_index).type() == _e || t_get(t_index).type() == _ne
     || t_get(t_index).type() == _g || t_get(t_index).type() == _l
     || t_get(t_index).type() == _ge || t_get(t_index).type() == _le){
    t_index++;
    return true;
  }
  return false;
}

bool parser::operand(){
  size_t first_index = t_index;
  if(attr_name()){
    return true;
  }
  t_index = first_index;
  if(literal()){
    return true;
  }
  t_index = first_index;
  return false;
}

bool parser::attr_name(){
  return identifier();
}

bool parser::literal(){
  if(t_get(t_index).type() == _literal
     || t_get(t_index).type() == _lit_integer){
    t_index++;
    return true;
  }
  return false;
}

bool parser::projection(){
  return project() && lparen() && attr_list() && rparen() && atomic_expr();
}

bool parser::project(){
  if(t_get(t_index).type() == _project){
    t_index++;
    return true;
  }
  return false;
}

bool parser::attr_list(){
  if(attr_name()){
    size_t first_index = t_index;
    while(comma() && attr_name()){
      first_index = t_index;
    }
    t_index = first_index;
    return true;
  }
  return false;
}

bool parser::renaming(){
  return rename() && lparen() && attr_list() && rparen() && atomic_expr();
}

bool parser::rename(){
  if(t_get(t_index).type() == _rename){
    t_index++;
    return true;
  }
  return false;
}

bool parser::union_rel(){
  return atomic_expr() && plus() && atomic_expr();
}

bool parser::plus(){
  if(t_get(t_index).type() == _plus){
    t_index++;
    return true;
  }
  return false;
}

bool parser::difference(){
  return atomic_expr() && minus() && atomic_expr();
}

bool parser::minus(){
  if(t_get(t_index).type() == _minus){
    t_index++;
    return true;
  }
  return false;
}

bool parser::product(){
  return atomic_expr() && asterisk() && atomic_expr();
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

bool parser::assign(){
  if(t_get(t_index).type() == _assign){
    t_index++;
    return true;
  }
  return false;
}

bool parser::command(){
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

bool parser::open_cmd(){
  return open() && rel_name();
}

bool parser::open(){
  if(t_get(t_index).type() == _open){
    t_index++;
    return true;
  }
  return false;
}

bool parser::close_cmd(){
  return close() && rel_name();
}

bool parser::close(){
  if(t_get(t_index).type() == _close){
    t_index++;
    return true;
  }
  return false;
}

bool parser::write_cmd(){
  return write() && rel_name();
}

bool parser::write(){
  if(t_get(t_index).type() == _write){
    t_index++;
    return true;
  }
  return false;
}

bool parser::exit_cmd(){
  return exit();
}

bool parser::exit(){
  if(t_get(t_index).type() == _exit){
    t_index++;
    return true;
  }
  return false;
}

bool parser::show_cmd(){
  return show() && atomic_expr();
}

bool parser::show(){
  if(t_get(t_index).type() == _show){
    t_index++;
    return true;
  }
  return false;
}

bool parser::create_cmd(){
  return create() && table() && rel_name() && lparen() && typed_attr_list()
    && rparen() && primary() && key() && lparen() && attr_list() && rparen();
}

bool parser::create(){
  if(t_get(t_index).type() == _create){
    t_index++;
    return true;
  }
  return false;
}

bool parser::table(){
  if(t_get(t_index).type() == _table){
    t_index++;
    return true;
  }
  return false;
}

bool parser::primary(){
  if(t_get(t_index).type() == _primary){
    t_index++;
    return true;
  }
  return false;
}

bool parser::key(){
  if(t_get(t_index).type() == _key){
    t_index++;
    return true;
  }
  return false;
}

bool parser::update_cmd(){
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

bool parser::update(){
  if(t_get(t_index).type() == _update){
    t_index++;
    return true;
  }
  return false;
}

bool parser::set(){
  if(t_get(t_index).type() == _set){
    t_index++;
    return true;
  }
  return false;
}

bool parser::where(){
  if(t_get(t_index).type() == _where){
    t_index++;
    return true;
  }
  return false;
}

bool parser::insert_cmd(){
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

bool parser::insert(){
  if(t_get(t_index).type() == _insert){
    t_index++;
    return true;
  }
  return false;
}

bool parser::into(){
  if(t_get(t_index).type() == _into){
    t_index++;
    return true;
  }
  return false;
}

bool parser::values(){
  if(t_get(t_index).type() == _values){
    t_index++;
    return true;
  }
  return false;
}

bool parser::from(){
  if(t_get(t_index).type() == _from){
    t_index++;
    return true;
  }
  return false;
}

bool parser::relation(){
  if(t_get(t_index).type() == _relation){
    t_index++;
    return true;
  }
  return false;
}

bool parser::delete_cmd(){
  return delete_keyword() && from() && rel_name() && where() && condition();
}

bool parser::delete_keyword(){
  if(t_get(t_index).type() == _delete){
    t_index++;
    return true;
  }
  return false;
}

bool parser::typed_attr_list(){
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

bool parser::type(){
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

bool parser::varchar(){
  if(t_get(t_index).type() == _varchar){
    t_index++;
    return true;
  }
  return false;
}

bool parser::lit_integer(){
  if(t_get(t_index).type() == _lit_integer){
    t_index++;
    return true;
  }
  return false;
}

bool parser::integer(){
  if(t_get(t_index).type() == _integer){
    t_index++;
    return true;
  }
  return false;
}

bool parser::equals(){
  if(t_get(t_index).type() == _equals){
    t_index++;
    return true;
  }
  return false;
}
