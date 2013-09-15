#include "parser.h"
#include<iostream>
using namespace std;

void testCreateTable(){

  parser P;  
  string str = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
  bool result = P.parse(str);
  if(!result){
  	cout<<"Create Table test 1 failed"<<endl;
  	return;
  	}
  	
  str = "create TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
  result = P.parse(str);	
  if(result!=0){
  	cout<<"Create Table test 2 failed"<<endl;
  	return;
  	}
  
  str = "CREATE TABLE animals (TABLE VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
  result = P.parse(str);	
  if(result!=0){
  	cout<<"Create Table test 3 failed"<<endl;
  	return;
  	}	
  
  str = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(eight), years INTEGER) PRIMARY KEY (name, kind);";
  result = P.parse(str);	
  if(result!=0){
  	cout<<"Create Table test 4 failed"<<endl;
  	return;
  	}
  	
  str = "CREATE TABLE species (kind VARCHAR(10)) PRIMARY KEY (kind);";
  result = P.parse(str);	
  if(result!=1){
  	cout<<"Create Table test 5 failed"<<endl;
  	return;
  	}
  	
  str = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (test, kind);"; //Can it be checked that the variables in primary key are one of the ones mentioned before? i.e. in this case either name,kind or years...not test.
  
  result = P.parse(str);	
  if(result!=0){
  	cout<<"Create Table test 6 failed"<<endl;
  	return;
  	}
  
 
  cout<<"All Create Table tests passed"<<endl;
  				
}

void showTableTest(){

 	parser P;  
  	string str = "SHOW animals animals;";
  	bool result = P.parse(str);
	if(result){
  	cout<<"Show Table test 1 failed"<<endl;
  	return;
  	}
  	
  	str = "Show animals;";
  	result = P.parse(str);
  	if(result!=0){
  	cout<<"Show Table test 2 failed"<<endl;
  	return;
  	}
  	
  	str = "Show animals;;";
  	result = P.parse(str);
  	if(result!=0){
  	cout<<"Show Table test 3 failed"<<endl;
  	return;
  	}
  	
  	str = "SHOW SHOW animals;";
  	result = P.parse(str);
  	if(result!=0){
  	cout<<"Show Table test 4 failed"<<endl;
  	return;
  	}
  	
  	str = "SHOW animals;";
  	result = P.parse(str);
  	if(result!=0){
  	cout<<"All Show Table tests Passed"<<endl;
  	return;
  	}
  	
}




int main(){
  parser P;
  
  
  string str2 = "common_names <- project (name) (select (aname == name && akind != kind) (a * animals));"; //single & gives infinite loop
  
  testCreateTable();
  showTableTest(); //Write and Close are similar, hence not tested separately. 
  
  
  
 /* while(true){
    string str; //= "high_hitters <- select (homeruns >= 40) baseball_players;";
    getline(cin, str);
    cout << P.parse(str) << endl;
    vector<Token> tokens = P.tokens;
    for(unsigned int i = 0; i < tokens.size(); ++i){
      cout << TokenStrings[tokens[i].type()] << ' ';
    }
    cout << endl;
  }*/
  return 0;
}
