#include "Attribute.h"
using namespace std;

Attribute::Attribute(){
	value = string();
	dataType = dataType();
}

Attribute::Attribute(string newValue, dataTypes newType){
	value = newValue;
	dataType = newType;
}

Attribute::Attribute(Attribute A){
	value = A.value;
	dataType = A.dataType;
}

string Attribute::getValue(){
	return value;
}

dataTypes Attribute::getDataType(){
	return dataType;
}

void Attribute::renameAttr(string newValue, dataTypes newType){
	value = newValue;
	dataType = newType;
}