#ifndef DATABASE_H
#define DATABASE_H

#include <cstdio>
#include <vector>
#include "Relation.h"
#include "Tuple.h"

using namespace std;

//                  {>, <, >=, <=, ==, !=}
enum logic_operator {g, l, ge, le, e, ne};

class Database{
		vector<Relation> dbase;
	public:
		Database();
		Database(vector<Relation> d);
		void addRelation(Relation r);
		void deleteRelation(string relationName); //This may change, but I'm implementing it [PMG]
		Relation getRelation(size_t index);
		Relation getRelation(string relationName);
		Relation *getRelationRef(size_t index);
		Relation *getRelationRef(string relationName);
		int numberOfRelations();
		
		//update and delete functions
		vector<int> where(Relation A, string attrib_val,logic_operator op, Attribute condition);

		void deleteTuples(Relation A, string attrib_val, logic_operator op, Attribute condition);
		void updateTuples(Relation A, string attrib_val, logic_operator op, Attribute condition, string updateTo);

		//Relational Functions, the rest are specific to a single Relation and are members of Relation class
		Relation selection(Relation A, string new_rel_name,
                                   string attrib_val, logic_operator op,
                                   Attribute condition);
		Relation projection(Relation A, string new_rel_name,
                                    vector<string> attrib_vals);
		Relation rename(Relation A, string new_rel_name,
                                vector<string> new_attrib_vals);
		Relation relation_union(Relation A, Relation B); //Relation A for this function is the one operated on (i.e. A.set_union(B))
		Relation relation_difference(Relation A, Relation B); //see above
		Relation cross_product(Relation A, Relation B); //see above. May need to be modified once we define how we are doing "Tuples of pairs"
		
		void Show(const Relation &r) const;
		void Show(string r) const;	//Show the relation
		void Show(size_t index) const;
		int RelationExists(string r) const; 	//Check if relation exists in dbase. created to avoid duplicate code in show, insert functions
		void Insert(string r, Tuple t); //relation r and the tuple t that needs to be inserted into the relation
		
		void Open(string r); //Open relation r - requires file IO
		void Close(string r);
		
		void Exit();
};

#endif /*DATABASE_H*/
