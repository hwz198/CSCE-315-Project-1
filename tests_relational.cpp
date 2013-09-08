#include "Database.h"
#include <iostream>
#include <vector>
using namespace std;

void test_relational();

int main(){
  test_relational();
  return 0;
}

void test_relational(){
  bool success = true;
  string test_output;

  vector<Attribute> animals_columns;
  animals_columns.push_back(Attribute("Species", str));
  animals_columns.push_back(Attribute("Age", i));
  animals_columns.push_back(Attribute("Name", str));
  animals_columns.push_back(Attribute("Gender", str));
  animals_columns.push_back(Attribute("Weight", d));

  vector<size_t> keys;
  keys.push_back(2);

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
  Relation animals("Animals", animals_rows, animals_columns, keys);
  r.push_back(animals);
  Database db(r);

  vector<string> jerry;
  jerry.push_back("Bird");
  jerry.push_back("1");
  jerry.push_back("Jerry");
  jerry.push_back("Male");
  jerry.push_back("1.4");

  vector<string> bowser;
  bowser.push_back("Dog");
  bowser.push_back("5");
  bowser.push_back("Bowser");
  bowser.push_back("Male");
  bowser.push_back("43.1");

//////////////////////////////////////////////////
///            BEGIN SELECTION TEST            ///
//////////////////////////////////////////////////
  if(!db.selection(Relation(), "empty", "Age", g,
                   Attribute("8", i)).empty()){
    cerr << "Selection, empty Relation FAILED\n";
    success = false;
  }
  //test not found
  if(!db.selection(db.getRelation(0), "broke", "Owner",
                   e, Attribute("Sam", str)).empty()){
    cerr << "Selection, attribute not found, FAILED\n";
    success = false;
  }
  //incompatiable dataTypes
  //selection int
  if(!db.selection(db.getRelation(0), "broke", "Age",
                   e, Attribute("eight", str)).empty()){
    cerr << "Selection, attribute not found, FAILED\n";
    success = false;
  }
  {
  vector<Tuple> old_animals_rows;
  old_animals_rows.push_back(mittens);
  old_animals_rows.push_back(fido);
  Relation old_animals("Old Animals", old_animals_rows, animals_columns, keys);
  if(!old_animals.equalContents(db.selection(db.getRelation(0), "old",
                                            "Age", g, Attribute("8", i)))){
    cerr << "Selection, greater, int, FAILED\n";
    success = false;
  }

  vector<Tuple> young_animals_rows;
  young_animals_rows.push_back(spot);
  young_animals_rows.push_back(socks);
  young_animals_rows.push_back(pocky);
  Relation young_animals("Young Animals", young_animals_rows, animals_columns, keys);
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
  Relation animals13("Animals 13", animals13_rows, animals_columns, keys);
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
  Relation heavy_animals("Heavy Animals", heavy_animals_rows, animals_columns, keys);
  if(!heavy_animals.equalContents(db.selection(db.getRelation(0), "heavy",
                                               "Weight", g, Attribute("37.2", d)))){
    cerr << "Selection, greater, double, FAILED\n";
    success = false;
  }

  vector<Tuple> light_animals_rows;
  light_animals_rows.push_back(socks);
  light_animals_rows.push_back(mittens);
  light_animals_rows.push_back(pocky);
  Relation light_animals("Light Animals", light_animals_rows, animals_columns, keys);
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
  Relation spotr("Spot", spotr_rows, animals_columns, keys);
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
  Relation dogs("Dogs", dogs_rows, animals_columns, keys);
  if(!dogs.equalContents(db.selection(db.getRelation(0), "dogs",
                                      "Species", e, Attribute("Dog", str)))){
    cerr << "Selection, equal, string, FAILED\n";
    success = false;
  }

  Relation not_cats = dogs;
  not_cats.addTuple(pocky);
  if(!not_cats.equalContents(db.selection(db.getRelation(0), "dogs",
                                      "Species", ne, Attribute("Cat", str)))){
    cerr << "Selection, nequal, string, FAILED\n";
    success = false;
  }
  }
//////////////////////////////////////////////////
///              END SELECTION TEST            ///
//////////////////////////////////////////////////

  if(success){
    test_output += " -- Selection Tests PASSED -- \n";
  } else {
    test_output += " -- Selection Tests FAILED -- \n";
    success = true;
  }

//////////////////////////////////////////////////
///            BEGIN PROJECTION TEST           ///
//////////////////////////////////////////////////
  {
  vector<string> attrib_vals;
  if(!db.projection(db.getRelation(0), "empty", attrib_vals).empty()){
    cerr << "Projection, empty attrib_vals test FAILED\n";
    success = false;
  }

  attrib_vals.push_back("Species");
  attrib_vals.push_back("Name");
  if(!db.projection(Relation(), "empty", attrib_vals).empty()){
    cerr << "Projection, empty relation FAILED\n";
    success = false;
  }

  vector<Tuple> proj_animals_rows;
  vector<string> pspot;
  pspot.push_back("Dog");
  pspot.push_back("Spot");
  proj_animals_rows.push_back(Tuple(pspot));

  vector<string> psockss;
  psockss.push_back("Cat");
  psockss.push_back("Socks");
  proj_animals_rows.push_back(Tuple(psockss));

  vector<string> pmittens;
  pmittens.push_back("Cat");
  pmittens.push_back("Mittens");
  proj_animals_rows.push_back(Tuple(pmittens));

  vector<string> pfido;
  pfido.push_back("Dog");
  pfido.push_back("Fido");
  proj_animals_rows.push_back(Tuple(pfido));

  vector<string> ppocky;
  ppocky.push_back("Bird");
  ppocky.push_back("Pocky");
  proj_animals_rows.push_back(Tuple(ppocky));

  vector<string> pbones;
  pbones.push_back("Dog");
  pbones.push_back("Bones");
  proj_animals_rows.push_back(Tuple(pbones));

  vector<Attribute> attribs;
  attribs.push_back(Attribute("Species", str));
  attribs.push_back(Attribute("Name", str));
  vector<size_t> proj_keys;
  proj_keys.push_back(1);
  Relation proj_animals("Projected Animals", proj_animals_rows, attribs, proj_keys);
  if(!proj_animals.equalContents(db.projection(db.getRelation(0), "SpecName",
                                               attrib_vals))){
    cerr << "Projection FAILED\n";
    success = false;
  }
  }
//////////////////////////////////////////////////
///             END PROJECTION TEST            ///
//////////////////////////////////////////////////

  if(success){
    test_output += " -- Projection Tests PASSED -- \n";
  } else {
    test_output += " -- Projection Tests FAILED -- \n";
    success = true;
  }

//////////////////////////////////////////////////
///            BEGIN RENAMING TEST             ///
//////////////////////////////////////////////////
  {
  vector<string> attrib_vals;
  if(!db.rename(db.getRelation(0), "empty", attrib_vals).empty()){
    cerr << "Projection, empty attrib_vals test FAILED\n";
    success = false;
  }

  attrib_vals.push_back("S");
  attrib_vals.push_back("A");
  if(!db.rename(db.getRelation(0), "empty", attrib_vals).empty()){
    cerr << "Projection, wrong attrib_vals size FAILED\n";
    success = false;
  }

  attrib_vals.push_back("N");
  attrib_vals.push_back("G");
  attrib_vals.push_back("W");
  if(!db.rename(Relation(), "empty", attrib_vals).empty()){
    cerr << "Projection, empty Relation FAILED\n";
    success = false;
  }

  vector<Attribute> attrib_cols;
  attrib_cols.push_back(Attribute("S", str));
  attrib_cols.push_back(Attribute("A", i));
  attrib_cols.push_back(Attribute("N", str));
  attrib_cols.push_back(Attribute("G", str));
  attrib_cols.push_back(Attribute("W", d));
  Relation renamed("Renamed Animals", animals_rows, attrib_cols, keys);
  if(!renamed.equalContents(db.rename(db.getRelation(0), "rename", attrib_vals))){
    cerr << "Renaming FAILED\n";
    success = false;
  }
  }
//////////////////////////////////////////////////
///              END RENAMING TEST             ///
//////////////////////////////////////////////////

  if(success){
    test_output += " -- Renaming Tests PASSED -- \n";
  } else {
    test_output += " -- Renaming Tests FAILED -- \n";
    success = true;
  }

//////////////////////////////////////////////////
///              BEGIN UNION TEST              ///
//////////////////////////////////////////////////
  {
  if(!db.relation_union(Relation(), db.getRelation(0)).empty()){
    cerr << "Union, empty relation FAILED\n";
    success = false;
  }

  if(!db.relation_union(db.getRelation(0), Relation()).empty()){
    cerr << "Union, empty relation FAILED\n";
    success = false;
  }

  vector<Attribute> union_cols;
  union_cols.push_back(Attribute("Species", str));
  union_cols.push_back(Attribute("Name", str));

  vector<Tuple> union_rows;
  vector<string> uspot;
  uspot.push_back("Dog");
  uspot.push_back("Spot");
  union_rows.push_back(Tuple(uspot));
  vector<string> usocks;
  usocks.push_back("Cat");
  usocks.push_back("Socks");
  union_rows.push_back(Tuple(usocks));

  vector<size_t> ukeys;
  ukeys.push_back(0);

  Relation inc_union("Union", union_rows, union_cols, ukeys);

  if(!db.relation_union(db.getRelation(0), inc_union).empty()){
    cerr << "Union, non compatible relations FAILED\n";
    success = false;
  }

  Relation ani_union = db.getRelation(0);
  ani_union.addTuple(Tuple(jerry));

  db.getRelationRef(0)->addTuple(Tuple(bowser));
  Relation union_result = ani_union;
  ani_union.addTuple(Tuple(bowser));
  if(!ani_union.equalContents(db.relation_union(ani_union, db.getRelation(0)))){
    cerr << "Union FAILED\n";
    success = false;
  }
  }
//////////////////////////////////////////////////
///              END UNION TEST                ///
//////////////////////////////////////////////////

  if(success){
    test_output += " -- Union Tests PASSED -- \n";
  } else {
    test_output += " -- Union Tests FAILED -- \n";
    success = true;
  }

//////////////////////////////////////////////////
///            BEGIN DIFFERENCE TEST           ///
//////////////////////////////////////////////////
  {
  if(!db.relation_difference(Relation(), db.getRelation(0)).empty()){
    cerr << "Difference, empty relation FAILED\n";
    success = false;
  }

  if(!db.relation_difference(db.getRelation(0), Relation()).empty()){
    cerr << "Difference, empty relation FAILED\n";
    success = false;
  }

  vector<Attribute> difference_cols;
  difference_cols.push_back(Attribute("Species", str));
  difference_cols.push_back(Attribute("Name", str));

  vector<Tuple> difference_rows;
  vector<string> uspot;
  uspot.push_back("Dog");
  uspot.push_back("Spot");
  difference_rows.push_back(Tuple(uspot));
  vector<string> usocks;
  usocks.push_back("Cat");
  usocks.push_back("Socks");
  difference_rows.push_back(Tuple(usocks));

  vector<size_t> ukeys;
  ukeys.push_back(0);

  Relation inc_difference("Difference", difference_rows, difference_cols, ukeys);

  if(!db.relation_difference(db.getRelation(0), inc_difference).empty()){
    cerr << "Difference, non compatible relations FAILED\n";
    success = false;
  }

  vector<Tuple> ani_diff_rows;
  ani_diff_rows.push_back(bones);
  ani_diff_rows.push_back(fido);
  ani_diff_rows.push_back(mittens);
  Relation ani_diff("Difference", ani_diff_rows, animals_columns, keys);

  vector<Tuple> diff_result_rows;
  diff_result_rows.push_back(spot);
  diff_result_rows.push_back(socks);
  diff_result_rows.push_back(pocky);
  diff_result_rows.push_back(bowser);
  Relation diff_result("Difference Result", diff_result_rows, animals_columns, keys);

  if(!diff_result.equalContents(db.relation_difference(db.getRelation(0), ani_diff))){
    cerr << "Difference FAILED\n";
    success = false;
  }
  }
//////////////////////////////////////////////////
///           END DIFFERENCE TEST              ///
//////////////////////////////////////////////////

  if(success){
    test_output += " -- Difference Tests PASSED -- \n";
  } else {
    test_output += " -- Difference Tests FAILED -- \n";
    success = true;
  }

//////////////////////////////////////////////////
///         BEGIN CROSS PRODUCT TEST           ///
//////////////////////////////////////////////////
  {
  if(!db.cross_product(Relation(), db.getRelation(0)).empty()){
    cerr << "Cross product, empty realtion FAILED\n";
    success = false;
  }

  if(!db.cross_product(db.getRelation(0), Relation()).empty()){
    cerr << "Cross product, empty realtion FAILED\n";
    success = false;
  }

  vector<Attribute> food_cols;
  food_cols.push_back(Attribute("Brand", str));
  food_cols.push_back(Attribute("Price", d));

  vector<Tuple> food_rows;
  vector<string> purina;
  purina.push_back("Purina");
  purina.push_back("8.5");
  food_rows.push_back(Tuple(purina));

  vector<string> chow;
  chow.push_back("Chow");
  chow.push_back("7");
  food_rows.push_back(Tuple(chow));

  vector<size_t> food_keys;
  food_keys.push_back(0);

  Relation food("Food", food_rows, food_cols, food_keys);


  vector<Attribute> cross_cols = animals_columns;
  cross_cols.push_back(Attribute("Brand", str));
  cross_cols.push_back(Attribute("Price", d));

  vector<Tuple> cross_rows;
  vector<string> spot1 = spot;
  spot1.push_back("Purina");
  spot1.push_back("8.5");
  cross_rows.push_back(Tuple(spot1));

  vector<string> spot2 = spot;
  spot2.push_back("Chow");
  spot2.push_back("7");
  cross_rows.push_back(Tuple(spot2));

  vector<string> socks1 = socks;
  socks1.push_back("Purina");
  socks1.push_back("8.5");
  cross_rows.push_back(Tuple(socks1));

  vector<string> socks2 = socks;
  socks2.push_back("Chow");
  socks2.push_back("7");
  cross_rows.push_back(Tuple(socks2));

  vector<string> mittens1 = mittens;
  mittens1.push_back("Purina");
  mittens1.push_back("8.5");
  cross_rows.push_back(Tuple(mittens1));

  vector<string> mittens2 = mittens;
  mittens2.push_back("Chow");
  mittens2.push_back("7");
  cross_rows.push_back(Tuple(mittens2));

  vector<string> fido1 = fido;
  fido1.push_back("Purina");
  fido1.push_back("8.5");
  cross_rows.push_back(Tuple(fido1));

  vector<string> fido2 = fido;
  fido2.push_back("Chow");
  fido2.push_back("7");
  cross_rows.push_back(Tuple(fido2));

  vector<string> pocky1 = pocky;
  pocky1.push_back("Purina");
  pocky1.push_back("8.5");
  cross_rows.push_back(Tuple(pocky1));

  vector<string> pocky2 = pocky;
  pocky2.push_back("Chow");
  pocky2.push_back("7");
  cross_rows.push_back(Tuple(pocky2));

  vector<string> bones1 = bones;
  bones1.push_back("Purina");
  bones1.push_back("8.5");
  cross_rows.push_back(Tuple(bones1));

  vector<string> bones2 = bones;
  bones2.push_back("Chow");
  bones2.push_back("7");
  cross_rows.push_back(Tuple(bones2));

  Relation cross("Cross", cross_rows, cross_cols, keys);

  if(!cross.equalContents(db.cross_product(animals, food))){
    cerr << "Cross product FAILED\n";
    success = false;
  }
  }
//////////////////////////////////////////////////
///           END CROSS PRODUCT TEST           ///
//////////////////////////////////////////////////

  if(success){
    test_output += " -- Cross Product Tests PASSED -- \n";
  } else {
    test_output += " -- Cross Product Tests FAILED -- \n";
    success = true;
  }

  cout << endl << test_output << endl;
}
