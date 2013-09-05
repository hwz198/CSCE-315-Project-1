#include <cstdio>
#include <string>
#include <vector>
using namespace std;

class Tuple{
		vector<string> dataStrings;
	public:
		void addData(string newData);
		void changeDataMember(int targetIndex, string newData);
		Tuple(vector<string> newDataVec);
		Tuple();
		vector<string> getDataStrings() const; 	//accessor function for dataStrings
};
