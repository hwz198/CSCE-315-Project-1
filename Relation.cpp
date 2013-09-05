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
	name = A.name;
	rows = A.rows;
	columns = A.columns;
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

vector<Tuple> getRows(){
	return rows;
}

vector<Attribute> getColumns(){
	return columns;
}

vector<size_t> getKeys(){
	return keys;
}

//returns false if index isn't found in keys vector
bool isKey(size_t index){
	return find(keys.begin(), keys.end(), index) != keys.end();
}

string getName(){
	return name;
}
