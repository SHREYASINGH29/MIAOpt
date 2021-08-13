#include "Mapping.h"
#include "InstructionInfo.h"
#include "iostream"

Mapping::Mapping(InstructionInfo *I) {
  InstName = I->getName();
  auto Order = I->getOrder();
  auto Indirection = I->getIndirection();
  int i = 0;
  if (I->LHS) {
    i = 1;
    LHS = std::make_pair(Order[0], Indirection[0]);
  }
  for (; i < Order.size(); i++) {
    RHS.push_back(std::make_pair(Order[i], Indirection[i]));
  }
}

std::string Mapping::getName() {
  return InstName;
}

std::pair<int, int> Mapping::getLHS() {
  return LHS;
}

std::vector<std::pair<int, int>> Mapping::getRHS() {
  return RHS;
}

void Mapping::print() {
  std::cout << InstName << " ";
  std::cout << "LHS" << LHS.first << " " << LHS.second << "   ";
  for (int i = 0; i < RHS.size(); i++) {
    std::cout << "RHS" << RHS[i].first << " " << RHS[i].second << "   ";
  }
  std::cout << "\n";
}
