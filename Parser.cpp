#include "Parser.h"
#include "InstructionInfo.h"
#include "Token.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

bool isVar = true;

/// return true if it is a instruction name.
bool isInstruction(string Name) {
  vector<string> InstSaver = {"store", "load",    "add",          "alloca",
                              "ret",   "bitcast", "getelementptr"};
  for (int i = 0; i < InstSaver.size(); i++) {
    if (InstSaver[i] == Name)
      return true;
  }
  return false;
}

/// check if the name is a variable.
bool isVariable(string Name) {
  // if variable is a constant or null.
  if (Name.empty())
    return false;
  // if instruction name then it cannot be a variable.
  if (isInstruction(Name))
    return false;
  return isVar;
}

/// check if it is not an instruction and a variable.
bool isOperand(string Operand) {
  if (Operand.empty())
    return false;
  if (isInstruction(Operand))
    return false;
  return !isVar;
}

InstructionInfo *I;
vector<InstructionInfo *> InstModel;
int Count = 0;
bool Inst = false;
bool Col;

void parse(Token *Tokptr) {
  if (Tokptr->getType() == instruction) {
    Inst = true;
    I = new InstructionInfo(Tokptr->getName());
  }
  if (Inst == true) {
    if (Tokptr->getType() == operand) {
      I->OpInfo[Tokptr->getName()] = Count;
      Count++;
    }
  }
  if (Tokptr->getType() == colon) {
    Inst = false;
    Count = 0;
    Col = true;
  }
  if (Col == true) {
    if (Tokptr->getType() == operand) {
      if (I->OpInfo.find(Tokptr->getName()) == I->OpInfo.end()) {
        I->insertOrder(-1);
        I->LHS = true;
      } else {
        I->insertOrder(I->OpInfo[Tokptr->getName()]);
      }
      I->insertIndirection(Count + 1);
      Count = 0;
    }
    if (Tokptr->getType() == equals) {
      I->LHS = true;
    }
    if (Tokptr->getType() == pointer) {
      Count++;
    }
    if (Tokptr->getType() == address) {
      Count = -1;
    }
  }
  if (Tokptr->getType() == newline) {
    Col = false;
    InstModel.push_back(I);
    I = nullptr;
  }
  // Tokptr->print();
}

std::vector<Mapping *> UsrModel;

void check(string S) {
  if (isInstruction(S)) {
    Token *T = new Token(S, instruction);
    isVar = false;
    parse(T);
  } else if (isOperand(S)) {
    Token *T = new Token(S, operand);
    parse(T);
  } else if (isVariable(S)) {
    Token *T = new Token(S, variable);
    parse(T);
  } else if (S != "") {
    cout << "String not found!!" << endl;
  }
}

void checkspc(char C) {
  if (C == '*') {
    Token *T = new Token(pointer);
    parse(T);
  } else if (C == '=') {
    Token *T = new Token(equals);
    parse(T);
  } else if (C == ',') {
    Token *T = new Token(comma);
    parse(T);
  } else if (C == '\n') {
    Token *T = new Token(newline);
    isVar = true;
    parse(T);
  } else if (C == ':') {
    Token *T = new Token(colon);
    parse(T);
  } else if (C == '&') {
    Token *T = new Token(address);
    parse(T);
  } else {
    cout << "unknown" << endl;
  }
}

std::vector<Mapping *> getModelInfo(std::string FileName) {
  ifstream readfrom;
  char C;
  readfrom.open(FileName);
  string S;
  while (readfrom >> noskipws >> C) {
    switch (C) {
    case ' ':
      check(S);
      S.clear();
      break;
    case ',':
    case '*':
    case '=':
    case ':':
    case '\n':
    case '&':
      check(S);
      S.clear();
      checkspc(C);
      break;
    default:
      S.push_back(C);
    }
  }
  check(S);
  readfrom.close();
  for (auto x : InstModel) {
    // x->printInstModel();
    Mapping *M = new Mapping(x);
    UsrModel.push_back(M);
    // M->print();
  }
  return UsrModel;
}
