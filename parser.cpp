#include "parser.h"
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

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
