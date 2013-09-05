#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <cstdio>
#include <string>
using namespace std;

enum dataTypes {str, i, d};

class Attribute{
		string value;
		dataTypes dataType;
	public:
		string getValue() const;
		dataTypes getDataType() const;
		void renameAttr(string newValue, dataTypes newType);
		Attribute(string newValue, dataTypes newType); //contructor
		Attribute(); //constructor
		Attribute(Attribute const &A); //copy constructor
		friend bool operator==(const Attribute &a, const Attribute &b);
		friend bool operator!=(const Attribute &a, const Attribute &b);
};

#endif /*ATTRIBUTE_H*/
