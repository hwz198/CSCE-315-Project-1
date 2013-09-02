#include <stdio.h>
#include "Tuple.h"
#include "Attribute.h"
//put more includey things here
using namespace std;

class Relation{
		vector<Tuple> rows;
		vector<Attribute> columns;
	public:
		vector<Tuple> selection(string condition); //When this function is made, you may need to update the condition to be the proper type
		Relation projection(vector<Attribute> columns);
		void rename(Attribute target, string newvalue);
		Relation set_union(Relation B); //Relation A for this function is the one operated on (i.e. A.set_union(B))
		Relation set_difference(Relation B); //see above
		Relation cartesian_product(Relation B); //see above. May need to be modified once we define how we are doing "Tuples of pairs"
		Relation(); //constructor
		~Relation(); //destructor
		//Do we need accessor functions?
}