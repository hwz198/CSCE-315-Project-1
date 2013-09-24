#include "FileIO.h"

using namespace std;

fileIOOp::fileIOOp(const Relation &R){ //constructor
	attr = R.getColumns();
	if(attr.empty()){
		cout << "Cannot store a Relation with no attributes." << endl;
	}
        /* not sure if this is necessary, apparently this is read as a copy
           constructor instead of initialization, and it looks like the STL
           says no go to that. not sure what you want to do. --RD */
	//fileTarget = ofstream();
	relationName = R.getName();
	fileName = relationName + ".db";
	fileTarget.open(fileName.c_str());
	tups = R.getRows();
	keys = R.getKeys();
	for(int i = 0; i<attr.size(); ++i){ //This works because everything is a string. A little inefficient (checks length for int and double) but simple.
		  varcharLength.push_back(0);
          for(int j = 0; j<tups.size(); ++j){
			if(varcharLength[i] < tups[j].getDataStrings()[i].length()){
				varcharLength[i] = tups[j].getDataStrings()[i].length();
			}
		}
	}
}

fileIOOp::~fileIOOp(){
	fileTarget.close();
}

void fileIOOp::writeToFile(){
	//Create the table
	fileTarget <<"CREATE TABLE " << relationName << " (";
	for(int i = 0; i<attr.size(); ++i){
		fileTarget << attr[i].getValue() << " ";
		if(attr[i].getDataType() == str){
			fileTarget << "VARCHAR(" << varcharLength[i] << ")";
		}
		else if(attr[i].getDataType() == in){
			fileTarget << "INTEGER";
		}
		else if(attr[i].getDataType() == d){
			fileTarget << "DOUBLE";
		}
		if(i != attr.size()-1){ fileTarget << ", ";}
		else{fileTarget << ") ";}
	}
	if(!keys.empty()){
		fileTarget << "PRIMARY KEY (";
		for(int i = 0; i<keys.size(); ++i){
			fileTarget << attr[keys[i]].getValue();
			if(i != keys.size()-1){fileTarget << " ,";}
			else{ fileTarget << ")";}
		}
	}
	fileTarget << ";" << endl;
	
	//Put the Tuples in it
	for(int i = 0; i<tups.size(); ++i){
		fileTarget << "INSERT INTO " << relationName << " VALUES FROM (";
		vector<string> tupData = tups[i].getDataStrings();
        for(int j = 0; j < tupData.size(); ++j){
            if(attr[j].getDataType() == str){
				fileTarget << "\"" << tupData[j] << "\"";
			}
			else{
				fileTarget << tupData[j];
			}
			if(j != tupData.size() -1){fileTarget << ", ";}
			else{fileTarget << ")";}
		}
		fileTarget << ";" << endl;
	}
}
