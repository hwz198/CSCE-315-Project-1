#include <stdio.h>
#include <string.h>
using namespace std;

enum dataTypes {str, i, d};

class Attribute{
		string value;
		dataTypes dataType;
	public:
		string getValue();
		dataTypes getDataType();
		void renameAttr(string newValue, dataTypes newType);
		Attribute(string newValue, dataTypes newType); //contructor
		Attribute(); //constructor
		Attribute(Attribute A); //copy constructor
};
