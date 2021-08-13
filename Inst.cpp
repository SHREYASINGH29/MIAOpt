#include "Inst.h"
#include "iostream"

std::pair<spatial::Token *, int> Inst::getLHS() {
  return LHS;
}

std::vector<std::pair<spatial::Token *, int>> Inst::getRHS() {
  return RHS;
}

void Inst::setLhsofRep(spatial::Token *T, int RD) {
  this->LHS = std::make_pair(T, RD);
}

void Inst::setRhsofRep(std::vector<std::pair<spatial::Token *, int>> RHS) {
  this->RHS = RHS;
}

void Inst::insertIntoRhs(spatial::Token *T, int RD) {
  RHS.push_back(std::make_pair(T, RD));
}

std::string Inst::getRDStr(int RD) {
  if (RD == 0)
    return "&";
  std::string Result = "";
  for (int i = 1; i < RD; i++) {
    Result += "*";
  }
  return Result;
}

void Inst::print() {
  std::cout << "    " << getRDStr(LHS.second) << *(LHS.first) << " = ";
  for (auto RHS : RHS) {
    std::cout << getRDStr(RHS.second) << *(RHS.first) << " ";
  }
  std::cout << std::endl;
}
