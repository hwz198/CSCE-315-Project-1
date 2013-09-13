#include "parser.h"
#include<iostream>
using namespace std;

int main(){
  parser P;
  while(true){
    string str; //= "high_hitters <- select (homeruns >= 40) baseball_players;";
    getline(cin, str);
    cout << P.parse(str) << endl;
    vector<Token> tokens = P.tokens;
    for(unsigned int i = 0; i < tokens.size(); ++i){
      cout << TokenStrings[tokens[i].type()] << ' ';
    }
    cout << endl;
  }
  return 0;
}
