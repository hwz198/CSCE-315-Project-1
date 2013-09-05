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
