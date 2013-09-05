#include <stdio.h>
#include <string.h>
using namespace std;

class Tuple{
		vector<string> dataStrings;
	public:
		void addData(string newData);
		void changeDataMember(int targetIndex, string newData);
		Tuple(vector<string> newDataVec);
		Tuple();
		vector<string> getDataStrings(); 	//accessor function for dataStrings
};