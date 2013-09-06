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
		if(dbase[i].getName()==relationName){
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
                  for(int j=0; j<dbase[index].getRows()[i].getDataStrings().size(); ++j)
			{
                          cout << dbase[index].getRows()[i].getDataStrings()[j] << ' ';
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
	
	dbase[index].addTuple(t);
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

/* param A: Relation selecting from
   param new_rel_name: Name of returned relation
   param attrib_val: Name (or value) or attribute in A used for comparison
   param op: Operator used in comparison
   param condition: Attribute value to compare to */
Relation Database::selection(Relation A, string new_rel_name, string attrib_val,
                             logic_operator op, Attribute condition){
  vector<Attribute> Acols = A.getColumns();
  int index = -1;
  for(size_t i = 0; i < Acols.size(); ++i){
    if(Acols[i].getValue() == attrib_val){	//attribute with matching name exists
      index = i;
      break;
    }
  }
  if(index == -1)
    return Relation();	//empty relation

  Attribute Aattrib = Acols[index];

  if(Aattrib.getDataType() != condition.getDataType()) //same name, different data type
    return Relation(); //empty relation

  vector<Tuple> Arows = A.getRows();
  Relation sel(new_rel_name, vector<Tuple>(), Acols);

  switch(op){
  case g:
    for(size_t i = 0; i < Arows.size(); ++i){
      //compare to Tuple value in index of Attribute to compare to
      if(condition.getValue() > Arows[i].getDataStrings()[index]){
        sel.addTuple(Arows[i]);
      }
    }
    break;
  case l:
    for(size_t i = 0; i < Arows.size(); ++i){
      //compare to Tuple value in index of Attribute to compare to
      if(condition.getValue() > Arows[i].getDataStrings()[index]){
        sel.addTuple(Arows[i]);
      }
    }
    break;
  case ge:
    for(size_t i = 0; i < Arows.size(); ++i){
      //compare to Tuple value in index of Attribute to compare to
      if(condition.getValue() >= Arows[i].getDataStrings()[index]){
        sel.addTuple(Arows[i]);
      }
    }
    break;
  case le:
    for(size_t i = 0; i < Arows.size(); ++i){
      //compare to Tuple value in index of Attribute to compare to
      if(condition.getValue() <= Arows[i].getDataStrings()[index]){
        sel.addTuple(Arows[i]);
      }
    }
    break;
  case e:
    for(size_t i = 0; i < Arows.size(); ++i){
      //compare to Tuple value in index of Attribute to compare to
      if(condition.getValue() == Arows[i].getDataStrings()[index]){
        sel.addTuple(Arows[i]);
      }
    }
    break;
  case ne:
    for(size_t i = 0; i < Arows.size(); ++i){
      //compare to Tuple value in index of Attribute to compare to
      if(condition.getValue() != Arows[i].getDataStrings()[index]){
        sel.addTuple(Arows[i]);
      }
    }
    break;
  }

  return sel;
}


/* param A: Relation to project from
   param new_rel_name: Name of returned relation
   attrib_vals: Names (or values) of attributes to project from A */
Relation Database::projection(Relation A, string new_rel_name,
                              vector<string> attrib_vals){
  vector<size_t> indices;
  vector<Attribute> Acols = A.getColumns();
  vector<Tuple> Arows = A.getRows();
  vector<Attribute> AprojCols;
  vector<Tuple> AprojRows; 

  for(size_t i = 0; i < Acols.size(); ++i){
    //attrib_vals contains Acols[i]
    if(find(attrib_vals.begin(), attrib_vals.end(), Acols[i].getValue()) != attrib_vals.end()){
      indices.push_back(i);
    }
  }

  if(indices.empty())
    return Relation();

  for(size_t i = 0; i < indices.size(); ++i){
    AprojCols.push_back(Acols[indices[i]]);
  }

  for(size_t i = 0; i < Arows.size(); ++i){
    Tuple tup;
    vector<string> dataStrings = Arows[i].getDataStrings();
    for(size_t j = 0; j < indices.size(); ++j){
      tup.addData(dataStrings[indices[j]]);
    }
    AprojRows.push_back(tup);
  }

  return Relation(new_rel_name, AprojRows, AprojCols);
}

/* param A: Relation to rename attributes from
   param new_rel_name: Name for returned relations
   param new_attrib_vals: Vector of new names for each attribute in A */
Relation Database::rename(Relation A, string new_rel_name,
                          vector<string> new_attrib_vals){
  vector<Attribute> Acols = A.getColumns();
  vector<Attribute> new_cols;
  if(Acols.size() != new_attrib_vals.size())
    return Relation();

  for(size_t i = 0; i < new_attrib_vals.size(); ++i){
    Attribute attr = Acols[i];
    attr.renameAttr(new_attrib_vals[i], Acols[i].getDataType());
    new_cols.push_back(attr);
  }

  return Relation(new_rel_name, A.getRows(), new_cols);
}


Relation Database::relation_union(Relation A, Relation B){
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

Relation Database::relation_difference(Relation A, Relation B){
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
