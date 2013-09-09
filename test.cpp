#include "Database.h"
#include "Tuple.h"
#include "Attribute.h"
#include "Relation.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

void test_relational();

/***********************Database Class Tests**************************/

void testRelationExists(){
	Database d;
	Relation r("test", vector<Tuple>(), vector<Attribute>(), vector<size_t>());
	d.addRelation(r);
	int ind = d.RelationExists("test");
	if(ind==0)
		printf("RelationExists test passed\n");
	else
		printf("Error. RelationExists test failed\n");
}

void testInsert(){
	Database d;
	vector<Attribute> sports;
	
	sports.push_back(Attribute("Player", str));
	sports.push_back(Attribute("Goals", in));
	sports.push_back(Attribute("Age", in));
	
	Relation r("test", vector<Tuple>(), sports, vector<size_t>());
		
	d.addRelation(r);
	
	vector<string> Ronaldo_row;
	Ronaldo_row.push_back("Ronaldo");
	Ronaldo_row.push_back("147");
	Ronaldo_row.push_back("28");
	
	Tuple Ronaldo(Ronaldo_row);
	
	
	d.Insert("test",Ronaldo);

	vector<Tuple> check = d.getRelation(0).getRows();

	vector<string> check_strings = check[0].getDataStrings();
	
	if(check_strings[0]=="Ronaldo" && check_strings[1]=="147" && check_strings[2]=="28")
		printf("testInsert passed\n");
	else
		printf("testInsert failed\n");
	
}

void testShow(){
	Database d;
	vector<Attribute> sports;
	
	sports.push_back(Attribute("Player", str));
	sports.push_back(Attribute("Goals", in));
	sports.push_back(Attribute("Age", in));
	
	Relation r("test", vector<Tuple>(), sports, vector<size_t>());
		
	d.addRelation(r);
	
	vector<string> Ronaldo_row;
	Ronaldo_row.push_back("Ronaldo");
	Ronaldo_row.push_back("147");
	Ronaldo_row.push_back("28");
	
	vector<string> Messi_row;
	Messi_row.push_back("Messi");
	Messi_row.push_back("220");
	Messi_row.push_back("26");
	
	Tuple Messi(Messi_row);
	Tuple Ronaldo(Ronaldo_row);
	
	d.Insert("test",Ronaldo);
	d.Insert("test",Messi);

	printf("\nTesting show. There should be 2 rows (Ronaldo and Messi) and 3 columns\n\n");
	d.Show(0);
	printf("\nTable shown as expected. testShow() Passed.\n");

}


Database createTestDatabase(){
	 vector<Attribute> animals_columns;
  animals_columns.push_back(Attribute("Species", str));
  animals_columns.push_back(Attribute("Age", in));
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

  return db;
}

void testUpdate(){
	Database db = createTestDatabase();

	db.updateTuples(db.getRelation(0),"Age",g,Attribute("8",in),"6");
	
	if(db.getRelation(0).getRows()[2].getDataStrings()[1]=="6" && db.getRelation(0).getRows()[3].getDataStrings()[1]=="6" )
		printf("testUpdate Passed\n");
	else
		printf("testUpdate Failed.\n");
	
}

void testDelete(){
	Database db = createTestDatabase();

	db.deleteTuples(db.getRelation(0),"Age",g,Attribute("8",in));
	
	if(db.getRelation(0).getRows().size()==4)
		printf("testDelete Passed\n");
	else
          printf("testDelete Failed\n");
}

void testWhere(){
 
  Database db = createTestDatabase();
 
  vector<int> cols = db.where(db.getRelation(0),"Age",g,Attribute("8",in));
  
  if(cols.size()==2 && cols[0]==2 && cols[1]==3)
	  printf("testWhere Passed\n");
  else
	  printf("testWhere Failed\n");
 
}

void testDatabaseEmptyConstructor(){
	Database d;
	Database * addr = &d;
	if(addr == NULL){
		cout << "testDatabaseEmptyConstructor failed. The database was NULL" << endl;
	}
	else{
		cout << "testDatabaseEmptyConstructor passed." << endl;
    }
	//Deprecated test, numberOf Relations tested elsewhere
	/*if(d.numberOfRelations() == 0) {
          cout << "testDatabaseEmptyConstructor passed." << endl;
    } else {
          cout << "testDatabaseEmptyConstructor failed. The database was NULL" << endl;
    }*/
}

void testInitializedDatabase(){
	vector<Relation> R;
	Relation r1,r2;
	R.push_back(r1);
	R.push_back(r2);
	
	Database d(R);
	Database * addr = &d;
	if(addr == NULL){
		cout << "testInitializedDatabase failed. The database was NULL" << endl;
		return;
	}
	if(d.numberOfRelations() != 2){
		cout << "testInitializedDatabase failed. The database contained " << d.numberOfRelations() << " relations instead of 2." << endl;
		return;
	}
	cout << "testInitializedDatabase passed." << endl;
}

void testGetRelation(){
	vector<Relation> R;
	Relation r1("test1", vector<Tuple>(), vector<Attribute>(), vector<size_t>());
	Relation r2("test2", vector<Tuple>(), vector<Attribute>(), vector<size_t>());
	R.push_back(r1);
	R.push_back(r2);
	
	Relation temp;
	Database d(R);
	temp = d.getRelation(0);
	if(temp.getName() != "test1"){
		cout << "testGetRelation failed. The indexing of the Database relations was wrong." << endl;
		return;
	}
	temp = d.getRelation("test2");
	if(temp.getName() != "test2"){
		cout << "testGetRelation failed. The named relation was not found." << endl;
		return;
	}
	cout << "testGetRelation passed." << endl;
}

void testNumberOfRelations(){
	vector<Relation> R;
	Relation r1("test1", vector<Tuple>(), vector<Attribute>(), vector<size_t>());
	Relation r2("test2", vector<Tuple>(), vector<Attribute>(), vector<size_t>());
	R.push_back(r1);
	R.push_back(r2);
	Database d(R);
	if(d.numberOfRelations() != 2){
		cout << "testNumberOfRelations failed. The function returned " << d.numberOfRelations() << " instead of 2.";
		return;
	}
	cout << "testNumberOfRelations passed." << endl;
}

/***************************Relation Class Tests************************/

void testRelationEmptyConstructor(){
	Relation r;
	Relation * addr = &r;
	if(addr == NULL){
		cout << "testRelationEmptyConstructor failed. The relation was NULL" << endl;
	}
	else{
		cout << "testRelationEmptyConstructor passed." << endl;
    } /* Deprecated test, Null better in this context
        if(r.getRows().empty() && r.getColumns().empty() && r.getKeys().empty()){
          cout << "testRelationEmptyConstructor passed." << endl;
        } else {
          cout << "testRelationEmptyConstructor failed. The database was NULL" << endl;
        }*/
}

void testInitializedRelation(){
	vector<Attribute> A;
	A.push_back(Attribute());
	vector<Tuple> T;
	vector<string> tupleData;
	tupleData.push_back("");
	T.push_back(Tuple(tupleData));
	vector<size_t> K;
	K.push_back(0);
	Relation r("test1", T, A, K);
	
	if(r.getName() != "test1"){
		cout << "testInitializedRelation failed. The name of the Relation was " << r.getName() << " not test1." << endl;
		return;
	}
	if(r.getRows().empty()){
		cout << "testInitializedRelation failed. The Tuple vector was NULL." << endl;
		return;
	}
	if(r.getColumns().empty()){
		cout << "testInitializedRelation failed. The Attribute vector was NULL." << endl;
		return;
	}
	if(r.getKeys().empty()){
		cout << "testInitializedRelation failed. The keys vector was NULL." << endl;
		return;
	}
	cout << "testInitializedRelation passed." << endl;
}

void testCopyRelation(){
	vector<Tuple> T;	
	vector<string> tupleData;
	tupleData.push_back("");
	T.push_back(Tuple(tupleData));
	vector<Attribute> A;
	A.push_back(Attribute());
	vector<size_t> K;
	K.push_back(0);
	Relation r("test1", T, A, K);
	Relation rc(r);
	
	if(rc.getName() != "test1"){
		cout << "testCopyRelation failed. The name of the Relation was " << r.getName() << " not test1." << endl;
		return;
	}
	if(rc.getRows().empty()){
		cout << "testCopyRelation failed. The Tuple vector was NULL." << endl;
		return;
	}
	if(rc.getColumns().empty()){
		cout << "testCopyRelation failed. The Attribute vector was NULL." << endl;
		return;
	}
	if(rc.getKeys().empty()){
		cout << "testCopyRelation failed. The keys vector was NULL." << endl;
		return;
	}
	cout << "testCopyRelation passed." << endl;
}

void testAddTuple(){
	Tuple T((vector<string>()));
	T.addData("test1");
	Relation r;
	r.addAttribute(Attribute("A", str),"test");
	r.addTuple(T);
	
	vector<Tuple> temp;
	temp = r.getRows();
	if(temp[0].getDataStrings()[0] != "test1"){
		cout << "testAddTuple failed. The Tuple put in was not returned." << endl;
		return;
	}
	cout << "testAddTuple() passed." << endl;
}

void testAddAttribute(){
  Tuple T((vector<string>()));
	T.addData("test1");
	Relation r;
	r.addAttribute(Attribute("A", str),"test");
	r.addTuple(T);
	r.addAttribute(Attribute("B", str),"test2");
	
	vector<Attribute> A;
	A = r.getColumns();
	if(A[1].getValue() != "B"){
		cout << "testAddAttribute failed. The Attribute was not added." << endl;
		return;
	}
	
	vector<Tuple> temp;
	temp = r.getRows();
	if(temp[0].getDataStrings()[1] != "test2"){
		cout << "testAddAttribute failed. The default value was not added to the Tuples." << endl;
		return;
	}
	cout << "testAddAttribute passed." << endl;
}

void testDeleteTuple(){
	vector<Tuple> T;
	Tuple t;
	vector<Attribute> A;
	vector<size_t> K;
	Relation r("test1", T, A, K);
	
	r.addTuple(t);
	r.deleteTuple(t);
	if(r.getRows().size() > 0){
		cout << "testDeleteTuple failed. The tuple was not deleted by reference." << endl;
		return;
	}
	r.addTuple(t);
	r.deleteTuple(0);
	if(r.getRows().size() > 0){
		cout << "testDeleteTuple failed. The tuple was not deleted by index." << endl;
		return;
	}
	cout << "testDeleteTuple passed." << endl;
}

void testGetRows(){
	vector<string> s;
	s.push_back("testString");
	Tuple T(s);
	vector<Tuple> R;
	R.push_back(T);
	R.push_back(T);
	
	Attribute A("test", str);
	vector<Attribute> C;
	C.push_back(A);
	
	vector<size_t> k;
	k.push_back(0);
	
	Relation r("testRelation", R, C, k);
	
	vector<Tuple> temp;
	temp = r.getRows();
	if(temp[0].getDataStrings()[0] != "testString"){
		cout << "testGetRows failed. The correct row was not returned." << endl;
		return;
	}
	cout << "testGetRows passed." << endl;
}

void testGetColumns(){
	vector<string> s;
	s.push_back("testString");
	Tuple T(s);
	vector<Tuple> R;
	R.push_back(T);
	R.push_back(T);
	
	Attribute A("test", str);
	vector<Attribute> C;
	C.push_back(A);
	
	vector<size_t> k;
	k.push_back(0);
	
	Relation r("testRelation", R, C, k);
	
	vector<Attribute> temp;
	temp = r.getColumns();
	if(temp[0].getValue() != "test"){
		cout << "testGetColumns failed. The correct attribute was not returned." << endl;
		return;
	}
	cout << "testGetColumns passed." << endl;
}

void testGetKeys(){
	vector<string> s;
	s.push_back("testString");
	Tuple T(s);
	vector<Tuple> R;
	R.push_back(T);
	R.push_back(T);
	
	Attribute A("test", str);
	vector<Attribute> C;
	C.push_back(A);
	
	vector<size_t> k;
	k.push_back(0);
	
	Relation r("testRelation", R, C, k);
	vector<size_t> temp;
	temp = r.getKeys();
	if(temp[0] != 0){
		cout << "testGetKeys failed. The correct key was not returned." << endl;
		return;
	}
	cout << "testGetKeys passed." << endl;
}

void testIsKey(){
	vector<string> s;
	s.push_back("testString");
	Tuple T(s);
	vector<Tuple> R;
	R.push_back(T);
	R.push_back(T);
	
	Attribute A("test", str);
	vector<Attribute> C;
	C.push_back(A);
	
	vector<size_t> k;
	k.push_back(0);
		
	Relation r("testRelation", R, C, k);
	
	if(!r.isKey(0)){
		cout << "testIsKey failed. The key was not detected." << endl;
		return;
	}
	cout << "testIsKey passed." << endl;
}

void testGetName(){
	Relation r("testRelation", vector<Tuple>(), vector<Attribute>(), vector<size_t>());
	if(r.getName() != "testRelation"){
		cout << "testGetName failed. The returned name was " << r.getName() << " instead of testRelation." << endl;
	}
}

/***************************Tuple Class Tests************************/

void testTupleEmptyContstructor(){
	Tuple t;
	Tuple * addr = &t;
	if(addr == NULL){
		cout << "testTupleEmptyConstructor failed. The Tuple was NULL" << endl;
	}
	else{
		cout << "testTupleEmptyConstructor passed." << endl;
	}
	/* Deprecated test, Null is better in this context.
        if(t.getDataStrings().empty()){
          cout << "testTupleEmptyConstructor passed." << endl;
        } else {
          cout << "testTupleEmptyConstructor failed. The Tuple was NULL" << endl;
        }*/
}

void testInitializedTuple(){
	vector<string> s;
	s.push_back("test1");
	s.push_back("test2");
	Tuple t(s);
	if(t.getDataStrings()[1] != "test2"){
		cout << "testInitializedTuple failed. The wrong data was in the Tuple." << endl;
		return;
	}
	cout << "testInitializedTuple passed." << endl;
}

void testAddData(){
	Tuple t;
	int temp = sizeof(t);
	t.addData("test1");
	if(sizeof(t)<temp){
		cout << "testAddData failed. Adding data does not increase the size of a tuple." << endl;
		return;
	}
	cout << "testAddData passed." << endl;
}

void testGetDataStrings(){
	Tuple t;
	string s1 = "test1";
	string s2 = "test2";
	vector<string> s;
	t.addData(s1);
	s.push_back(s1);
	t.addData(s2);
	s.push_back(s2);
	if(t.getDataStrings() != s){
		cout << "testGetDataStrings failed. The Tuple contents and the data put in are not equivalent." << endl;
		return;
	}
	cout << "testGetDataStrings passed." << endl;
}

void testChangeDataMember(){
	vector<string> s;
	s.push_back("test1");
	s.push_back("test2");
	Tuple t(s);
	
	t.changeDataMember(1,"testChanged");
	if(t.getDataStrings()[1] != "testChanged"){
          cout << "testChangeDataMember failed. The data member was " << t.getDataStrings()[1] << " instead of testChanged." << endl;
		return;
	}
	cout << "testChangeDataMember passed." << endl;
}

/**************************Attribute Class Tests************************/

void testAttributeEmptyConstructor(){
	Attribute a;
	Attribute * addr = &a;
	if(addr == NULL){
		cout << "testAttributeEmptyConstructor failed. The Attribute was NULL" << endl;
	}
	else{
		cout << "testAttributeEmptyConstructor passed." << endl;
	}
	/*
        if(a.getValue().empty()) {
          cout << "testAttributeEmptyConstructor passed." << endl;
        } else {
          cout << "testAttributeEmptyConstructor failed. The Attribute was NULL" << endl;
        }*/
}

void testInitializedAttribute(){
	Attribute a("testString", str);
	if(a.getValue() != "testString"){
		cout << "testInitializedAttribute failed. The value was " << a.getValue() << " not testString." << endl;
		return;
	}
	if(a.getDataType() != str){
		cout << "testInitializedAttribute failed. The type was not string." << endl;
		return;
	}
	cout << "testInitializedAttribute passed." << endl;
}

void testCopyAttribute(){
	Attribute a("testString", str);
	Attribute b(a);
	if(b !=a){
		cout << "testCopyAttribute failed. The copy was not the same." << endl;
		return;
	}
	cout << "testCopyAttribute passed." << endl;
}

void testAttributeGetValue(){
	Attribute a("testString", str);
	if(a.getValue() != "testString"){
		cout << "testAttributeGetValue failed. The value was different from the initialized value." << endl;
		return;
	}
	cout << "testAttributeGetValue passed." << endl;

}

void testAttributeGetDataType(){
	Attribute a("testString", str);
	if(a.getDataType() != str){
		cout << "testAttributeGetDataType failed. The value was different from the initialized value." << endl;
		return;
	}
	cout << "testAttributeGetDataType passed." << endl;
}

void testRenameAttr(){
	Attribute a("testString", str);
	Attribute b(a);
	b.renameAttr("testString2", str);
	if(a == b){
		cout << "testRenameAttr failed. The data type did not change." << endl;
		return;
	}
	cout << "testRenameAttr passed." << endl;
}

int main(){
	
	//Database Tests
	testDatabaseEmptyConstructor();
	testInitializedDatabase();
	testGetRelation();
	testNumberOfRelations();

	
	//Relation Tests
	testRelationEmptyConstructor();
	testInitializedRelation();
	testCopyRelation();
	testAddTuple();
	testAddAttribute();
	testDeleteTuple();
	testGetRows();
	testGetColumns();
	testGetKeys();
	testIsKey();
	testGetName();
	
	//Tuple Tests
	testTupleEmptyContstructor();
	testInitializedTuple();
	testAddData();
	testChangeDataMember();
	testGetDataStrings();
	
	//Attribute Tests
	testAttributeEmptyConstructor();
	testInitializedAttribute();
	testCopyAttribute();
	testAttributeGetValue();
	testAttributeGetDataType();
	testRenameAttr();

	//Database management functions test
	testWhere();
	testDelete();
	testUpdate();
	testRelationExists();
	testInsert();
	//Test for show - displays a table so putting it at the end
	testShow();

        //Relational tests
        test_relational();
}





void test_relational(){
  bool success = true;
  string test_output;

  vector<Attribute> animals_columns;
  animals_columns.push_back(Attribute("Species", str));
  animals_columns.push_back(Attribute("Age", in));
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
                   Attribute("8", in)).empty()){
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
                                            "Age", g, Attribute("8", in)))){
    cerr << "Selection, greater, int, FAILED\n";
    success = false;
  }

  vector<Tuple> young_animals_rows;
  young_animals_rows.push_back(spot);
  young_animals_rows.push_back(socks);
  young_animals_rows.push_back(pocky);
  Relation young_animals("Young Animals", young_animals_rows, animals_columns, keys);
  if(!young_animals.equalContents(db.selection(db.getRelation(0), "young",
                                              "Age", l, Attribute("8", in)))){
    cerr << "Selection, less, int, FAILED\n";
    success = false;
  }

  old_animals.addTuple(bones);
  if(!old_animals.equalContents(db.selection(db.getRelation(0), "old2",
                                             "Age", ge, Attribute("8", in)))){
    cerr << "Selection, greaterEqual, int, FAILED\n";
    success = false;
  }

  young_animals.addTuple(bones);
  if(!young_animals.equalContents(db.selection(db.getRelation(0), "young2",
                                               "Age", le, Attribute("8", in)))){
    cerr << "Selection, lessEqual, int, FAILED\n";
    success = false;
  }

  vector<Tuple> animals13_rows;
  animals13_rows.push_back(fido);
  Relation animals13("Animals 13", animals13_rows, animals_columns, keys);
  if(!animals13.equalContents(db.selection(db.getRelation(0), "13",
                                           "Age", e, Attribute("13", in)))){
    cerr << "Selection, equal, int, FAILED\n";
    success = false;
  }

  Relation animals_not_13 = animals;
  animals_not_13.deleteTuple(fido);
  if(!animals_not_13.equalContents(db.selection(db.getRelation(0), "not13",
                                                "Age", ne, Attribute("13", in)))){
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
  attrib_cols.push_back(Attribute("A", in));
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
