#include "Tuple.h"
using namespace std;

Tuple::Tuple(){
	dataStrings = vector<string>;
}

Tuple::Tuple(vector<string> newDataVec){
	dataStrings = newDataVec;
}

void Tuple::addData(string newData){
	dataString.push_back(newData);
}

void Tuple::changeDataMember(int targetIndex, string newData){
	if(targetIndex > dataStrings.size()-1){
		printf("Error: index out of bounds. The tuple is not that big. Use addData instead.");
		return;
	}
	else{
		dataString[targetIndex] = newData;
	}
}

vector<string> getDataStrings(){
	return dataStrings;
}