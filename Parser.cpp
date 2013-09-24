#include "Parser.h"

bool Parser::parse(string str){
  bool success = 0;
  AST* tree = A.assemble(str);
  if(tree){
    success = T.traverse(tree);
  } else {
    cerr << "Syntax error.\n";
    return false;
  }
  return success;
}
