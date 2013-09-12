#include "parser.h"
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

void parser::lex(string input){
  str = input;
  t_index = 0;
  while(t_index < str.size()){
    if(isspace(get(t_index))){
      //tokens.push_back(Token(t_index, get(t_index), _space));
      t_index++;
      continue;
    }
    if(get(t_index) == '('){
      tokens.push_back(Token(t_index, get(t_index), _lparen));
      t_index++;
      continue;
    }
    if(get(t_index) == ')'){
      tokens.push_back(Token(t_index, get(t_index), _rparen));
      t_index++;
      continue;
    }
    if(get(t_index) == ','){
      tokens.push_back(Token(t_index, get(t_index), _comma));
      t_index++;
      continue;
    }
    if(get(t_index) == '('){
      tokens.push_back(Token(t_index, get(t_index), _lparen));
      t_index++;
      continue;
    }
    if(get(t_index) == '<' && get(t_index+1) == '-'){
      tokens.push_back(Token(t_index, str.substr(t_index, 2), _assign));
      t_index += 2;
      continue;
    }
    if(get(t_index) == '+'){
      tokens.push_back(Token(t_index, get(t_index), _plus));
      t_index++;
      continue;
    }
    if(get(t_index) == '-'){
      tokens.push_back(Token(t_index, get(t_index), _minus));
      t_index++;
      continue;
    }
    if(get(t_index) == '*'){
      tokens.push_back(Token(t_index, get(t_index), _asterisk));
      t_index++;
      continue;
    }
    if(get(t_index) == ';'){
      tokens.push_back(Token(t_index, get(t_index), _semicolon));
      t_index++;
      continue;
    }
    if(get(t_index) == '>'){
      if(get(t_index+1) == '='){
        tokens.push_back(Token(t_index, str.substr(t_index, 2), _ge));
        t_index += 2;
        continue;
      } else {
        tokesn.push_back(Token(t_index, get(t_index), _g));
        t_index++;
        continue;
      }
    }
    if(get(t_index) == '<'){
      if(get(t_index+1) == '='){
        tokens.push_back(Token(t_index, str.substr(t_index, 2), _le));
        t_index += 2;
        continue;
      } else {
        tokesn.push_back(Token(t_index, get(t_index), _l));
        t_index++;
        continue;
      }
    }
    if(get(t_index) == '!' && get(t_index+1) == '='){
      tokens.push_back(Token(t_index, str.substr(t_index, 2), _ne));
      t_index += 2;
      continue;
    }
    if(get(t_index) == '=' && get(t_index+1) == '='){
      tokens.push_back(Token(t_index, str.substr(t_index, 2), _e));
      t_index += 2;
      continue;
    }
    if(str.substr(t_index, 7) == "project"){
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _project));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 6) == "rename"){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _rename));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 4) == "OPEN"){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _open));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 5) == "CLOSE"){
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _close));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 5) == "WRTIE"){
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _write));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 4) == "EXIT"){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _exit));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 4) == "SHOW"){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _show));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 6) == "CREATE"){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _create));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "UPDATE"){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _update));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "INSERT"){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _update));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "DELETE"){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _delete));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 7) == "VARCHAR"){
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _varchar));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 5) == "TABLE"){
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _table));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 7) == "PRIMARY"){
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _primary));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 3) == "KEY"){
      tokens.push_back(Token(t_index, str.substr(t_index, 3), _key));
      t_index += 3;
      continue;
    }
    if(str.substr(t_index, 3) == "SET"){
      tokens.push_back(Token(t_index, str.substr(t_index, 3), _set));
      t_index += 3;
      continue;
    }
    if(str.substr(t_index, 5) == "WHERE"){
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _where));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 4) == "INTO"){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _into));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 6) == "VALUES"){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _values));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 4) == "FROM"){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _FROM));
      t_index += 4;
      continue;
    }
  }
}

bool parser::parse(string input){
  str = input;
  marker = 0;
  return statement();
}

bool parser::statement(){
  bool val = query() && semicolon(); //|| command();
  cout << marker << endl;
  cout << get(marker-1) << get(marker) << get(marker+1) << endl;
  return val;
}

bool parser::query(){
  return rel_name() && assign() && expr();
}

bool parser::rel_name(){
  return identifier();
}

bool parser::identifier(){
  if (quote()) {
    if (alpha()) {
          while (alpha() || digit()){
          }
          if (quote()) {
            return true;
          }
        }
  } else if (alpha()) {
      while (alpha() || digit()){
      }
      consumeWhitespace();
      return true;
  }
  return false;
}

bool parser::alpha(){
  if((get(marker) >= 'A' && get(marker) <= 'Z')
     || (get(marker) >= 'a' && get(marker) <= 'z')
     || get(marker) == '_'){
    marker++;
    return true;
  }
  return false;
}

bool parser::digit(){
  if(get(marker) >= '0' && get(marker) <= '9'){
    marker++;
    return true;
  }
  return false;
}

bool parser::expr(){
  return selection() || projection() || renaming()
    || union_rel() || difference() || product() || atomic_expr();
}

bool parser::atomic_expr(){
  return rel_name() || (lparen() && expr() && rparen());
}

bool parser::selection(){
  return literal("select") && lparen() && condition() && rparen() && atomic_expr();
}

bool parser::condition(){
  if (conjunction()) {
    if (literal("||") && conjunction()) {
      return true;
    }
    consumeWhitespace();
    return true;
  }
  return false;
}

bool parser::conjunction(){
  if (comparison()) {
    if (literal("&&") && conjunction()){
      return true;
    }
    consumeWhitespace();
    return true;
  }
  return false;
}

bool parser::comparison(){
  return (operand() && op() && operand()) || (lparen() && condition() && rparen());
}

bool parser::op(){
  return literal("==") || literal("!=") || literal("<") || literal(">")
    || literal("<=") || literal(">=");
}

bool parser::operand(){
  return attr_name(); // || literal()?
}

bool parser::attr_name(){
  return identifier();
}

bool parser::projection(){
  return literal("project") && lparen() && attr_list() && rparen() && atomic_expr();
}

bool parser::attr_list(){
  if (attr_name()){
    while (comma() && attr_name()){
    }
    return true;
  }
  return false;
}

bool parser::renaming(){
  return literal("rename") && lparen() && attr_list() && rparen() && atomic_expr();
}

bool parser::union_rel(){
  return atomic_expr() && plus() && atomic_expr();
}

bool parser::difference(){
  return atomic_expr() && minus() && atomic_expr();
}

bool parser::product(){
  return atomic_expr() && asterisk() && atomic_expr();
}

bool parser::assign(){
  if(get(marker) == '<' && get(marker+1) == '-'){
    marker += 2;
    consumeWhitespace();
    return true;
  }
  return false;
}

bool parser::quote(){
  if(get(marker) == '\"'){
    marker++;
    return true;
  }
  return false;
}

bool parser::space(){
  if(get(marker) == ' '){
    marker++;
    return true;
  }
  return false;
}

bool parser::lparen(){
  if(get(marker) == '('){
    marker++;
    consumeWhitespace();
    return true;
  }
  return false;
}

bool parser::rparen(){
  if(get(marker) == ')'){
    marker++;
    consumeWhitespace();
    return true;
  }
  return false;
}

bool parser::literal(string lit){
  if(marker + lit.size() < str.size()){
    if(str.substr(marker, marker+lit.size()) == lit){
      marker += lit.size();
      consumeWhitespace();
      return true;
    }
  }
  return false;
}

bool parser::plus(){
  if(get(marker) == '+'){
    marker++;
    consumeWhitespace();
    return true;
  }
  return false;
}

bool parser::minus(){
  if(get(marker) == '-'){
    marker++;
    consumeWhitespace();
    return true;
  }
  return false;
}


bool parser::asterisk(){
  if(get(marker) == '*'){
    marker++;
    consumeWhitespace();
    return true;
  }
  return false;
}

bool parser::comma(){
  if(get(marker) == ','){
    marker++;
    consumeWhitespace();
    return true;
  }
  return false;
}

bool parser::semicolon(){
  if(get(marker) == ';'){
    marker++;
    consumeWhitespace();
    return true;
  }
  return false;
}

char parser::get(size_t index){
  if(index < str.size()){
    return str[index];
  }
  return (char)0;
}

void parser::consumeWhitespace(){
  while(isspace(get(marker)))
    marker++;
}
