#include "Database.h"
using namespace std;

Database::Database(){
	dbase = vector<Relations>();
}

Database::Database(vector<Relations> d){
	dbase = d;
}

void Database::addRelation(Relation r){
	for(int i=0; i++; i<dbase.size()){
		if(dbase[i].getName()==r.getName()){
			printf("\nA relation of that name already exists. Please try again. \n");
			return;
		}
	}
	dbase.push_back(r);
	return;
}

void deleteRelation(string relationName){
	for(int i=0; i++; i<dbase.size()){
		if(dbase[i].getName()==r.getName()){
			dbase.erase(dbase.begin()+i);
			return;
		}
	}
	printf("\n Relation to delete not found. Please try again. \n");
	return;
}


Relation Database::set_union(Relation A, Relation B){
  if(A.columns != B.columns){
    //return Empty relation
  }

void Database::Show(string r)
{
	int index = RelationExists(r);	//Check if relation exists and get the index
	if( index == -1 )
	{
		printf("Either the relation does not exist or is not open");
		return;
	}
	//Show the relation in dBase
	for(int i=0;i<dbase[index].rows.size();i++)
	{
		{
			for(int j=0;j<dbase[index].rows.dataStrings.size();j++)
			{
				printf("%s ",dbase[index].getRows()[i].getdataStrings()[j]);	//CHECK SYNTAX LATER - VA
			}
			printf("\n");
		}
	}	
}

int Database::RelationExists(string r)
{
	bool exist = false; //check if relation exists in dbase -- Need to edit this for views after our discussion today. 
	int index;
	for(int i = 0; i<dbase.size();i++){
		if( r == dbase[i].name ){
			exist = true;
			index = i;
			break;
		}
	}
	if(exist)
		return index;
	else{
		index = -1;
		return index;
	}
}

void Database::Insert(string r, Tuple t)
{
	int index = RelationExists(r);
	if( index == -1 )
	{
		printf("Either the relation does not exist or is not open");
		return;
	}
	
	dbase[index].rows.push_back(t);
	
}
