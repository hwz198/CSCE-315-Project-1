#include <algorithm>
#include "Relation.h"
using namespace std;

Relation::Relation(){
	name = string();
	rows = vector<Tuple>();
	columns = vector<Attribute>();
}

Relation::Relation(string c_name, vector<Tuple> c_rows, vector<Attribute> c_columns){
	name = c_name;
	rows = c_rows;
	columns = c_columns;
}

Relation::Relation(Relation const &A){
	name = A.getName();
	rows = A.getRows();
	columns = A.getColumns();
}

void Relation::addTuple(Tuple T){
	rows.push_back(T);
}

void Relation::addAttribute(Attribute A, string defaultValue){
	columns.push_back(A);
	for(int i = 0; i<rows.size(); ++i){				
		rows[i].addData(defaultValue);
	}
}

void Relation::deleteTuple(Tuple T){
  for(vector<Tuple>::iterator it = rows.begin(); it != rows.end(); ++it){
    if(*it == T){
      rows.erase(it);
      break;
    }
  }
}

void Relation::deleteTuple(size_t index){
  if(index < rows.size())
    rows.erase(rows.begin() + index);
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

bool Relation::equalContents(const Relation &B) const{
  return rows == B.getRows() && columns == B.getColumns();
}

bool operator==(const Relation &a, const Relation &b){
  return a.name == b.name
    && a.rows == b.rows
    && a.columns == b.columns
    && a.keys == b.keys;
}

bool operator!=(const Relation &a, const Relation &b){
  return a.name != b.name
    || a.rows != b.rows
    || a.columns != b.columns
    || a.keys != b.keys;
}
