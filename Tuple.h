#include <stdio.h>
#include <string.h>
using namespace std;

class Tuple{
		vector<string> dataStrings;
	public:
		addData(string newData);
		changeDataMember(int targetColumn, string newData);
		Tuple(vector<string> newDataVec);
		Tuple();
		~Tuple();
};