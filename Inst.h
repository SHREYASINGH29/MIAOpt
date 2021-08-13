#ifndef INST_H
#define INST_H

#include "spatial/Token/Token.h"
#include "string"
#include "vector"

class Inst {
  std::pair<spatial::Token *, int> LHS;
  std::vector<std::pair<spatial::Token *, int>> RHS;

public:
  std::pair<spatial::Token *, int> getLHS();
  std::vector<std::pair<spatial::Token *, int>> getRHS();
  void setLhsofRep(spatial::Token *T, int RD);
  void setRhsofRep(std::vector<std::pair<spatial::Token *, int>>);
  void insertIntoRhs(spatial::Token *, int);
  std::string getRDStr(int);
  void print();
};

#endif
