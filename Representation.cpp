#include "Representation.h"
#include "InstRep.h"
#include "Inst.h"
#include "spatial/Token/Token.h"
#include "Parser.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Operator.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

static cl::opt<std::string>
    ModelFile("model-input", cl::init("input.txt"),
              cl::desc("Name of file with instruction modeling"), cl::Hidden);

static cl::opt<bool>
    PrintInst("print-inst", cl::init(false),
              cl::desc("Print instruction after representation"), cl::Hidden);

static cl::opt<bool>
    PrintInstOpt("print-inst-after-opt", cl::init(false),
                 cl::desc("Print instruction after optimization"), cl::Hidden);

static cl::opt<bool> PrintInstReplace(
    "print-inst-replace", cl::init(false),
    cl::desc("Print instruction after optimization with replaced instructions"),
    cl::Hidden);

spatial::Token *InstRepPass::getOperand(Instruction *I, int Idx) {
  if (isa<GetElementPtrInst>(I))
    return TW->getToken(
        new spatial::Token(cast<GEPOperator>(I), I->getFunction()));
  if (!isa<Instruction>(I->getOperand(Idx)) &&
      isa<GEPOperator>(I->getOperand(Idx)))
    return TW->getToken(new spatial::Token(
        cast<GEPOperator>(I->getOperand(Idx)), I->getFunction()));
  return TW->getToken(new spatial::Token(I->getOperand(Idx)));
}

spatial::Token *InstRepPass::getVariableName(Instruction *I) {
  return TW->getToken(new spatial::Token(I));
}

std::string InstRepPass::getInstName(Instruction *I) {
  if (isa<StoreInst>(I))
    return "store";
  else if (isa<LoadInst>(I))
    return "load";
  else if (isa<ReturnInst>(I))
    return "ret";
  else if (isa<GetElementPtrInst>(I))
    return "getelementptr";
  else if (isa<AllocaInst>(I))
    return "alloca";
  else if (isa<BinaryOperator>(I)) {
    switch (I->getOpcode()) {
    case Instruction::Add:
      return "add";
    }
  } else if (isa<CallInst>(I)) {
    return "call";
  } else if (isa<BitCastInst>(I))
    return "bitcast";
  return I->getName().str();
}

Mapping *InstRepPass::getInstModelStructure(Instruction *I) {
  std::string RepInst = getInstName(I);
  for (Mapping *II : this->InstModel) {
    if (II->getName() == RepInst) {
      return II;
    }
  }
  return nullptr;
}

Inst *InstRepPass::createInst(Instruction *I) {
  Mapping *M = getInstModelStructure(I);
  if (!M)
    return nullptr;
  Inst *NewInst = new Inst();
  auto LHS = M->getLHS();
  if (LHS.first == -1) {
    NewInst->setLhsofRep(getVariableName(I), LHS.second);
  } else {
    auto *OpRes = getOperand(I, LHS.first);
    if (OpRes->getName() != "" && OpRes->isGlobalVar())
      LHS.second -= 1;
    NewInst->setLhsofRep(OpRes, LHS.second);
  }
  auto RHS = M->getRHS();
  for (auto x : RHS) {
    auto *OpRes = getOperand(I, x.first);
    if (OpRes->getName() != "" && OpRes->isGlobalVar())
      x.second -= 1;
    NewInst->insertIntoRhs(OpRes, x.second);
  }
  return NewInst;
}

InstRep *InstRepPass::getIR(Module &M) {
  InstRep *IR = new InstRep();
  InstModel = getModelInfo(ModelFile);
  for (Module::iterator F = M.begin(); F != M.end(); F++) {
    for (inst_iterator I = inst_begin(*F), E = inst_end(*F); I != E; ++I) {
      auto ModelInst = createInst(&*I);
      if (ModelInst) {
        IR->addInstRep(&*I, ModelInst);
      }
    }
  }
  if (PrintInst)
    IR->print();
  SUBPass X;
  X.substituteOnModule(M, IR);
  if (PrintInstOpt)
    IR->print();
  if (PrintInstReplace)
    IR->printAll(M);
  return IR;
}
