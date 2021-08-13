#ifndef MAPPING_H
#define MAPPING_H

#include "InstructionInfo.h"
#include "string"
#include "vector"

class Mapping {
  std::string InstName;
  std::pair<int, int> LHS;
  std::vector<std::pair<int, int>> RHS;

public:
  Mapping(InstructionInfo *);
  std::string getName();
  std::pair<int, int> getLHS();
  std::vector<std::pair<int, int>> getRHS();
  void print();
};
#endif
