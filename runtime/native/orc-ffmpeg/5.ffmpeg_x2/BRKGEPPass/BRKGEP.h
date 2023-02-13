#define MY_RESET   "\033[0m"
#define MY_BLACK   "\033[30m"      /* Black */
#define MY_RED     "\033[31m"      /* Red */
#define MY_GREEN   "\033[32m"      /* Green */
#define MY_YELLOW  "\033[33m"      /* Yellow */
#define MY_BLUE    "\033[34m"      /* Blue */
#define MY_MAGENTA "\033[35m"      /* Magenta */
#define MY_CYAN    "\033[36m"      /* Cyan */
#define MY_WHITE   "\033[37m"      /* White */
#define MY_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define MY_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define MY_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define MY_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define MY_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define MY_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define MY_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define MY_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/InlineAsm.h"

struct BreakGEPPass : public llvm::PassInfoMixin<BreakGEPPass> {
  llvm::PreservedAnalyses run(llvm::Module &M,
                              llvm::ModuleAnalysisManager &);
  bool runOnModule(llvm::Module &M);
  llvm::ConstantExpr * hasConstantGEP(llvm::Value * V);

  llvm::Type *VoidTy;
  llvm::Type *Int8PtrTy;
  llvm::Type *Int64PtrTy;
};