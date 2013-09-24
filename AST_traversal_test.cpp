#include "AST_Traversal.h"
#include "AST_Assembly.h"
#include<iostream>
using namespace std;

int main(){
  //construct initial Relation animal for testing
  vector<Attribute> animals_columns;
  animals_columns.push_back(Attribute("Species", str));
  animals_columns.push_back(Attribute("Age", in));
  animals_columns.push_back(Attribute("Name", str));
  animals_columns.push_back(Attribute("Gender", str));

  vector<size_t> keys;
  keys.push_back(2);

  vector<Tuple> animals_rows;

  vector<string> spot;
  spot.push_back("Dog");
  spot.push_back("5");
  spot.push_back("Spot");
  spot.push_back("Male");
  animals_rows.push_back(Tuple(spot));

  vector<string> socks;
  socks.push_back("Cat");
  socks.push_back("3");
  socks.push_back("Socks");
  socks.push_back("Female");
  animals_rows.push_back(Tuple(socks));

  vector<string> mittens;
  mittens.push_back("Cat");
  mittens.push_back("11");
  mittens.push_back("Mittens");
  mittens.push_back("Male");
  animals_rows.push_back(Tuple(mittens));

  vector<string> fido;
  fido.push_back("Dog");
  fido.push_back("13");
  fido.push_back("Fido");
  fido.push_back("Female");
  animals_rows.push_back(Tuple(fido));

  vector<string> pocky;
  pocky.push_back("Bird");
  pocky.push_back("2");
  pocky.push_back("Pocky");
  pocky.push_back("Male");
  animals_rows.push_back(Tuple(pocky));

  vector<string> bones;
  bones.push_back("Dog");
  bones.push_back("8");
  bones.push_back("Bones");
  bones.push_back("Male");
  animals_rows.push_back(Tuple(bones));

  //make new Datbase and add animals relation
  vector<Relation> r;
  Relation animals("Animals", animals_rows, animals_columns, keys);
  r.push_back(animals);
  Database db(r);

  Database views;
  vector<Tuple> tups;
  vector<Attribute> attrs;
  vector<size_t> keys2;
  db.addRelation(Relation("hello", tups, attrs, keys2));
  AST_Traversal A(&db, &views);
  AST_Assembly P;
  string str; //= "high_hitters <- select (homeruns >= 40) baseball_players;";
  while(getline(cin, str)){
    bool parsed = 0;
    AST* tree = P.assemble(str);
    if(tree != NULL){
      parsed = A.traverse(tree);
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
