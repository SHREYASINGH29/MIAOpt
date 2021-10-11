#include "Parser.h"
#include "InstructionInfo.h"
#include "Token.h"
#include "fstream"
#include "iostream"
#include "map"
#include "IMParser.hpp"
#include "string"
#include "vector"

using namespace std;

std::vector<Mapping *> UsrModel;

std::vector<Mapping *> getModelInfo(std::string FileName) {
  auto InstModel = ParseFile(FileName);
  for (auto x : InstModel) {
    Mapping *M = new Mapping(x);
    UsrModel.push_back(M);
  }
  return UsrModel;
}
