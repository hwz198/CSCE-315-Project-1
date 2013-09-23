#include <algorithm>
#include <iostream>
#include "Relation.h"
#include "Attribute.h"
using namespace std;

Relation::Relation(){ //Empty constructor
	name = string();
	rows = vector<Tuple>();
	columns = vector<Attribute>();
}

Relation::Relation(string c_name, vector<Tuple> c_rows, vector<Attribute> c_columns, vector<size_t> c_keys){ //Initialized constructor
	if(!c_rows.empty()){
		if(c_rows[0].getDataStrings().size() != c_columns.size()){
			cout << "ERROR: Rows and Columns have different count. The Relation cannot be built." << endl;
			cout << "There are " << c_rows[0].getDataStrings().size() << " rows and " << c_columns.size() << " columns" << endl;
			return;
		}
	}
	for(int i; i++; i<c_rows.size()){
		vector<string> checkData = c_rows[i].getDataStrings();
		for(int j; j++; j<checkData.size()){
			if(c_columns[j].getDataType() == str && checkData[j].length() > c_columns[j].maxLength()){
				cout << "ERROR: The rows of this Relation contnai data larger than the column attributes will allow. The Relation cannot be built." << endl;
				return;
			}
		}
	}
	name = c_name;
	rows = c_rows;
	columns = c_columns;
	keys = c_keys;
}

Relation::Relation(Relation const &A){ //copy constructor
	name = A.getName();
	rows = A.getRows();
	columns = A.getColumns();
	keys = A.getKeys();
}

void Relation::addTuple(Tuple T){
  if(T.getDataStrings().size() != columns.size()){ //This checks that a Tuple has a proper number of columns. If it doesn't that would break the table.
    cout<< "ERROR: The Tuple put into Relation " << name << " does not have the correct number of columns. Please try a different Tuple." << endl;
    return;
  }
  vector<string> dataCheck = T.getDataStrings();
  for(int i = 0; i<dataCheck.size(); ++i){
	if(dataCheck[i].length() > columns[i].maxLength() && columns[i].getDataType() == str){
		cout << "Error: The Tuple contains string data longer than the container is allowed to hold, and thus cannot be added to the Relation." << endl;
		return;
	}
  }
 
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


void Relation::updateTuple(Tuple T, int target_index, string newData){
	for(vector<Tuple>::iterator it = rows.begin(); it != rows.end(); ++it){
    if(*it == T){
	  int index = distance(rows.begin(),it);
	  if(newData.length() > columns[index].maxLength() && columns[index].getDataType() == str){
		cout << "ERROR: The new Tuple data is larger than the associated Attribute will allow. The Tuple could not be updated." << endl;
		return;
	  }
      it->changeDataMember(target_index,newData);
      break;
    }
	}
}

Tuple Relation::getTuple(Tuple T) const{
  for(size_t i = 0; i < rows.size(); ++i){
    if(rows[i] == T){
      return rows[i];
    }
  }
  cerr << "Tuple not found.\n";
  return Tuple();
}

Tuple Relation::getTuple(size_t index) const{
  if(index < rows.size()){
    return rows[index];
  }
  cerr << "Index out of bounds.\n";
  return Tuple();
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
  vector<Tuple> Arows = rows;
  vector<Tuple> Brows = B.getRows();
  sort(Arows.begin(), Arows.end(), tupleComp(keys));
  sort(Brows.begin(), Brows.end(), tupleComp(keys));
  return Arows == Brows;
}

bool Relation::empty() const{
  return rows.empty();
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
