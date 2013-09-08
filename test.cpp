#include "Database.h"


/***********************Database Class Tests**************************/

void testDatabaseEmptyConstructor(){
	Database d;
	if(d == NULL){
		cout << "testDatabaseEmptyConstructor failed. The database was NULL" << endl;
	}
	else{
		cout << "testDatabaseEmptyConstructor passed." << endl;
	}
}

void testInitializedDatabase(){
	vector<Relation> R;
	Relation r1,r2;
	R.push_back(r1);
	R.push_back(r2);
	
	Database d(R);
	if(d == NULL){
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
	Relation r1("test1", vector<Tuple>(), vector<Attribute>());
	Relation r2("test2", vector<Tuple>(), vector<Attribute>());
	R.push_back(r1);
	R.push_back(r2);
	
	Relation temp;
	Database d(R);
	temp = d.getRelation(0);
	if(temp.getName() != "test1"){
		cout << "testGetRelation failed. The indexing of the Database relations was wrong." << endl;
		return;
	}
	temp = d.getRelation("test2")
	if(temp.getName() != "test2"){
		cout << "testGetRelation failed. The named relation was not found." << endl;
		return;
	}
	cout << "testGetRelation passed." << endl;
}

void testNumberOfRelations(){
	vector<Relation> R;
	Relation r1("test1", vector<Tuple>(), vector<Attribute>());
	Relation r2("test2", vector<Tuple>(), vector<Attribute>());
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
	if(r == NULL){
		cout << "testRelationEmptyConstructor failed. The database was NULL" << endl;
	}
	else{
		cout << "testRelationEmptyConstructor passed." << endl;
	}
}

void testInitializedRelation(){
	vector<Tuple> T;
	vector<Attribute> A;
	vector<size_t> K;
	Relation r("test1", T, A, K);
	
	if(r.getName() != "test1"){
		cout << "testInitializedRelation failed. The name of the Relation was " << r.getName() << " not test1." << endl;
		return;
	}
	if(r.getRows() == NULL){
		cout << "testInitializedRelation failed. The Tuple vector was NULL." << endl;
		return;
	}
	if(r.getColumns() == NULL){
		cout << "testInitializedRelation failed. The Attribute vector was NULL." << endl;
		return;
	}
	if(r.getKeys() == NULL){
		cout << "testInitializedRelation failed. The keys vector was NULL." << endl;
		return;
	}
	cout << "testInitializedRelation passed." << endl;
}

void testCopyRelation(){
	vector<Tuple> T;
	vector<Attribute> A;
	vector<size_t> K;
	Relation r("test1", T, A, K);
	Relation rC(r);
	
	if(rc.getName() != "test1"){
		cout << "testCopyRelation failed. The name of the Relation was " << r.getName() << " not test1." << endl;
		return;
	}
	if(rc.getRows() == NULL){
		cout << "testCopyRelation failed. The Tuple vector was NULL." << endl;
		return;
	}
	if(rc.getColumns() == NULL){
		cout << "testCopyRelation failed. The Attribute vector was NULL." << endl;
		return;
	}
	if(rc.getKeys() == NULL){
		cout << "testCopyRelation failed. The keys vector was NULL." << endl;
		return;
	}
	cout << "testCopyRelation passed." << endl;
}

void testAddTuple(){
	Tuple T(vector<string>());
	T.addData("test1");
	Relation r;
	r.addAttribute(Attribute("A", dataTypes::str),"test");
	r.addTuple(T);
	
	vector<Tuple> temp;
	temp = r.getRows();
	if(temp[0].getDataStrings[0] != "test1"){
		cout << "testAddTuple failed. The Tuple put in was not returned." << endl;
		return;
	}
	cout << "testAddTuple() passed." << endl;
}

void testAddAttribute(){
	Tuple T(vector<string>());
	T.addData("test1");
	Relation r;
	r.addAttribute(Attribute("A", dataTypes::str),"test");
	r.addTuple(T);
	r.addAttribute(Attribute("B", dataTypes::str),"test2");
	
	vector<Attribute> A;
	A = r.getColumns();
	if(A[1].getValue() == "B"){
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
	
	Attribute A("test", dataTypes::str);
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
	
	Attribute A("test", dataTypes::str);
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
	
	Attribute A("test", dataTypes::str);
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
	
	Attribute A("test", dataTypes::str);
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
}