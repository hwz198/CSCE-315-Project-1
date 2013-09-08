#include "Tuple.h"
using namespace std;

Tuple::Tuple(){
	dataStrings = vector<string>();
}

Tuple::Tuple(vector<string> newDataVec){
	dataStrings = newDataVec;
}

void Tuple::addData(string newData){
	dataStrings.push_back(newData);
}

void Tuple::changeDataMember(int targetIndex, string newData){
	if(targetIndex > dataStrings.size()-1){
		printf("Error: index out of bounds. The tuple is not that big. Use addData instead.");
		return;
	}
	else{
		dataStrings[targetIndex] = newData;
	}
}

vector<string> Tuple::getDataStrings() const{
	return dataStrings;
}

tupleComp::tupleComp(){
  vector<size_t> keys;
  keys.push_back(0);
  sort_keys = keys;
}

tupleComp::tupleComp(vector<size_t> keys){
  sort_keys = keys;
}

bool tupleComp::operator()(const Tuple &a, const Tuple &b) const{
  for(unsigned int i = 0; i < sort_keys.size(); ++i){
    if(a.getDataStrings()[sort_keys[i]] < b.getDataStrings()[sort_keys[i]]){
      return true;
    }
  }
  return false;
}

bool operator==(const Tuple &a, const Tuple &b){
  return a.dataStrings == b.dataStrings;
}

bool operator!=(const Tuple &a, const Tuple &b){
  return a.dataStrings != b.dataStrings;
}
