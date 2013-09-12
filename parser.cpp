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
    if(get(t_index) == '-'){
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
    if(str.substr(t_index, 7) == "project" && isspace(get(t_index+7))){
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _project));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 6) == "rename" && isspace(get(t_index+6))){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _rename));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 4) == "OPEN" && isspace(get(t_index+4))){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _open));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 5) == "CLOSE" && isspace(get(t_index+5))){
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _close));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 5) == "WRTIE" && isspace(get(t_index+5))){
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _write));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 4) == "EXIT" && isspace(get(t_index+4))){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _exit));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 4) == "SHOW" && isspace(get(t_index+4))){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _show));
      t_index += 4;
      continue;
    }
    if(str.substr(t_index, 6) == "CREATE" && isspace(get(t_index+6))){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _create));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "UPDATE" && isspace(get(t_index+6))){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _update));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "INSERT" && isspace(get(t_index+6))){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _update));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 6) == "DELETE" && isspace(get(t_index+6))){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _delete));
      t_index += 6;
      continue;
    }
    if(str.substr(t_index, 7) == "VARCHAR" && isspace(get(t_index+7))){
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _varchar));
      t_index += 7;
      continue;
    }
    if(str.substr(t_index, 5) == "TABLE" && isspace(get(t_index+5))){
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _table));
      t_index += 5;
      continue;
    }
    if(str.substr(t_index, 7) == "PRIMARY" && isspace(get(t_index+7))){
      tokens.push_back(Token(t_index, str.substr(t_index, 7), _primary));
      t_index += 7;
      continue;
    }
      if(str.substr(t_index, 3) == "KEY" && isspace(get(t_index+3))){
      tokens.push_back(Token(t_index, str.substr(t_index, 3), _key));
      t_index += 3;
      continue;
    }
      if(str.substr(t_index, 3) == "SET" && isspace(get(t_index+3))){
      tokens.push_back(Token(t_index, str.substr(t_index, 3), _set));
      t_index += 3;
      continue;
    }
      if(str.substr(t_index, 5) == "WHERE" && isspace(get(t_index+5))){
      tokens.push_back(Token(t_index, str.substr(t_index, 5), _where));
      t_index += 5;
      continue;
    }
      if(str.substr(t_index, 4) == "INTO" && isspace(get(t_index+4))){
      tokens.push_back(Token(t_index, str.substr(t_index, 4), _into));
      t_index += 4;
      continue;
    }
      if(str.substr(t_index, 6) == "VALUES" && isspace(get(t_index+6))){
      tokens.push_back(Token(t_index, str.substr(t_index, 6), _values));
      t_index += 6;
      continue;
    }
      if(str.substr(t_index, 4) == "FROM" && isspace(get(t_index+4))){
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
    if(get(t_index) >= '0' && get(t_index) <= '9'){
      size_t first_index = t_index;
      t_index++;
      while(get(t_index) >= '0' && get(t_index) <= '9'){
        t_index++;
      }
      tokens.push_back(Token(first_index,
                             str.substr(first_index, t_index - first_index),
                             _integer));
      continue;
    }
    char t = 'a';
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
