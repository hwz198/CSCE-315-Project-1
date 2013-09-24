#include "AST_Traversal.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <algorithm>
using namespace std;

int atoi(string const& s){
  return atoi(s.c_str());
}

bool AST_Traversal::traverse(AST* ast){
  try{
    switch(ast->tag){
    case (AST::ASSIGN):{//query
      string new_relation_name = identifier(static_cast<AssignAST*>(ast)->left);
      Relation expr_relation = expr(static_cast<AssignAST*>(ast)->right);
      views->addRelation(Relation(new_relation_name,
                                  expr_relation.getRows(),
                                  expr_relation.getColumns(),
                                  expr_relation.getKeys()));
      break;
    }
    case (AST::CREATE):{
      CreateAST* cast = static_cast<CreateAST*>(ast);
      string rel_name = identifier(cast->left);

      vector<Attribute> columns;
      TypedAttrListAST* attrAST = static_cast<TypedAttrListAST*>(cast->center);
      while(attrAST){
        columns.push_back(make_attr(attrAST->center, identifier(attrAST->left)));
        attrAST = static_cast<TypedAttrListAST*>(attrAST->right);
      }
      vector<size_t> keys;
      AttrListAST* key = static_cast<AttrListAST*>(cast->right);
      while(key){
        string attr_name = identifier(key->left);
        size_t i;
        for(i = 0; i < columns.size(); ++i){
          if(attr_name == columns[i].getValue()){
            keys.push_back(i);
            break;
          }
        }
        if(i == columns.size()){
          throw runtime_error("Invalid primary key");
        }
        key = static_cast<AttrListAST*>(key->right);
      }
      db->addRelation(Relation(rel_name, vector<Tuple>(), columns, keys));
      break;
    }
    case (AST::INSERT):{
      InsertAST* iast = static_cast<InsertAST*>(ast);
      string rel_name = identifier(iast->left);
      Relation* r = db->getRelationRef(rel_name);
      if(!r){
        r = views->getRelationRef(rel_name);
        if(!r){
          throw runtime_error("Relation " + rel_name + " not found.");
        }
      }
      vector<Attribute> attribs = r->getColumns();
      if(iast->right->tag == AST::LIT_LIST){
        LiteralListAST* list = static_cast<LiteralListAST*>(iast->right);
        size_t i = 0;
        vector<string> row;
        while(list){
          Token tok = literal(list->left);
          if(tok.type() == _literal && attribs[i].getDataType() == str){
            string field = tok.field();
            field = field.substr(1, field.size()-2);
            field = field.substr(0, attribs[i].maxLength());
            row.push_back(field);
          } else if (tok.type() == _lit_integer && attribs[i].getDataType() == in){
            row.push_back(tok.field());
          } else {
            throw runtime_error("Row doesn't match columns");
          }
          list = static_cast<LiteralListAST*>(list->right);
          ++i;
        }
        if(i != attribs.size()){
          throw runtime_error("Not enough strings in INSERT");
        }
        r->addTuple(Tuple(row));
      } else {
        Relation e = expr(iast->right);
        vector<Tuple> erows = e.getRows();
        //TODO check types
        for(size_t j = 0; j < erows.size(); ++j){
          r->addTuple(erows[j]);
        }
      }
      break;
    }
    case (AST::UPDATE):{
      UpdateAST* uast = static_cast<UpdateAST*>(ast);
      string rel_name = identifier(uast->left);
      Relation* r = db->getRelationRef(rel_name);
      if(!r){
        r = views->getRelationRef(rel_name);
        if(!r){
          throw runtime_error("Relation " + rel_name + " not found.");
        }
      }
      vector<Attribute> attribs = r->getColumns();
      vector<Tuple>* rows = r->getRowsRef();
      for(size_t i = 0; i < rows->size(); ++i){
        UpdateListAST* list = static_cast<UpdateListAST*>(uast->center);
        vector<size_t> indices;
        vector<Token> tokens;
        while(list){
          //vector<size_t> indices;
          size_t j;
          string attr_name = identifier(list->left);
          Token lit_tok = literal(list->center);
          for(j = 0; j < attribs.size(); ++j){
            if(attr_name == attribs[j].getValue()
               && ((lit_tok.type() == _literal && attribs[j].getDataType() == str)
                   || (lit_tok.type() == _lit_integer && attribs[j].getDataType() == in))){
              break;
            }
          }
          if(j == attribs.size()){
            throw runtime_error("Attribute " + identifier(list->left)
                                + " doesn't exist in " + rel_name);
          }
          indices.push_back(j);
          tokens.push_back(lit_tok);
          list = static_cast<UpdateListAST*>(list->right);
        }
        cout << "{" << i << "}\n";
        if(binaryop(uast->right, (*rows)[i], attribs)){
          for(size_t k = 0; k <indices.size(); ++k){
            cout << "{" << i << ", " << k << "}\n";
            (*rows)[i].changeDataMember(indices[k], tokens[k].field());
          }
        }
      }
      break;
    }
    case (AST::DELETE):{
      DeleteAST* dast = static_cast<DeleteAST*>(ast);
      string rel_name = identifier(dast->left);
      Relation* r = db->getRelationRef(rel_name);
      if(!r){
        r = views->getRelationRef(rel_name);
        if(!r){
          throw runtime_error("Relation " + rel_name + " not found.");
        }
      }
      vector<Tuple> const *rows = r->getRowsRef();
      vector<Attribute> attribs = r->getColumns();
      vector<size_t> indices;
      for(size_t i = 0; i < rows->size(); ++i){
        if(binaryop(dast->right, (*rows)[i], attribs)){
          indices.push_back(i);
        }
      }
      sort(indices.begin(), indices.end(), greater<size_t>());
      for(size_t i = 0; i < indices.size(); ++i){
        r->deleteTuple(indices[i]);
      }
      break;
    }
    case (AST::SHOW):{
      Relation r = expr(static_cast<ShowAST*>(ast)->center);
      db->Show(r);
      break;
    }
    case (AST::OPEN):{
      string rel_name = identifier(static_cast<OpenAST*>(ast)->center);
      db->Open(rel_name);
      break;
    }
    case (AST::CLOSE):{
      string rel_name = identifier(static_cast<CloseAST*>(ast)->center);
      db->Close(rel_name);
      break;
    }
    case (AST::WRITE):{
      string rel_name = identifier(static_cast<WriteAST*>(ast)->center);
      db->Write(rel_name);
      break;
    }
    case (AST::EXIT):{
      db->Exit();
      break;
    }
    default: //not query or command
      throw runtime_error("Invalid syntax");
    }
  } catch(exception& e) {
    cerr << e.what() << endl;
    return false;
  }
  return true;
}

string AST_Traversal::identifier(AST* ast){
  if(ast->tag == AST::IDENTIFIER){
    return static_cast<IdentifierAST*>(ast)->center.field();
  }
  throw runtime_error("Not identifier.");
}

Relation AST_Traversal::expr(AST* ast){
  switch(ast->tag){
  case (AST::IDENTIFIER):{
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
    break;}
  case (AST::SELECT):{
    Relation right = expr(static_cast<SelectAST*>(ast)->right);
    vector<Tuple> rows = right.getRows();
    Relation new_rel = Relation("", vector<Tuple>(),
                                right.getColumns(), right.getKeys());
    vector<Tuple>::const_iterator cit;
    for(cit = rows.begin(); cit != rows.end(); ++cit){
      if(binaryop(static_cast<BinaryOpAST*>(ast)->left, *cit, right.getColumns())){
        new_rel.addTuple(*cit);
      }
    }
    return new_rel;
  }
  case (AST::PROJECT):{
    Relation right = expr(static_cast<ProjectAST*>(ast)->right);
    AST* left = static_cast<ProjectAST*>(ast)->left;
    vector<string> attrib_vals;
    while(left){
      attrib_vals.push_back(identifier(static_cast<AttrListAST*>(left)->left));
      left = static_cast<AttrListAST*>(left)->right;
    }
    return db->projection(right, "projection", attrib_vals);
  }
  case (AST::RENAME):{
    Relation right = expr(static_cast<RenameAST*>(ast)->right);
    AST* left = static_cast<RenameAST*>(ast)->left;
    vector<string> attrib_vals;
    while(left){
      attrib_vals.push_back(identifier(static_cast<AttrListAST*>(left)->left));
      left = static_cast<AttrListAST*>(left)->right;
    }
    return db->rename(right, "renameion", attrib_vals);
  }
  case (AST::BINARYOP):{
    Relation left = expr(static_cast<BinaryOpAST*>(ast)->left);
    Relation right = expr(static_cast<BinaryOpAST*>(ast)->right);
    TokenType op = static_cast<BinaryOpAST*>(ast)->op; 
    switch(op){
    case (_plus):
      return db->relation_union(left, right);
    case (_minus):
      return db->relation_difference(left, right);
    case (_asterisk):
      return db->cross_product(left, right);
    default:
      throw runtime_error("Invalid op");
    }
  }
  default:
    throw runtime_error("Expression invalid.");
  }
  throw runtime_error("Expression invalid.");
}

bool AST_Traversal::binaryop(AST* ast, Tuple const& t, vector<Attribute> const& a){
  assert(ast->tag == AST::BINARYOP);
  AST* l = static_cast<BinaryOpAST*>(ast)->left;
  AST* r = static_cast<BinaryOpAST*>(ast)->right;
  TokenType op = static_cast<BinaryOpAST*>(ast)->op;
  switch(op){
  case _g:
  case _l:
  case _ge:
  case _le:
  case _e:
  case _ne:
    return perform_op(ident_or_literal(l, t, a), ident_or_literal(r, t, a), op);
  case _and:
    return (binaryop(l, t, a) && binaryop(r, t, a));
  case _or:
    return (binaryop(l, t, a) || binaryop(r, t, a));
  default:
    assert(false);
  }
  return false;
}

bool AST_Traversal::perform_op(Value left, Value right, TokenType op){
  if(left.kind != right.kind){
    throw runtime_error("Invalid operands.");
  }
  switch(op){
  case _g:
    if(left.kind == Value::INTEGER)
      return left.i > right.i;
    else
      return left.s > right.s;
  case _l:
    if(left.kind == Value::INTEGER)
      return left.i < right.i;
    else
      return left.s < right.s;
  case _ge:
    if(left.kind == Value::INTEGER)
      return left.i >= right.i;
    else
      return left.s >= right.s;
  case _le:
    if(left.kind == Value::INTEGER)
      return left.i <= right.i;
    else
      return left.s <= right.s;
  case _e:
    if(left.kind == Value::INTEGER)
      return left.i == right.i;
    else
      return left.s == right.s;
  case _ne:
    if(left.kind == Value::INTEGER)
      return left.i != right.i;
    else
      return left.s != right.s;
  default:
    assert(false);
  }
}

Token AST_Traversal::literal(AST* ast){
  if(ast->tag == AST::LITERAL){
    return static_cast<LiteralAST*>(ast)->center;
  }
  throw runtime_error("Not literal.");
}

Value AST_Traversal::ident_or_literal(AST* ast, Tuple const& t, vector<Attribute> const& a){
  Value val;
  switch(ast->tag){
  case (AST::IDENTIFIER):{
    string ident = identifier(ast);
    for(size_t i = 0; i < a.size(); ++i){
      if(a[i].getValue() == ident){
        if(a[i].getDataType() == str){
          val.kind = Value::STRING;
          val.s = t.getString(i);
          return val;
        } else {
          val.kind = Value::INTEGER;
          val.i = atoi(t.getString(i));
          return val;
        }
      }
    }
    throw runtime_error("Invalid attribute name " + ident + '.');}
  case (AST::LITERAL):{
    Token tok = literal(ast);
    if(tok.type() == _literal){
      val.kind = Value::STRING;
      val.s = tok.field();
      val.s = val.s.substr(1, val.s.size()-2); //get rid of quotes
      return val;
    } else if(tok.type() == _lit_integer) {
      val.kind = Value::INTEGER;
      val.i = atoi(tok.field());
      return val;
    } else {
      assert(false);
    }}
  default:
    throw runtime_error("Neither ident nor literal.");
  }
}

Attribute AST_Traversal::make_attr(AST* ast, string name){
  assert(ast->tag == AST::TYPE);
  TokenType toktype = static_cast<TypeAST*>(ast)->center.type();
  dataTypes attrtype;
  if(toktype == _varchar){
    attrtype = str;
  } else if (toktype == _integer){
    attrtype = in;
  } else {
    assert(false);
  }
  size_t sz = static_cast<TypeAST*>(ast)->size;
  return Attribute(name, attrtype, sz);
}
