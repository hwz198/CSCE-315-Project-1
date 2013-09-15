#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <cstdio>
#include <string>
using namespace std;

enum dataTypes {str, in, d};

class Attribute{
		string value;
		dataTypes dataType;
		int stringLimit; //should be -1 if its not a string
	public:
		string getValue() const;
		dataTypes getDataType() const;
		int maxLength() const;
		void renameAttr(string newValue, dataTypes newType, int newLimit = -1);
		Attribute(string newValue, dataTypes newType, int newLimit = -1); //contructor
		Attribute(); //constructor
		Attribute(Attribute const &A); //copy constructor
		friend bool operator==(const Attribute &a, const Attribute &b);
		friend bool operator!=(const Attribute &a, const Attribute &b);
};

#endif /*ATTRIBUTE_H*/
