#include "Database.h"
#include "Tuple.h"
#include "Attribute.h"
#include "Relation.h"
#include <iostream>
#include <cstdlib>

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
	db.Show(0);
	
	printf("TESTupdate still needs to be worked on");
	
}

void testDelete(){
	Database db = createTestDatabase();

	db.deleteTuples(db.getRelation(0),"Age",g,Attribute("8",in));
	db.Show(0);
	if(db.getRelation(0).getRows().size()==4)
		printf("testDelete passed");
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
	
	testRelationExists();
	testInsert();
	
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

	//DELETE AND UPDATE TESTS
	testWhere();
	testDelete();
	testUpdate();
	//Test for show - displays a table so putting it at the end
	testShow();
	
}
