#ifndef RELATION_H
#define RELATION_H

#include <cstdio>
#include <vector>
#include "Tuple.h"
#include "Attribute.h"

using namespace std;

class Relation{
		string name;
		vector<Tuple> rows;
		vector<Attribute> columns;
		vector<size_t> keys;
	public:
		Relation(); //constructor
		Relation(string c_name, vector<Tuple> c_rows, vector<Attribute> c_columns, vector<size_t> c_keys);
		Relation(Relation const &A); //copy constructor
		void addTuple(Tuple T);
		void addAttribute(Attribute A, string defaultValue); //A is the attribute to be added, default value is the value used to initially populate the tuples
		void deleteTuple(Tuple T); //This may need different parameters
		void deleteTuple(size_t index);
		Tuple getTuple(Tuple T) const;
		Tuple getTuple(size_t index) const;
		vector<Tuple> getRows() const;
		vector<Attribute> getColumns() const;
		vector<size_t> getKeys() const;
		bool isKey(size_t id);
		string getName() const;
		bool equalContents(const Relation &b) const; //checks if Relations contain the same Tuples, not order sensitive
		friend bool operator==(const Relation &a, const Relation &b);
		friend bool operator!=(const Relation &a, const Relation &b);
		bool empty() const;
};

#endif /*RELATION_H*/
