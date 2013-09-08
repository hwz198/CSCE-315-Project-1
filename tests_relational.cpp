#include "Database.h"
#include <iostream>
#include <vector>
using namespace std;

bool test_relational();

int main(){
  cout << test_relational() << endl;
  return 0;
}

bool test_relational(){
  bool success = true;

  vector<Attribute> animals_columns;
  animals_columns.push_back(Attribute("Species", str));
  animals_columns.push_back(Attribute("Age", i));
  animals_columns.push_back(Attribute("Name", str));
  animals_columns.push_back(Attribute("Gender", str));
  animals_columns.push_back(Attribute("Weight", d));

  vector<Tuple> animals_rows;

  vector<string> spot;
  spot.push_back("Dog");
  spot.push_back("5");
  spot.push_back("Spot");
  spot.push_back("Male");
  spot.push_back("62.5");
  animals_rows.push_back(Tuple(spot));

  vector<string> socks;
  socks.push_back("Cat");
  socks.push_back("3");
  socks.push_back("Socks");
  socks.push_back("Female");
  socks.push_back("6.1");
  animals_rows.push_back(Tuple(socks));

  vector<string> mittens;
  mittens.push_back("Cat");
  mittens.push_back("11");
  mittens.push_back("Mittens");
  mittens.push_back("Male");
  mittens.push_back("8.3");
  animals_rows.push_back(Tuple(mittens));

  vector<string> fido;
  fido.push_back("Dog");
  fido.push_back("13");
  fido.push_back("Fido");
  fido.push_back("Female");
  fido.push_back("73.6");
  animals_rows.push_back(Tuple(fido));

  vector<string> pocky;
  pocky.push_back("Bird");
  pocky.push_back("2");
  pocky.push_back("Pocky");
  pocky.push_back("Male");
  pocky.push_back("2.9");
  animals_rows.push_back(Tuple(pocky));

  vector<string> bones;
  bones.push_back("Dog");
  bones.push_back("8");
  bones.push_back("Bones");
  bones.push_back("Male");
  bones.push_back("37.2");
  animals_rows.push_back(Tuple(bones));

  vector<Relation> r;
  Relation animals("Animals", animals_rows, animals_columns);
  r.push_back(animals);
  Database db(r);

  db.Show(db.getRelation(0).getName());
  cout << endl << endl;

//////////////////////////////////////////////////
///            BEGIN SELECTION TEST            ///
//////////////////////////////////////////////////
  //selection int
  {
  vector<Tuple> old_animals_rows;
  old_animals_rows.push_back(mittens);
  old_animals_rows.push_back(fido);
  Relation old_animals("Old Animals", old_animals_rows, animals_columns);
  if(!old_animals.equalContents(db.selection(db.getRelation(0), "old",
                                            "Age", g, Attribute("8", i)))){
    cerr << "Selection, greater, int, FAILED\n";
    success = false;
  }

  vector<Tuple> young_animals_rows;
  young_animals_rows.push_back(spot);
  young_animals_rows.push_back(socks);
  young_animals_rows.push_back(pocky);
  Relation young_animals("Young Animals", young_animals_rows, animals_columns);
  if(!young_animals.equalContents(db.selection(db.getRelation(0), "young",
                                              "Age", l, Attribute("8", i)))){
    cerr << "Selection, less, int, FAILED\n";
    success = false;
  }

  old_animals.addTuple(bones);
  if(!old_animals.equalContents(db.selection(db.getRelation(0), "old2",
                                             "Age", ge, Attribute("8", i)))){
    cerr << "Selection, greaterEqual, int, FAILED\n";
    success = false;
  }

  young_animals.addTuple(bones);
  if(!young_animals.equalContents(db.selection(db.getRelation(0), "young2",
                                               "Age", le, Attribute("8", i)))){
    cerr << "Selection, lessEqual, int, FAILED\n";
    success = false;
  }

  vector<Tuple> animals13_rows;
  animals13_rows.push_back(fido);
  Relation animals13("Animals 13", animals13_rows, animals_columns);
  if(!animals13.equalContents(db.selection(db.getRelation(0), "13",
                                           "Age", e, Attribute("13", i)))){
    cerr << "Selection, equal, int, FAILED\n";
    success = false;
  }

  Relation animals_not_13 = animals;
  animals_not_13.deleteTuple(fido);
  if(!animals_not_13.equalContents(db.selection(db.getRelation(0), "not13",
                                                "Age", ne, Attribute("13", i)))){
    cerr << "Selection, nequal, int, FAILED\n";
    success = false;
  }
  }

  {
  //selection double
  vector<Tuple> heavy_animals_rows;
  heavy_animals_rows.push_back(spot);
  heavy_animals_rows.push_back(fido);
  Relation heavy_animals("Heavy Animals", heavy_animals_rows, animals_columns);
  if(!heavy_animals.equalContents(db.selection(db.getRelation(0), "heavy",
                                               "Weight", g, Attribute("37.2", d)))){
    cerr << "Selection, greater, double, FAILED\n";
    success = false;
  }

  vector<Tuple> light_animals_rows;
  light_animals_rows.push_back(socks);
  light_animals_rows.push_back(mittens);
  light_animals_rows.push_back(pocky);
  Relation light_animals("Light Animals", light_animals_rows, animals_columns);
  if(!light_animals.equalContents(db.selection(db.getRelation(0), "light",
                                               "Weight", l, Attribute("37.2", d)))){
    cerr << "Selection, less, double, FAILED\n";
    success = false;
  }

  heavy_animals.addTuple(bones);
  if(!heavy_animals.equalContents(db.selection(db.getRelation(0), "heavy2",
                                               "Weight", ge, Attribute("37.2", d)))){
    cerr << "Selection, greater/equal, double, FAILED\n";
    success = false;
  }

  light_animals.addTuple(bones);
  if(!light_animals.equalContents(db.selection(db.getRelation(0), "light2",
                                               "Weight", le, Attribute("37.2", d)))){
    cerr << "Selection, less/equal, double, FAILED\n";
    success = false;
  }

  vector<Tuple> spotr_rows;
  spotr_rows.push_back(spot);
  Relation spotr("Spot", spotr_rows, animals_columns);
  if(!spotr.equalContents(db.selection(db.getRelation(0), "light2",
                                       "Weight", e, Attribute("62.5", d)))){
    cerr << "Selection, equal, double, FAILED\n";
    success = false;
  }

  Relation not_spotr = animals;
  not_spotr.deleteTuple(spot);
  if(!not_spotr.equalContents(db.selection(db.getRelation(0), "light2",
                                       "Weight", ne, Attribute("62.5", d)))){
    cerr << "Selection, nequal, double, FAILED\n";
    success = false;
  }
  }

  {
  //string
  vector<Tuple> dogs_rows;
  dogs_rows.push_back(spot);
  dogs_rows.push_back(fido);
  dogs_rows.push_back(bones);
  Relation dogs("Dogs", dogs_rows, animals_columns);
  if(!dogs.equalContents(db.selection(db.getRelation(0), "dogs",
                                      "Species", e, Attribute("Dog", str)))){
    cerr << "Selection, equal, string, FAILED\n";
    success = false;
  }

  Relation not_cats = dogs;
  not_cats.deleteTuple(bones); //equalContents is order sensitive
  not_cats.addTuple(pocky);
  not_cats.addTuple(bones);
  if(!not_cats.equalContents(db.selection(db.getRelation(0), "dogs",
                                      "Species", ne, Attribute("Cat", str)))){
    cerr << "Selection, nequal, string, FAILED\n";
    success = false;
  }
  }
//////////////////////////////////////////////////
///              END SELECTION TEST            ///
//////////////////////////////////////////////////

  return success;
}
