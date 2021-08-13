#ifndef REPRESENTATION_H
#define REPRESENTATION_H

#include "InstRep.h"
#include "Inst.h"
#include "spatial/Token/Token.h"
#include "spatial/Token/TokenWrapper.h"
#include "Substitution.h"
#include "Parser.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "vector"

using namespace llvm;

class InstRepPass {
public:
  spatial::TokenWrapper *TW;
  std::vector<Mapping *> InstModel;
  InstRepPass(spatial::TokenWrapper &TW){
      this->TW = &TW;
  }
  spatial::Token *getOperand(Instruction *I, int Idx);
  spatial::Token *getVariableName(Instruction *I);
  std::string getInstName(Instruction *I);

  Mapping *getInstModelStructure(Instruction *I);
  Inst *createInst(Instruction *I);
  InstRep *getIR(Module &M);
};
#endif
