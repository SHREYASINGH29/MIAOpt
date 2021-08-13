#include "../Representation.h"
#include "spatial/Token/TokenWrapper.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

namespace {

#define DEBUG_TYPE "demo"

class DemoPass : public ModulePass {
public:
  static char ID;
  InstRep *IR;
  DemoPass() : ModulePass(ID) {}

  bool runOnModule(Module &M) override {
    spatial::TokenWrapper *TW = new spatial::TokenWrapper();
    InstRepPass X(*TW);
    IR = X.getIR(M);
    return false;
  }
};
} // namespace

char DemoPass::ID = 0;
static RegisterPass<DemoPass> X("demo",
                               "Demo Pass to demonstrate miao",
                               true,
                               true);
