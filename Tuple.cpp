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

bool tupleComp::operator()(const Tuple &a, const Tuple &b) const{
  //size_t sort_key = keys[0]; //no way to get keys at this level
  size_t sort_key = 0;
  return a.getDataStrings()[sort_key] < b.getDataStrings()[sort_key];
}
