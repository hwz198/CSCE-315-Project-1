#include "Parser.h"
#include<iostream>
using namespace std;

int main(){
  Parser P;
  string str; //= "high_hitters <- select (homeruns >= 40) baseball_players;";
  while(getline(cin, str)){
    if(str.empty())
      continue;
    cout << "$$ " << str << endl;
    cout << P.parse(str) << endl << endl;
  }
  return 0;
}
