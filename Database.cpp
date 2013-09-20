#include <algorithm>
#include <iostream>
#include <cstdlib>
#include "Database.h"
#include "parser.h"
using namespace std;

Database::Database(){ //Empty Constructor
	dbase = vector<Relation>();
}

Database::Database(vector<Relation> d){ //Initialized Constructor
	dbase = d;
}

void Database::addRelation(Relation r){
  for(int i=0; i<dbase.size(); ++i){  //Need to check that there isn't already a same named relation
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
	printf("\n Relation to delete not found. Please try again. \n"); // if the delete was unsuccessful, we need to notify the user
	return;
}

Relation Database::getRelation(size_t index){
  if(index < dbase.size()){
    return dbase[index];
  } else {
    cerr << "Index " << index << " out of bounds.\n";
    return Relation();
  }
}

Relation Database::getRelation(string relationName){
  for(size_t i = 0; i < dbase.size(); ++i){
    if(dbase[i].getName() == relationName){
      return dbase[i];
    }
  }
  cerr << "Relation '" << relationName << "' not found.\n";
  return Relation();
}

Relation *Database::getRelationRef(size_t index){
  if(index < dbase.size()){
    return &(dbase[index]);
  } else {
    cerr << "Index " << index << " out of bounds.\n";
    return new Relation(); //this is probably bad
  }
}

Relation *Database::getRelationRef(string relationName){
  for(size_t i = 0; i < dbase.size(); ++i){
    if(dbase[i].getName() == relationName){
      return &(dbase[i]);
    }
  }
  cerr << "Relation '" << relationName << "' not found.\n";
  return new Relation(); //also maybe bad. YAY POINTERS!
}

int Database::numberOfRelations(){
	return dbase.size();
}

void Database::Show(const Relation &r) const{
  //Show the relation in dBase
  for(int i = 0; i < r.getColumns().size(); ++i){
    cout << r.getColumns()[i].getValue() << '\t';
  }
  cout << endl << endl;

  for(int i=0; i<r.getRows().size(); ++i)
    {
      for(int j=0; j<r.getRows()[i].getDataStrings().size(); ++j)
        {
          cout << r.getRows()[i].getDataStrings()[j] << '\t';
        }
      cout << '\n';
    }
}


void Database::Show(string r) const
{
  int index = RelationExists(r);	//Check if relation exists and get the index
  if( index == -1 )
    {
      printf("Either the relation does not exist or is not open");
      return;
    }
  Database::Show(dbase[index]);
}

void Database::Show(size_t index) const{
  if(index < dbase.size())
    return Database::Show(dbase[index]);
}

int Database::RelationExists(string r) const
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
          cerr << "Either the relation " << r << " does not exist or is not open\n";
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
	
	ofstream file;
	Parser p;
	string l;
	file.open(r + ".db");
	if(file.is_open()){
		while(getline(file,l)){
			p.parse(l);
		}
		file.close();
	}
	//Rest of the function requires file IO - to be implemented later
}

void Database::Write(string r)
{
	int index = RelationExists(r);	//Check if relation is already in memory
	if(index == -1){
          cout << "Error. Database " << r << " does not exist in memory!\n";
		return;
	}
	
	fileIOOp F(getRelation(r));
	F.writeToFile();
}

void Database::Close(string r)
{
	int index = RelationExists(r);	//Check if relation is already in memory
	if(index == -1){
          cout << "Error. Database " << r << " does not exist in memory!\n";
		return;
	}

	//Write to disk - file IO
	Write(r);
	printf("Closing database. \n");
	dbase.erase(dbase.begin() + index);			//Delete from memory
}

void Database::Exit()
{
	printf("Shutting down the database");
	exit(-1);
}

//////UPDATE AND DELETE ---------//////////////////////////////////////////////


void Database::deleteTuples(Relation A, string attrib_val, logic_operator op, Attribute condition)
{

	vector<int> rows_to_delete = where(A, attrib_val, op, condition);

	int rel = RelationExists(A.getName());

	if(rel==-1){
		printf("RELATION DOES NOT EXIST");
		return;
	}
	else{
		vector<Tuple> to_delete;
		int j=0;
		for(int i=0;i<rows_to_delete.size();i++)
		{
			Tuple t = dbase[rel].getTuple(rows_to_delete[i]);
			to_delete.push_back(t);
		}
		for(int i=0;i<rows_to_delete.size();i++)
		{
			dbase[rel].deleteTuple(to_delete[i]);			
		}

	}

}

void Database::updateTuples(Relation A, string attrib_val, logic_operator op, Attribute condition, string updateTo)
{
	 vector<Attribute> Acols = A.getColumns();
  	 int index = -1;
	 for(size_t i = 0; i < Acols.size(); ++i){
		  if(Acols[i].getValue() == attrib_val){	//attribute with matching name exists
		 	index = i;
		 	break;
    		  }
	 }
	 if(index==-1){
	 	printf("Attribute does not exist\n");
	 	return;
	}

	vector<int> rows_to_delete = where(A, attrib_val, op, condition);

	int rel = RelationExists(A.getName());

	if(rel==-1){
		printf("RELATION DOES NOT EXIST\n");
		return;
	}
	else{
		vector<Tuple> to_delete;
		for(int i=0;i<rows_to_delete.size();i++)
		{
			Tuple t = dbase[rel].getTuple(rows_to_delete[i]);
			to_delete.push_back(t);
		}
		for(int i=0;i<rows_to_delete.size();i++)
		{
			dbase[rel].updateTuple(to_delete[i],index,updateTo);			
		}

	}
}


vector<int> Database::where(Relation A, string attrib_val,
                             logic_operator op, Attribute condition)
{
	vector<int> ret;
  if(A.empty()){
    cerr << "Passed empty relation\n";
    return ret;	//EMPTY
  }

  vector<Attribute> Acols = A.getColumns();
  int index = -1;
  for(size_t i = 0; i < Acols.size(); ++i){
    if(Acols[i].getValue() == attrib_val){	//attribute with matching name exists
      index = i;
      break;
    }
  }
  if(index == -1){
    cerr << "Attribute '" << attrib_val << "' not found.\n";
    return ret;
  }

  Attribute Aattrib = Acols[index];

  if(Aattrib.getDataType() != condition.getDataType()){ //same name, different data type
    cerr << "Attributes to compare are not of the same data type\n";
    return ret; //empty relation
  }

  vector<Tuple> Arows = A.getRows();
 
  // Lots of similar code ahead. 3 switch statements, 1 for each dataType
  if(Aattrib.getDataType() == in){ //int
    switch(op){
    case g:
      for(size_t i = 0; i < Arows.size(); ++i){
        //compare to Tuple value in index of Attribute to compare to
        if(atoi(Arows[i].getDataStrings()[index].c_str()) > atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    case l:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) < atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    case ge:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) >= atoi(condition.getValue().c_str())){
         ret.push_back(i);
        }
      }
      break;
    case le:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) <= atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    case e:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) == atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    case ne:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) != atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    }

  } else if(Aattrib.getDataType() == d){ //double

    switch(op){
    case g:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) > atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    case l:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) < atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    case ge:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) >= atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    case le:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) <= atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    case e:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) == atoi(condition.getValue().c_str())){
			ret.push_back(i);
        }
      }
      break;
    case ne:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) != atoi(condition.getValue().c_str())){
          ret.push_back(i);
        }
      }
      break;
    }

  } else { //string

    switch(op){
    case g:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] > condition.getValue()){
          ret.push_back(i);
        }
      }
      break;
    case l:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] < condition.getValue()){
          ret.push_back(i);
        }
      }
      break;
    case ge:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] >= condition.getValue()){
          ret.push_back(i);
        }
      }
      break;
    case le:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] <= condition.getValue()){
          ret.push_back(i);
        }
      }
      break;
    case e:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] == condition.getValue()){
          ret.push_back(i);
        }
      }
      break;
    case ne:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] != condition.getValue()){
          ret.push_back(i);
        }
      }
      break;
    }
  }

  return ret;
}

//-------------------------------------------------------------------------//////



/* param A: Relation selecting from
   param new_rel_name: Name of returned relation
   param attrib_val: Name (or value) or attribute in A used for comparison
   param op: Operator used in comparison
   param condition: Attribute value to compare to */
Relation Database::selection(Relation A, string new_rel_name, string attrib_val,
                             logic_operator op, Attribute condition){
  if(A.empty()){
    cerr << "Passed empty relation\n";
    return Relation();
  }

  vector<Attribute> Acols = A.getColumns();
  int index = -1;
  for(size_t i = 0; i < Acols.size(); ++i){	//find attrib_val in A
    if(Acols[i].getValue() == attrib_val){
      index = i;
      break;
    }
  }
  if(index == -1){
    cerr << "Attribute '" << attrib_val << "' not found.\n";
    return Relation();	//empty relation
  }

  Attribute Aattrib = Acols[index]; //attribute in A that matches attrib_val

  if(Aattrib.getDataType() != condition.getDataType()){ //same name, different data type
    cerr << "Attributes to compare are not of the same data type\n";
    return Relation(); //empty relation
  }

  vector<Tuple> Arows = A.getRows();
  Relation sel(new_rel_name, vector<Tuple>(), Acols, A.getKeys()); //Relation to be returned

  // Lots of similar code ahead. 3 switch statements, 1 for each dataType
  if(Aattrib.getDataType() == in){ //int
    switch(op){
    case g:
      for(size_t i = 0; i < Arows.size(); ++i){
        //compare to Tuple value in index of Attribute to compare to
        if(atoi(Arows[i].getDataStrings()[index].c_str()) > atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case l:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) < atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case ge:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) >= atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case le:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) <= atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case e:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) == atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case ne:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) != atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    }

  } else if(Aattrib.getDataType() == d){ //double

    switch(op){
    case g:
      for(size_t i = 0; i < Arows.size(); ++i){
        //compare to Tuple value in index of Attribute to compare to
        if(atoi(Arows[i].getDataStrings()[index].c_str()) > atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case l:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) < atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case ge:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) >= atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case le:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) <= atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case e:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) == atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case ne:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(atoi(Arows[i].getDataStrings()[index].c_str()) != atoi(condition.getValue().c_str())){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    }

  } else { //string

    switch(op){
    case g:
      for(size_t i = 0; i < Arows.size(); ++i){
        //compare to Tuple value in index of Attribute to compare to
        if(Arows[i].getDataStrings()[index] > condition.getValue()){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case l:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] < condition.getValue()){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case ge:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] >= condition.getValue()){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case le:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] <= condition.getValue()){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case e:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] == condition.getValue()){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    case ne:
      for(size_t i = 0; i < Arows.size(); ++i){
        if(Arows[i].getDataStrings()[index] != condition.getValue()){
          sel.addTuple(Arows[i]);
        }
      }
      break;
    }
  }

  return sel;
}


/* param A: Relation to project from
   param new_rel_name: Name of returned relation
   attrib_vals: Names (or values) of attributes to project from A */
Relation Database::projection(Relation A, string new_rel_name,
                              vector<string> attrib_vals){
  if(A.empty()){
    cerr << "Passed empty Relation\n";
    return Relation();
  }

  vector<size_t> indices; //indices of Attributes in A that exist in attrib_vals
  vector<Attribute> Acols = A.getColumns();
  vector<Tuple> Arows = A.getRows();
  vector<Attribute> AprojCols; //columns projected to
  vector<Tuple> AprojRows; //rows projected to

  for(size_t i = 0; i < Acols.size(); ++i){
    //attrib_vals contains Acols[i]
    if(find(attrib_vals.begin(), attrib_vals.end(), Acols[i].getValue()) != attrib_vals.end()){
      indices.push_back(i);
    }
  }

  if(indices.empty()){
    cerr << "No matching attribute values found\n";
    return Relation();
  }

  for(size_t i = 0; i < indices.size(); ++i){
    AprojCols.push_back(Acols[indices[i]]); //add matching Attributes in A to projected columns
  }

  //construct Tuples from A that contain only the columns to project
  for(size_t i = 0; i < Arows.size(); ++i){
    Tuple tup;
    vector<string> dataStrings = Arows[i].getDataStrings();
    for(size_t j = 0; j < indices.size(); ++j){
      tup.addData(dataStrings[indices[j]]);
    }
    AprojRows.push_back(tup);
  }

  return Relation(new_rel_name, AprojRows, AprojCols, A.getKeys());
}

/* param A: Relation to rename attributes from
   param new_rel_name: Name for returned relations
   param new_attrib_vals: Vector of new names for each attribute in A */
Relation Database::rename(Relation A, string new_rel_name,
                          vector<string> new_attrib_vals){
  if(A.empty()){
    cerr << "Passed empty Relation\n";
    return Relation();
  }

  vector<Attribute> Acols = A.getColumns();
  vector<Attribute> new_cols; //renamed Attributes
  if(Acols.size() != new_attrib_vals.size()){
    cerr << "Number of new attributes names not equal to number of current attributes.\n";
    return Relation();
  }

  //rename each Attribute and add to new_cols
  for(size_t i = 0; i < new_attrib_vals.size(); ++i){
    Attribute attr = Acols[i];
    attr.renameAttr(new_attrib_vals[i], Acols[i].getDataType());
    new_cols.push_back(attr);
  }

  return Relation(new_rel_name, A.getRows(), new_cols, A.getKeys());
}


Relation Database::relation_union(Relation A, Relation B){
  if(A.empty() || B.empty()){
    cerr << "Passed empty Relation\n";
    return Relation();
  }

  if(A.getColumns() != B.getColumns()){ //not union compatible
    cerr << "Relations not union compatible.\n";
    return Relation();
  }

  vector<Tuple> union_rows;
  vector<Tuple> Arows = A.getRows();
  vector<Tuple> Brows = B.getRows();

  //sort for use with std::set_union
  sort(Arows.begin(), Arows.end(), tupleComp(A.getKeys()));
  sort(Brows.begin(), Brows.end(), tupleComp(A.getKeys()));
  std::set_union(Arows.begin(), Arows.end(),
            Brows.begin(), Brows.end(),
            back_inserter(union_rows), tupleComp(A.getKeys()));

  return Relation("ABUnion", union_rows, A.getColumns(), A.getKeys());
}

Relation Database::relation_difference(Relation A, Relation B){
  if(A.empty() || B.empty()){
    cerr << "Passed empty Relation\n";
    return Relation();
  }

  if(A.getColumns() != B.getColumns()){ //not union compatiable
    cerr << "Relations not difference compatiable.\n";
    return Relation();
  }

  vector<Tuple> difference_rows;
  vector<Tuple> Arows = A.getRows();
  vector<Tuple> Brows = B.getRows();

  //sort for use with std::set_difference
  sort(Arows.begin(), Arows.end(), tupleComp(A.getKeys()));
  sort(Brows.begin(), Brows.end(), tupleComp(A.getKeys()));
  std::set_difference(Arows.begin(), Arows.end(),
            Brows.begin(), Brows.end(),
            back_inserter(difference_rows), tupleComp(A.getKeys()));

  return Relation("ABDifference", difference_rows, A.getColumns(), A.getKeys());
}

Relation Database::cross_product(Relation A, Relation B){
  if(A.empty() || B.empty()){
    cerr << "Passed empty Relation\n";
    return Relation();
  }

  vector<Attribute> cross_columns = A.getColumns();
  vector<Attribute> Bcols = B.getColumns();
  //add columns from B to cross_columns (columns from A)
  cross_columns.reserve(cross_columns.size()+Bcols.size());
  cross_columns.insert(cross_columns.end(), Bcols.begin(), Bcols.end());

  //for every row in A, append each row in B
  vector<Tuple> cross_rows;
  vector<Tuple> Arows = A.getRows();
  vector<Tuple> Brows = B.getRows();
  for(size_t i = 0; i < Arows.size(); ++i){
    for(size_t j = 0; j < Brows.size(); ++j){
      vector<string> Atuple = Arows[i].getDataStrings();
      vector<string> Btuple = Brows[j].getDataStrings();
      //append Brows[j] to Arows[i] and add to cross_rows
      Atuple.reserve(Atuple.size() + Btuple.size());
      Atuple.insert(Atuple.end(), Btuple.begin(), Btuple.end());
      cross_rows.push_back(Atuple);
    }
  }

  return Relation("ABcross", cross_rows, cross_columns, A.getKeys());
}
