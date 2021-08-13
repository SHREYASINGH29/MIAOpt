#include "InstRep.h"
#include "iostream"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"

void InstRep::skipInst(llvm::Instruction *I) {
  InstRepMap.erase(I);
}

bool InstRep::hasInst(llvm::Instruction *I) {
  return InstRepMap.find(I) != InstRepMap.end();
}

void InstRep::addInstRep(llvm::Instruction *I, Inst *R) {
  InstRepMap[I] = R;
}

Inst *InstRep::getInstRep(llvm::Instruction *I) {
  if (hasInst(I))
    return InstRepMap[I];
  return nullptr;
}

void InstRep::print() {
  for (auto I : InstRepMap) {
    llvm::errs() << *I.first << "\n";
    I.second->print();
  }
}

void InstRep::printAll(llvm::Module &M) {
  for (llvm::Module::iterator F = M.begin(); F != M.end(); F++) {
    for (llvm::inst_iterator I = inst_begin(*F), E = inst_end(*F); I != E; ++I) {
      auto *Inst = getInstRep(&*I);
      llvm::errs() << *I << "\n";
      if (Inst)
        Inst->print();
    }
  }
}
