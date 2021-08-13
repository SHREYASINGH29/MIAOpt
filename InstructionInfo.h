#ifndef INSTRUCTIONINFO_H
#define INSTRUCTIONINFO_H

#include "map"
#include "string"
#include "vector"

class InstructionInfo {
  std::vector<int> Order;
  std::vector<int> Indirection;
  std::string InstName;

public:
  std::map<std::string, int> OpInfo;
  bool LHS;
  InstructionInfo(std::string);
  std::string getName();
  std::vector<int> getOrder();
  std::vector<int> getIndirection();
  void insertOrder(int);
  void insertIndirection(int);
  void printInstModel();
};
#endif
