#include "Attribute.h"
using namespace std;

Attribute::Attribute(){		//Do we need default constructor for attribute? - VA
	value = string(); 
	dataType = dataTypes();
}

Attribute::Attribute(string newValue, dataTypes newType){
	value = newValue;
	dataType = newType;
}

Attribute::Attribute(Attribute const &A){
	value = A.value;
	dataType = A.dataType;
}

string Attribute::getValue() const{
	return value;
}

dataTypes Attribute::getDataType() const{
	return dataType;
}

void Attribute::renameAttr(string newValue, dataTypes newType){
	value = newValue;
	dataType = newType;
}

bool operator==(const Attribute &a, const Attribute &b){
  return (a.getValue() == b.getValue() && a.getDataType() == b.getDataType());
}

bool operator!=(const Attribute &a, const Attribute &b){
  return (a.getValue() != b.getValue() || a.getDataType() != b.getDataType());
}
