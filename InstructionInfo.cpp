#include "InstructionInfo.h"
#include "iostream"
#include "string"
#include "vector"

InstructionInfo::InstructionInfo(std::string S) {
  InstName = S;
  LHS = false;
}

std::string InstructionInfo::getName() {
  return InstName;
}

std::vector<int> InstructionInfo::getOrder() {
  return Order;
}

std::vector<int> InstructionInfo::getIndirection() {
  return Indirection;
}

void InstructionInfo::insertOrder(int O) {
  Order.push_back(O);
}

void InstructionInfo::insertIndirection(int I) {
  Indirection.push_back(I);
}

void InstructionInfo::printInstModel() {
  std::cout << InstName << std::endl;
  std::cout << Order[0] << " " << Indirection[0];
  if (LHS == true) {
    std::cout << " = ";
  } else {
    std::cout << " , ";
  }

  for (int i = 1; i < Order.size(); i++) {
    std::cout << Order[i] << " ";
    std::cout << Indirection[i];
    if (i < Order.size() - 1) {
      std::cout << " ,";
    }
  }
  std::cout << std::endl;
}
