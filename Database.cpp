#include <algorithm>
#include <iostream>
#include "Database.h"
using namespace std;

Database::Database(){
	dbase = vector<Relation>();
}

Database::Database(vector<Relation> d){
	dbase = d;
}

void Database::addRelation(Relation r){
  for(int i=0; i<dbase.size(); ++i){
		if(dbase[i].getName()==r.getName()){
			printf("\nA relation of that name already exists. Please try again. \n");
			return;
		}
	}
	dbase.push_back(r);
	return;
}

void Database::deleteRelation(string relationName){
  for(int i=0; i<dbase.size(); ++i){
		if(dbase[i].getName()==r.getName()){
			dbase.erase(dbase.begin()+i);
			return;
		}
	}
	printf("\n Relation to delete not found. Please try again. \n");
	return;
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
	for(int i=0; i<dbase[index].getRows().size(); ++i)
	{
		{
                  for(int j=0; j<dbase[index].getRows().getDataStrings.size(); ++j)
			{
                          cout << dbase[index].getRows()[i].getdataStrings()[j] << ' ';
			}
                  cout << '\n';
		}
	}	
}

int Database::RelationExists(string r)
{
	bool exist = false; //check if relation exists in dbase -- Need to edit this for views after our discussion today. 
	int index;
	for(int i = 0; i<dbase.size(); ++i){
		if( r == dbase[i].getName() ){
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
          cout << "Either the relation " << r << " does not exist or is not open\n";
		return;
	}
	
	dbase[index].getRows().addTuple(t);
}

void Database::Open(string r)
{
	int check = RelationExists(r);	//Check if relation is already in memory
	if(check != -1){
          cout << "Database " << r << " is already open\n";
		return;
	}
	
	//Rest of the function requires file IO - to be implemented later
}

void Database::Close(string r)
{
	int index = RelationExists(r);	//Check if relation is already in memory
	if(index == -1){
          cout << "Error. Database " << r << " does not exist in memory!\n";
		return;
	}

	//Write to disk - file IO
		
		

	dbase.erase(dbase.begin() + index);			//Delete from memory
}

void Database::Exit()
{
	printf("Shutting down the database");	//Do we need to delete all the files? - VA
	exit(-1);
}

Relation Database::set_union(Relation A, Relation B){
  if(A.getColumns() != B.getColumns()){ //not union compatible
    return Relation();
  }

  vector<Tuple> union_rows;
  vector<Tuple> Arows = A.getRows();
  vector<Tuple> Brows = B.getRows();

  sort(Arows.begin(), Arows.end(), tupleComp());
  sort(Brows.begin(), Brows.end(), tupleComp());
  std::set_union(Arows.begin(), Arows.end(),
            Brows.begin(), Brows.end(),
            back_inserter(union_rows), tupleComp());

  return Relation("ABUnion", union_rows, A.getColumns());
}

Relation Database::set_difference(Relation A, Relation B){
  if(A.getColumns() != B.getColumns()){ //not union compatible
    //return empty relation
  }

  vector<Tuple> difference_rows;
  vector<Tuple> Arows = A.getRows();
  vector<Tuple> Brows = B.getRows();

  sort(Arows.begin(), Arows.end(), tupleComp());
  sort(Brows.begin(), Brows.end(), tupleComp());
  std::set_difference(Arows.begin(), Arows.end(),
            Brows.begin(), Brows.end(),
            back_inserter(difference_rows), tupleComp());

  return Relation("ABDifference", difference_rows, A.getColumns());
}

Relation cartesian_product(Relation A, Relation B){
  vector<Attribute> cross_columns = A.getColumns();
  vector<Attribute> Bcols = B.getColumns();
  cross_columns.reserve(cross_columns.size()+Bcols.size());
  cross_columns.insert(cross_columns.end(), Bcols.begin(), Bcols.end());

  vector<Tuple> cross_rows;
  vector<Tuple> Arows = A.getRows();
  vector<Tuple> Brows = B.getRows();
  for(size_t i = 0; i < Arows.size(); ++i){
    vector<string> Atuple = Arows[i].getDataStrings();
    for(size_t j = 0; j < Brows.size(); ++j){
      vector<string> Btuple = Brows[j].getDataStrings();
      Atuple.reserve(Atuple.size() + Btuple.size());
      Atuple.insert(Atuple.end(), Btuple.begin(), Btuple.end());
      cross_rows.push_back(Atuple);
    }
  }

  return Relation("ABcartesian", cross_rows, cross_columns);
}
