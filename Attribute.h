#include <stdio.h>
#include <string.h>
using namespace std;

class Attribute{
		string value;
		string dataType;
	public:
		string getValue();
		string getDataType();
		void renameAttr(string newValue, string newType);
		Attribute(string newValue, string newType); //contructor
		Attribute();
		~Attribute(); //destructor
};