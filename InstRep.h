#ifndef INSTREP_H
#define INSTREP_H

#include "Inst.h"
#include "map"

class InstRep {
  std::map<llvm::Instruction *, Inst *> InstRepMap;

public:
  void skipInst(llvm::Instruction *);
  bool hasInst(llvm::Instruction *);
  void addInstRep(llvm::Instruction *, Inst *);
  Inst *getInstRep(llvm::Instruction *);
  void print();
  void printAll(llvm::Module &);
};
#endif
