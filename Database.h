#include <stdio.h>
#include "Relation.h"
#include "Tuple.h"

using namespace std;

class Database{
		vector<Relations> dbase;
	public:
		Database();
		Database(vector<Relations> d);
		void addRelation(Relation r);
		void deleteRelation(string relationName); //This may change, but I'm implementing it [PMG]
		
		//Relational Functions, the rest are specific to a single Relation and are members of Relation class
		Relation set_union(Relation A, Relation B); //Relation A for this function is the one operated on (i.e. A.set_union(B))
		Relation set_difference(Relation A, Relation B); //see above
		Relation cartesian_product(Relation A, Relation B); //see above. May need to be modified once we define how we are doing "Tuples of pairs"
		
		void Show(string r);	//Show the relation
		int RelationExists(string r); 	//Check if relation exists in dbase. created to avoid duplicate code in show, insert functions
		void Insert(string r, Tuple t); //relation r and the tuple t that needs to be inserted into the relation
		
		void Open(string r); //Open relation r - requires file IO
		void Close(string r);
		
		void Exit();
};
