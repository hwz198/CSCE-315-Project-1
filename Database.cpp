#include "Database.h"
using namespace std;

Relation Database::set_union(Relation A, Relation B){
  if(A.columns != B.columns){
    //return Empty relation
  }

void Database::Show(string r)
{
	bool exist = false; //check if relation exists in Dbase -- Need to edit this for views after our discussion today. 
	int index;
	for(int i = 0; i<dBase.size();i++){
		if( r == dBase[i].name ){
			exist = true;
			index = i;
			break;
		}
	}
	if(exist){
	//Show the relation in dBase
	for(int i=0;i<dBase[index].rows.size();i++)
		{
			for(int j=0;j<dBase[index].rows.dataStrings.size();j++)
			{
				printf("%s ",dBase[index].rows[i].dataStrings[j]);
			}
			printf("\n");
		}
	}
	else
		printf("Either the relation does not exist or is not open");
}


