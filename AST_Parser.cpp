#include "AST_Parser.h"
#include <iostream>
#include <stdexcept>
using namespace std;

bool AST_Parser::parse(AST* ast){
  try{
    if(ast->tag == AST::ASSIGN){//query
      string new_relation_name = identifier(static_cast<AssignAST*>(ast)->left);
      Relation expr_relation = expr(static_cast<AssignAST*>(ast)->right);
      views->addRelation(Relation(new_relation_name,
                                  expr_relation.getRows(),
                                  expr_relation.getColumns(),
                                  expr_relation.getKeys()));
    }/*
       } else if (ast->tag == AST::OPEN){
       //OPEN
       } else if (ast->tag == AST::CLOSE){
       //CLOSE
       } else if (ast->tag == AST::WRITE){
       //WRITE
       } else if (ast->tag == AST::EXIT){
       //EXIT
       } else if (ast->tag == AST::SHOW){
       //SHOW
       } else if (ast->tag == AST::CREATE){
       //CREATE
       } else if (ast->tag == AST::UPDATE){
       //UPDATE
       }*/ else { //not query or command
      throw runtime_error("Invalid syntax");
    }
  } catch(exception& e) {
    cerr << e.what() << endl;
    return false;
  }
  return true;
}

string AST_Parser::identifier(AST* ast){
  if(ast->tag == AST::IDENTIFIER){
    return static_cast<IdentifierAST*>(ast)->center.field();
  }
  throw runtime_error("Not identifier.");
}

Relation AST_Parser::expr(AST* ast){
  switch(ast->tag){
  case (AST::IDENTIFIER):
    string rel_name = identifier(ast);

    Relation rel = db->getRelation(rel_name);
    if(rel != Relation()){ //rel_name in db
      return rel;
    } else if ((rel = views->getRelation(rel_name)) != Relation()){ //in views
      return rel;
    } else {
      //expr is relation name, but doesn't exist
      throw runtime_error("Relation " + rel_name + " not found.");
    }
  case (AST::SELECT):
    Relation right = expr(static_cast<SelectAST*>(ast)->right);
    vector<Tuple> rows = right.getRows();
    Relation new_rel = Relation("", vector<Tuple>(),
                                right.getColumns(), right.getKeys());
    vector<Tuple>::const_iterator cit;
    for(cit = rows.begin(); cit != rows.end(); ++cit){
      if(binaryop(stactic_case<BinaryOP*>(ast)->left, *cit)){
        new_rel.addTuple(*cit);
      }
    }

    return new_rel;
    /*
      } else if (ast->tag == AST::PROJECT) {
      //projection
      } else if (ast->tag == AST::RENAME) {
      //renaming
      } else if (ast->tag == AST::BINARYOP) {
      //union, difference, or product
      }
    */
  default:
    throw runtime_error("Expression invalid.");
  }
}

bool AST_Parser::binaryop(AST* ast, Tuple const& t){
  assert(ast->tag == AST::BINARYOP);
  switch(static_cast<BinaryAST*>(ast)->op){
  case _g:
    
  case _l:
  case _ge:
  case _le:
  case _e:
  case _ne:
  case _and:
  case _or:
  default:
    assert(false);
  }
  return false;
}
