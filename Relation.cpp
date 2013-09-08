#include <algorithm>
#include "Relation.h"
using namespace std;

Relation::Relation(){
	name = string();
	rows = vector<Tuple>();
	columns = vector<Attribute>();
}

Relation::Relation(string c_name, vector<Tuple> c_rows, vector<Attribute> c_columns, vector<size_t> c_keys){
	name = c_name;
	rows = c_rows;
	columns = c_columns;
	keys = c_keys;
}

Relation::Relation(Relation const &A){
	name = A.getName();
	rows = A.getRows();
	columns = A.getColumns();
}

void Relation::addTuple(Tuple T){
	if(T.size() != columns.size()){
		cout << "ERROR: The Tuple put into Relation " << name << " does not have the correct number of columns. Please try a different Tuple." << endl;
		return;
	}
	rows.push_back(T);
}

void Relation::addAttribute(Attribute A, string defaultValue){
	columns.push_back(A);
	for(int i = 0; i<rows.size(); ++i){				
		rows[i].addData(defaultValue);
	}
}

vector<Tuple> Relation::getRows() const{
	return rows;
}

vector<Attribute> Relation::getColumns() const{
	return columns;
}

vector<size_t> Relation::getKeys() const{
	return keys;
}

//returns false if index isn't found in keys vector
bool Relation::isKey(size_t index){
	return find(keys.begin(), keys.end(), index) != keys.end();
}

string Relation::getName() const{
	return name;
}
