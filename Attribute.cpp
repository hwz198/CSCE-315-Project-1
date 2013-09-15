#include "Attribute.h"
using namespace std;

Attribute::Attribute(){		//Empty Constructor
	value = string(); 
	dataType = dataTypes();
	stringLimit = int();
}

Attribute::Attribute(string newValue, dataTypes newType, int newLimit){ //Initialized Constructor
	value = newValue;
	dataType = newType;
	stringLimit = newLimit;
}

Attribute::Attribute(Attribute const &A){ //Copy Constructor
	value = A.getValue();
	dataType = A.getDataType();
	stringLimit = A.maxLength();
}

string Attribute::getValue() const{
	return value;
}

dataTypes Attribute::getDataType() const{
	return dataType;
}

int Attribute::maxLength() const{
	return stringLimit;
}

void Attribute::renameAttr(string newValue, dataTypes newType, int newLimit){
	value = newValue;
	dataType = newType;
	stringLimit = newLimit;
}

bool operator==(const Attribute &a, const Attribute &b){
  return (a.getValue() == b.getValue() && a.getDataType() == b.getDataType());
}

bool operator!=(const Attribute &a, const Attribute &b){
  return (a.getValue() != b.getValue() || a.getDataType() != b.getDataType());
}
