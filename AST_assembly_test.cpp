#include "AST_Assembly.h"
#include<iostream>
using namespace std;

void testCreateTable(){

  AST_Assembly P;  
  string str = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
  bool result = P.assemble(str);
  if(!result){
  	cout<<"Create Table test 1 failed"<<endl;
  	return;
  	}
  	
  str = "create TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
  result = P.assemble(str);	
  if(result!=0){
  	cout<<"Create Table test 2 failed"<<endl;
  	return;
  	}
  
  str = "CREATE TABLE animals (TABLE VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
  result = P.assemble(str);	
  if(result!=0){
  	cout<<"Create Table test 3 failed"<<endl;
  	return;
  	}	
  
  str = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(eight), years INTEGER) PRIMARY KEY (name, kind);";
  result = P.assemble(str);	
  if(result!=0){
  	cout<<"Create Table test 4 failed"<<endl;
  	return;
  	}
  	
  str = "CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);";
  result = P.assemble(str);	
  if(result!=1){
  	cout<<"Create Table test 5 failed"<<endl;
  	return;
  	}
  	
  str = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (test, kind);"; //Can it be checked that the variables in primary key are one of the ones mentioned before? i.e. in this case either name,kind or years...not test.
  //that will probably be checked upon relation creation
  
  result = P.assemble(str);	
  if(result!=1){
  	cout<<"Create Table test 6 failed"<<endl;
  	return;
  	}
  
 
  cout<<"All Create Table tests passed"<<endl;
  				
}

void showTableTest(){

 	AST_Assembly P;  
  	string str = "SHOW animals animals;";
  	bool result = P.assemble(str);
	if(result){
  		cout<<"Show Table test 1 failed"<<endl;
  		return;
  	}
  	
  	str = "Show animals;";
  	result = P.assemble(str);
  	if(result!=0){
  		cout<<"Show Table test 2 failed"<<endl;
  		return;
  	}
  	
  	str = "Show animals;;";
  	result = P.assemble(str);
  	if(result!=0){
  		cout<<"Show Table test 3 failed"<<endl;
  		return;
  	}
  	
  	str = "SHOW SHOW & animals;";
  	result = P.assemble(str);
  	if(result!=0){
 	 	cout<<"Show Table test 4 failed"<<endl;
  		return;
  	}
  	
  	str = "SHOW animals;";
  	result = P.assemble(str);
  	if(result!=0){
  		cout<<"All Show Table tests Passed"<<endl;
  		return;
  	}
  	
}

void insertTest(){

	AST_Assembly P;  
  	string str = "INSERT INT animals VALUES FROM (\"Joe\", \"cat\", 4);";
  	bool result = P.assemble(str);
	if(result!=0){
  		cout<<"Insert Table test 1 failed"<<endl;
  		return;
  	}
  	
  	str = "INSERT INTO animals VALueS FROM (\"Joe\", \"cat\", 4);";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Insert Table test 2 failed"<<endl;
  		return;
  	}
  	
  	str = "INSERT INTO animals VALUES FROM (\"Joe\",, \"cat\", 4);";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Insert Table test 3 failed"<<endl;
  		return;
  	}
  	
  	str = "INSERT INTO animals VALUES FROM \"Joe\", \"cat\", 4);";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Insert Table test 4 failed"<<endl;
  		return;
  	}
  	
  	str = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\",);";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Insert Table test 5 failed"<<endl;
  		return;
  	}
  	
  	str = "INSERT INTO points VALUES FROM RELATION (select (z2 > 0) dots_to_points);";
  	result = P.assemble(str);
	if(result!=1){
  		cout<<"Insert Table test 6 failed"<<endl;
  		return;
  	}
  	
  	str = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);";
  	result = P.assemble(str);
	if(result==1){
  		cout<<"All Insert Table tests passed"<<endl;
  		return;
  	}

}

void exitTest(){

	AST_Assembly P;  
  	string str = "EXITT;";
  	bool result = P.assemble(str);
	if(result!=0){
  		cout<<"Exit test 1 failed"<<endl;
  		return;
  	}

	str = "EXIT;blah";		//Text after semicolon 
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Exit test 2 failed"<<endl;
  		return;
  	}
  	str = "exit;";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Exit test 3 failed"<<endl;
  		return;
  	}

	str = "EXIT;";
  	result = P.assemble(str);
	if(result==1){
  		cout<<"All Exit tests Passed"<<endl;
  		return;
  	}

}

void queryTest(){

	AST_Assembly P;
	string str = "common_names <- project (name) (select (aname == name & akind != kind) (a * animals));"; //single & gives infinite loop
	bool result = P.assemble(str);
	if(result!=0){
  		cout<<"Query Test 1 failed"<<endl;
  		return;
  	}
  	
  	str = "good_and_bad_guys <- friends + enemies;";
  	result = P.assemble(str);
	if(result!=1){
  		cout<<"Query Test 2 failed"<<endl;
  		return;
  	}
  	
  	str = "high_hitters <- select (homeruns >= 40) baseball_players;";
  	result = P.assemble(str);
	if(result!=1){
  		cout<<"Query Test 3 failed"<<endl;
  		return;
  	}
  	
  	str = "product_test <- shapes ** colors;";
	result = P.assemble(str);
	if(result!=0){
  		cout<<"Query Test 4 failed"<<endl;
  		return;
  	}

	str = "bad_query <- project t) points;";
	result = P.assemble(str);
	if(result!=0){
  		cout<<"Query Test 5 failed"<<endl;
  		return;
  	}
  	
  	str = "dots_to_points < rename (x2, y2, z2) dots;";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Query Test 6 failed"<<endl;
  		return;
  	}
  	
  	str = "dots_to_points <- rename (x2, y2 z2) dots;";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Query Test 7 failed"<<endl;
  		return;
  	}

	str = "dots_to_points <- renamE (x2, y2 z2) dots;";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Query Test 8 failed"<<endl;
  		return;
  	}
  	
  	str = "dots_to_points <-& rename (x2, y2, z2) dots;";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"Query Test 7 failed"<<endl;
  		return;
  	}

	str = "dots_to_points <- rename (x2, y2, z2) dots;";
  	result = P.assemble(str);
	if(result!=0){
  		cout<<"All Query Tests Passed."<<endl;
  		return;
  	}
}




int main(){
  
  testCreateTable();
  showTableTest(); //Write and Close are similar, hence not tested separately. 
  insertTest();
  exitTest();
  queryTest();
  
  
 /* while(true){
    string str; //= "high_hitters <- select (homeruns >= 40) baseball_players;";
    getline(cin, str);
    cout << P.assemble(str) << endl;
    vector<Token> tokens = P.tokens;
    for(unsigned int i = 0; i < tokens.size(); ++i){
      cout << TokenStrings[tokens[i].type()] << ' ';
    }
    cout << endl;
  }*/
  return 0;
}
