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
