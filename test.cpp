#include "Database.h"

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



int main(){
	
	//Database Tests
	testDatabaseEmptyConstructor();
	testInitializedDatabase();
	testGetRelation();
	testNumberOfRelations();
}