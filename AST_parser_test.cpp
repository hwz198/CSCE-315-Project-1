#include "AST_Parser.h"
#include "Parser.h"
#include<iostream>
using namespace std;

int main(){
  Database db;
  Database views;
  vector<Tuple> tups;
  vector<Attribute> attrs;
  vector<size_t> keys;
  db.addRelation(Relation("hello", tups, attrs, keys));
  AST_Parser A(&db, &views);
  Parser P;
  while(true){
    bool parsed = 0;
    string str; //= "high_hitters <- select (homeruns >= 40) baseball_players;";
    getline(cin, str);
    AST* tree = P.parse(str);
    if(tree != NULL){
      parsed = A.parse(tree);
      tree->print(std::cout);
    }
    cout << endl;
    cout << parsed << endl;
    /*
    vector<Token> tokens = P.tokens;
    for(unsigned int i = 0; i < tokens.size(); ++i){
      cout << TokenStrings[tokens[i].type()] << ' ';
    }
    cout << endl;
    */
  }
  return 0;
}
