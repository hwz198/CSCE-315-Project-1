#ifndef TUPLE_H
#define TUPLE_H

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
		friend bool operator==(const Tuple &a, const Tuple &b);
		friend bool operator!=(const Tuple &a, const Tuple &b);
};

struct tupleComp{
  bool operator()(const Tuple &a, const Tuple &b) const;
};

#endif /*TUPLE_H*/
