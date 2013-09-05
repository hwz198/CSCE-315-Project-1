#include <stdio.h>
#include <vector>
#include "Tuple.h"
#include "Attribute.h"
//put more includey things here
using namespace std;

class Relation{
		string name;
		vector<Tuple> rows;
		vector<Attribute> columns;
		vector<size_t> keys;
	public:
		//Other relational functions
		vector<Tuple> selection(string condition); //When this function is made, you may need to update the condition to be the proper type
		Relation projection(vector<Attribute> columns);
		void rename(Attribute target, string newvalue);
		Relation(); //constructor
		Relation(string c_name, Vector<Tuple> c_rows, Vector<Attribute> c_columns);
		Relation(Relation A); //copy constructor
		void addTuple(Tuple T);
		void addAttribute(Attribute A, string defaultValue); //A is the attribute to be added, default value is the value used to initially populate the tuples
		vector<Tuple> getRows();
		vector<Attribute> getColumns();
		vector<size_t> getKeys();
		bool isKey(size_t id);
		string getName();
		bool tupleComp(const Tuple &a, const Tuple &b);
};
