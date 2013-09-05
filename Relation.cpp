#include "Relation.h"
using namespace std;

Relation::Relation(){
	name = string();
	rows = vector<Tuple>();
	columns = vector<Attribute>();
}

Relation::Relation(string c_name, Vector<Tuple> c_rows, Vector<Attribute> c_columns){
	name = c_name;
	rows = c_rows;
	columns = c_columns;
}

Relation::Relation(Relation A){
	name = A.getName();
	rows = A.getRows();
	columns = A.getColumns();
}

void Relation::addTuple(Tuple T){
	rows.push_back(T);
}

void Relation::addAttribute(Attribute A, string defaultValue){
	columns.push_back(A);
	for(int i = 0; i++; i<rows.size()){				
		rows[i].addData(defaultValue);
	}
}

vector<Tuple> Relation::getRows(){
	return rows;
}

vector<Attribute> Relation::getColumns(){
	return columns;
}

vector<size_t> Relation::getKeys(){
	return keys;
}

//returns false if index isn't found in keys vector
bool Relation::isKey(size_t index){
	return find(keys.begin(), keys.end(), index) != keys.end();
}

string Relation::getName(){
	return name;
}

bool Relation::tupleComp(const Tuple &a, const Tuple &b){
  size_t sort_key = keys[0];
  return a.getDataStrings()[sort_key] < b.getDataStrings()[sort_key];
}
