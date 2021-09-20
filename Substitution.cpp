#include "Substitution.h"
#include "InstRep.h"
#include "Inst.h"
#include "spatial/Token/Token.h"
#include "Parser.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

static cl::opt<bool> PrintInstSubstitute(
    "print-inst-substitute", cl::init(false),
    cl::desc("Print instruction after optimization with substituted instructions"),
    cl::Hidden);

void SUBPass::skipEmptyInst(Module &M) {
    for (Module::iterator F = M.begin(); F != M.end(); F++) {
        for (inst_iterator I = inst_begin(*F), E = inst_end(*F); I != E; ++I) {
            if (IR->hasInst(&*I)) {
                auto IRInst = IR->getInstRep(&*I);
                if (!IRInst)
                    IR->skipInst(&*I);
                auto LHS = IRInst->getLHS();
                if (LHS.first->getName().empty())
                    IR->skipInst(&*I);
                auto RHS = IRInst->getRHS();
                for (auto R : RHS) {
                    if (R.first->getName().empty())
                        IR->skipInst(&*I);
                }
            }
        }
    }
}

void SUBPass::updateTemp(Inst *I) {
    if (!I)
        return;
    if (I->getRHS().size() != 1)
        return;
    if (I->getLHS().first->getName() == "")
        return;
    if (I->getRHS()[0].first->getName() == "")
        return;
    Temp[I->getLHS()] = I->getRHS()[0];
}

std::pair<spatial::Token *, int>
SUBPass::replaceOp(std::pair<spatial::Token *, int> Op, int OR) {
    if (Temp.find(Op) != Temp.end()) {
        return std::make_pair(Temp[Op].first, OR + Temp[Op].second - 1);
    }
    return std::make_pair(nullptr, 0);
}

void SUBPass::replaceLHS(Inst *I) {
    std::pair<spatial::Token *, int> OpVar =
        std::make_pair(I->getLHS().first, 1);
    auto NewOp = replaceOp(OpVar, I->getLHS().second);
    if (NewOp.first)
        I->setLhsofRep(NewOp.first, NewOp.second);
}

void SUBPass::replaceRHS(Inst *I) {
    auto RHSVec = I->getRHS();
    std::vector<std::pair<spatial::Token *, int>> ResVec;
    for (auto RHS : RHSVec) {
        int OldSize = ResVec.size();
        auto NewOp = replaceOp(RHS, RHS.second);
        if (NewOp.first) {
            if (RHS.second == 1)
                ToBeRemoved.insert(RHS.first);
            ResVec.push_back(NewOp);
        } else {
            std::pair<spatial::Token *, int> OpVar =
                std::make_pair(RHS.first, 1);
            NewOp = replaceOp(OpVar, RHS.second);
            if (NewOp.first) {
                ToBeRemoved.insert(RHS.first);
                ResVec.push_back(NewOp);
            }
        }
        if (ResVec.size() == OldSize)
            ResVec.push_back(RHS);
    }
    I->setRhsofRep(ResVec);
}

void SUBPass::replaceInst(Inst *I) {
    replaceLHS(I);
    replaceRHS(I);
}

void SUBPass::substitute(Module &M) {
    for (Module::iterator F = M.begin(); F != M.end(); F++) {
        for (inst_iterator I = inst_begin(*F), E = inst_end(*F); I != E; ++I) {
            if (IR->hasInst(&*I)) {
                replaceInst(IR->getInstRep(&*I));
                updateTemp(IR->getInstRep(&*I));
            }
        }
    }
}

void SUBPass::removeDeadInst(Module &M) {
    for (Module::iterator F = M.begin(); F != M.end(); F++) {
        for (inst_iterator I = inst_begin(*F), E = inst_end(*F); I != E; ++I) {
            if (IR->hasInst(&*I)) {
                auto IRInst = IR->getInstRep(&*I);
                auto LHS = IRInst->getLHS();
                if (ToBeRemoved.find(LHS.first) != ToBeRemoved.end())
                    IR->skipInst(&*I);
            }
        }
    }
}

void SUBPass::substituteOnModule(Module &M, InstRep *I) {
    IR = I;
    skipEmptyInst(M);
    substitute(M);
    if(PrintInstSubstitute)
        IR->printAll(M);
    removeDeadInst(M);
    return;
}
