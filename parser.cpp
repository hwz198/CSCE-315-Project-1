#include "parser.h"
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

const string TokenStrings[] = {"null", "identifier", "lparen", "rparen",
                               "comma", "assign", "space", "plus", "minus",
                               "asterisk", "semicolon", "g", "l", "e", "ge",
                               "le", "ne", "project", "rename","open", "close",
                               "write", "exit", "show", "create", "update",
                               "insert", "delete", "varchar", "integer",
                               "table", "primary", "key", "set", "where",
                               "into", "values", "from", "lit_integer",
                               "literal"};

void parser::lex(string input){
  tokens.clear();
  str = input;
  t_index = 0;
  while(t_index < str.size()){
    if(isspace(get(t_index))){
      //tokens.push_back(Token(t_index, str.substr(t_index, 1), _space));
      t_index++;
      continue;
    }
    if(get(t_index) == '('){
      tokens.push_back(Token(t_index, str.substr(t_index, 1), _lparen));
      t_index++;
      continue;
    }
    if(get(t_index) == ')'){
      tokens.push_back(Token(t_index, str.substr(t_index, 1), _rparen));
      t_index++;
      continue;
    }
    if(get(t_index) == ','){
      tokens.push_back(Token(t_index, str.substr(t_index, 1), _comma));
      t_index++;
      continue;
    }
    if(get(t_index) == '('){
      tokens.push_back(Token(t_index, str.substr(t_index, 1), _lparen));
      t_index++;
      continue;
    }
    if(get(t_index) == '<' && get(t_index+1) == '-'){
      tokens.push_back(Token(t_index, str.substr(t_index, 2), _assign));
      t_index += 2;
      continue;
    }
    if(get(t_index) == '+'){
      tokens.push_back(Token(t_index, str.substr(t_index, 1), _plus));
      t_index++;
      continue;
    }
    if(get(t_index) == '-' && !isdigit(get(t_index+1))){
      tokens.push_back(Token(t_index, str.substr(t_index, 1), _minus));
      t_index++;
      continue;
    }
    if(get(t_index) == '*'){
      tokens.push_back(Token(t_index, str.substr(t_index, 1), _asterisk));
      t_index++;
      continue;
    }
    if(get(t_index) == ';'){
      tokens.push_back(Token(t_index, str.substr(t_index, 1), _semicolon));
      t_index++;
      continue;
    }
    if(get(t_index) == '>'){
      if(get(t_index+1) == '='){
        tokens.push_back(Token(t_index, str.substr(t_index, 2), _ge));
        t_index += 2;
        continue;
      } else {
        tokens.push_back(Token(t_index, str.substr(t_index, 1), _g));
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
        tokens.push_back(Token(t_index, str.substr(t_index, 1), _l));
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
    if(str.substr(t_index, 7) == "project"
       /* also check that keyword isnt part of identifier
         and thus isnt followed by alpha or digit */
       && !((get(t_index+7) >= 'a' && get(t_index+7) <= 'z')
            || (get(t_index+7) >= 'A' && get(t_index+7) <= 'Z')
            || (get(t_index+7) >= '0' && get(t_index+7) <= '9')
            || (get(t_index+7) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _project));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 6) == "rename"
       && !((get(t_index+6) >= 'a' && get(t_index+6) <= 'z')
            || (get(t_index+6) >= 'A' && get(t_index+6) <= 'Z')
            || (get(t_index+6) >= '0' && get(t_index+6) <= '9')
            || (get(t_index+6) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _rename));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 4) == "OPEN"
       && !((get(t_index+4) >= 'a' && get(t_index+4) <= 'z')
            || (get(t_index+4) >= 'A' && get(t_index+4) <= 'Z')
            || (get(t_index+4) >= '0' && get(t_index+4) <= '9')
            || (get(t_index+4) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _open));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 5) == "CLOSE"
       && !((get(t_index+5) >= 'a' && get(t_index+5) <= 'z')
            || (get(t_index+5) >= 'A' && get(t_index+5) <= 'Z')
            || (get(t_index+5) >= '0' && get(t_index+5) <= '9')
            || (get(t_index+5) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _close));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 5) == "WRTIE"
       && !((get(t_index+5) >= 'a' && get(t_index+5) <= 'z')
            || (get(t_index+5) >= 'A' && get(t_index+5) <= 'Z')
            || (get(t_index+5) >= '0' && get(t_index+5) <= '9')
            || (get(t_index+5) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _write));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 4) == "EXIT"
       && !((get(t_index+4) >= 'a' && get(t_index+4) <= 'z')
            || (get(t_index+4) >= 'A' && get(t_index+4) <= 'Z')
            || (get(t_index+4) >= '0' && get(t_index+4) <= '9')
            || (get(t_index+4) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _exit));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 4) == "SHOW"
       && !((get(t_index+4) >= 'a' && get(t_index+4) <= 'z')
            || (get(t_index+4) >= 'A' && get(t_index+4) <= 'Z')
            || (get(t_index+4) >= '0' && get(t_index+4) <= '9')
            || (get(t_index+4) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _show));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 6) == "CREATE"
       && !((get(t_index+6) >= 'a' && get(t_index+6) <= 'z')
            || (get(t_index+6) >= 'A' && get(t_index+6) <= 'Z')
            || (get(t_index+6) >= '0' && get(t_index+6) <= '9')
            || (get(t_index+6) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _create));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "UPDATE"
       && !((get(t_index+6) >= 'a' && get(t_index+6) <= 'z')
            || (get(t_index+6) >= 'A' && get(t_index+6) <= 'Z')
            || (get(t_index+6) >= '0' && get(t_index+6) <= '9')
            || (get(t_index+6) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _update));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "INSERT"
       && !((get(t_index+6) >= 'a' && get(t_index+6) <= 'z')
            || (get(t_index+6) >= 'A' && get(t_index+6) <= 'Z')
            || (get(t_index+6) >= '0' && get(t_index+6) <= '9')
            || (get(t_index+6) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _update));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "DELETE"
       && !((get(t_index+6) >= 'a' && get(t_index+6) <= 'z')
            || (get(t_index+6) >= 'A' && get(t_index+6) <= 'Z')
            || (get(t_index+6) >= '0' && get(t_index+6) <= '9')
            || (get(t_index+6) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _delete));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 7) == "VARCHAR"
       && !((get(t_index+7) >= 'a' && get(t_index+7) <= 'z')
            || (get(t_index+7) >= 'A' && get(t_index+7) <= 'Z')
            || (get(t_index+7) >= '0' && get(t_index+7) <= '9')
            || (get(t_index+7) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _varchar));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 7) == "INTEGER"
       && !((get(t_index+7) >= 'a' && get(t_index+7) <= 'z')
            || (get(t_index+7) >= 'A' && get(t_index+7) <= 'Z')
            || (get(t_index+7) >= '0' && get(t_index+7) <= '9')
            || (get(t_index+7) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _integer));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 5) == "TABLE"
       && !((get(t_index+5) >= 'a' && get(t_index+5) <= 'z')
            || (get(t_index+5) >= 'A' && get(t_index+5) <= 'Z')
            || (get(t_index+5) >= '0' && get(t_index+5) <= '9')
            || (get(t_index+5) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _table));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 7) == "PRIMARY"
       && !((get(t_index+7) >= 'a' && get(t_index+7) <= 'z')
            || (get(t_index+7) >= 'A' && get(t_index+7) <= 'Z')
            || (get(t_index+7) >= '0' && get(t_index+7) <= '9')
            || (get(t_index+7) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _primary));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 3) == "KEY"
       && !((get(t_index+3) >= 'a' && get(t_index+3) <= 'z')
            || (get(t_index+3) >= 'A' && get(t_index+3) <= 'Z')
            || (get(t_index+3) >= '0' && get(t_index+3) <= '9')
            || (get(t_index+3) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 3), _key));
      t_index += 3;
      continue;
    }
    if(str.substr(t_index, 3) == "SET"
       && !((get(t_index+3) >= 'a' && get(t_index+3) <= 'z')
            || (get(t_index+3) >= 'A' && get(t_index+3) <= 'Z')
            || (get(t_index+3) >= '0' && get(t_index+3) <= '9')
            || (get(t_index+3) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 3), _set));
      t_index += 3;
      continue;
    }
    if(str.substr(t_index, 5) == "WHERE"
       && !((get(t_index+5) >= 'a' && get(t_index+5) <= 'z')
            || (get(t_index+5) >= 'A' && get(t_index+5) <= 'Z')
            || (get(t_index+5) >= '0' && get(t_index+5) <= '9')
            || (get(t_index+5) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _where));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 4) == "INTO"
       && !((get(t_index+4) >= 'a' && get(t_index+4) <= 'z')
            || (get(t_index+4) >= 'A' && get(t_index+4) <= 'Z')
            || (get(t_index+4) >= '0' && get(t_index+4) <= '9')
            || (get(t_index+4) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _into));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 6) == "VALUES"
       && !((get(t_index+6) >= 'a' && get(t_index+6) <= 'z')
            || (get(t_index+6) >= 'A' && get(t_index+6) <= 'Z')
            || (get(t_index+6) >= '0' && get(t_index+6) <= '9')
            || (get(t_index+6) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _values));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 4) == "FROM"
       && !((get(t_index+4) >= 'a' && get(t_index+4) <= 'z')
            || (get(t_index+4) >= 'A' && get(t_index+4) <= 'Z')
            || (get(t_index+4) >= '0' && get(t_index+4) <= '9')
            || (get(t_index+4) == '_'))) {
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _from));
      t_index += 4;
      continue;
    }
    if((get(t_index) >= 'a' && get(t_index) <= 'z')
       || (get(t_index) >= 'A' && get(t_index) <= 'Z')){
      size_t first_index = t_index;
      t_index++;
      while((get(t_index) >= 'a' && get(t_index) <= 'z')
            || (get(t_index) >= 'A' && get(t_index) <= 'Z')
            || (get(t_index) >= '0' && get(t_index) <= '9')
            || (get(t_index) == '_')){
        /*
          cout << t_index << endl;
          cout << get(t_index) << endl;
        */
        t_index++;
      }
      tokens.push_back(Token(first_index,
                             str.substr(first_index, t_index - first_index),
                             _identifier));
      continue;
    }
    if(get(t_index) == '\"'){
      size_t first_index = t_index;
      t_index++;
      while(get(t_index) != '\"'){
        t_index++;
      }
      t_index++; //catch quote that escaped while loop
      tokens.push_back(Token(first_index,
                             str.substr(first_index, t_index - first_index),
                             _literal));
      continue;
    }
    if((get(t_index) >= '0' && get(t_index) <= '9')){
      size_t first_index = t_index;
      t_index++;
      while(get(t_index) >= '0' && get(t_index) <= '9'){
        t_index++;
      }
      tokens.push_back(Token(first_index,
                             str.substr(first_index, t_index - first_index),
                             _lit_integer));
      continue;
    }
    if((get(t_index) >= '0' && get(t_index) <= '9') || (get(t_index) == '-')){
      size_t first_index = t_index;
      t_index++;
      while(get(t_index) >= '0' && get(t_index) <= '9'){
        t_index++;
      }
      tokens.push_back(Token(first_index,
                             str.substr(first_index, t_index - first_index),
                             _literal));
      continue;
    }
    char t = 'a'; //gdb breakpoint
    /*
      cout << t_index << endl;
      cout << get(t_index) << endl;
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
