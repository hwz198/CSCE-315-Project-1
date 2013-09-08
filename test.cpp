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
	T.push_back("test1");
	Relation r;
	r.addAttribute(Attribute("A", "string"),"test");
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
	T.push_back("test1");
	Relation r;
	r.addAttribute(Attribute("A", "string"),"test");
	r.addTuple(T);
	r.addAttribute(Attribute("B", "string"),"test2");
	
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
}