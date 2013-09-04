#include <stdio.h>
#include "Relation.h"

using namespace std;

class Database{
		vector<Relations> dbase;
	public:
		Database();
		~Database():
		addRelation(Relation r);
		deleteRelation(int relationIndex); //This may change, but I'm implementing it [PMG]
		
		//Relational Functions, the rest are specific to a single Relation and are members of Relation class
		Relation set_union(Relation A, Relation B); //Relation A for this function is the one operated on (i.e. A.set_union(B))
		Relation set_difference(Relation A, Relation B); //see above
		Relation cartesian_product(Relation A, Relation B); //see above. May need to be modified once we define how we are doing "Tuples of pairs"
};


Relation Database::set_union(Relation A, Relation B){
  if(A.columns != B.columns){
    //return Empty relation
  }
  
