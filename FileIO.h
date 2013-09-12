#include <stdio>
#include <iostream>
#include <fstream>
#include "Database.h"
#include "Relation.h"
#include "Attribute.h"
#include "Tuple.h"

class fileIOOp{
	ofstream fileTarget;
	string relationName;
	string fileName;
	vector<Tuple> tups;
	vector<Attribute> attr;
	vector<int> varcharLength;
	vector<size_t> keys;
	public:
	//File is opened when constructor is called and deleted when the destructor  is called
	fileIOOp(const Relation &R); //constructor
	~fileIOOp(); //destructor
	void writeToFile();
}