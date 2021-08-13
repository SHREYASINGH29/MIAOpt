#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include "Inst.h"
#include "InstRep.h"
#include "map"
#include "set"
#include "spatial/Token/Token.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Operator.h"

using namespace llvm;

class SUBPass {
public:
  InstRep *IR;
  std::map<std::pair<spatial::Token *, int>, std::pair<spatial::Token *, int>>
      Temp;
  std::set<spatial::Token *> ToBeRemoved;
  SUBPass() {}
  void skipEmptyInst(Module &M);
  void updateTemp(Inst *I);
  std::pair<spatial::Token *, int>
  replaceOp(std::pair<spatial::Token *, int> Op, int OR);
  void replaceLHS(Inst *I);
  void replaceRHS(Inst *I);
  void replaceInst(Inst *I);
  void substitute(Module &M);
  void removeDeadInst(Module &M);
  void substituteOnModule(Module &M, InstRep *I);
};

#endif
