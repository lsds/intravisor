// source: https://raw.githubusercontent.com/gkrls/kerma/b8332779110d6110df744da39ee0a0adb2614ee5/lib/Transforms/Canonicalize/BreakConstantGEP.cpp
//
#include "BRKGEP.h"

#define DEBUG

using namespace llvm;





ConstantExpr *BreakGEPPass::hasConstantGEP (Value * V) {
  if ( !V) return nullptr;
  if (ConstantExpr * CE = dyn_cast<ConstantExpr>(V)) {
//    if (CE->getOpcode() == Instruction::GetElementPtr) so now we are breaking any constantexpression 
      return CE;
    for (unsigned index = 0; index < CE->getNumOperands(); ++index)
      if (hasConstantGEP (CE->getOperand(index)))
        return CE;
  }
  return nullptr;
}

bool BreakGEPPass::runOnModule(Module &M) {
	bool changed = false;



	for (auto &F : M) {
		SmallVector<Instruction*, 32> Worklist;

		for ( auto& BB : F)
		    for ( auto& I : BB) {
			for (unsigned index = 0; index < I.getNumOperands(); ++index) {
			    if (hasConstantGEP (I.getOperand(index))) {
				Worklist.push_back(&I);
			    }
			}
		    }

		changed |= Worklist.size();

		while ( Worklist.size()) {
			Instruction *I = Worklist.pop_back_val();

			if (auto* PHI = dyn_cast<PHINode>(I)) {
				for (unsigned index = 0; index < PHI->getNumIncomingValues(); ++index) {
        // For PHI Nodes, if an operand is a constant expression with a GEP, we
        // want to insert the new instructions at the end of the incoming block.
    					Instruction * InsertPt = PHI->getIncomingBlock(index)->getTerminator();

    					if (ConstantExpr * CE = hasConstantGEP (PHI->getIncomingValue(index))) {

        					Instruction * NewInst = CE->getAsInstruction();
        					NewInst->insertBefore(InsertPt);
        					NewInst->setName("brk.gep");

        					for ( unsigned i = index; i < PHI->getNumIncomingValues(); ++i)
        						if ( PHI->getIncomingBlock(i) == PHI->getIncomingBlock(index))
            							PHI->setIncomingValue(i, NewInst);

        					Worklist.push_back(NewInst);
        					if ( CE->user_empty())
        						CE->destroyConstant();
    					}
    				}
			} else {
    				for (unsigned index = 0; index < I->getNumOperands(); ++index) {
        // For other instructions, just insert the instruction replacing
        // the operand just before the instruction itself
    					if (ConstantExpr * CE = hasConstantGEP (I->getOperand(index))) {

        					Instruction * NewInst = CE->getAsInstruction();
        					NewInst->insertBefore(I);
        					NewInst->setName("brk.gep");

        					I->replaceUsesOfWith(CE, NewInst);

        					Worklist.push_back(NewInst);
        					if ( CE->user_empty())
        						CE->destroyConstant();
    					}
    				}
			}
		}
	}

	return changed;
}

PreservedAnalyses BreakGEPPass::run(llvm::Module &M,
                                       llvm::ModuleAnalysisManager &) {

  const DataLayout &DL = M.getDataLayout();
  unsigned AllocaAS = DL.getAllocaAddrSpace();


  VoidTy = Type::getVoidTy(M.getContext());
  Int8PtrTy = Type::getInt8PtrTy(M.getContext(), AllocaAS);
  Int64PtrTy = Type::getInt64PtrTy(M.getContext(), AllocaAS);


  bool Changed =  runOnModule(M);

  return (Changed ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getBreakGEPPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "breakgep", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "breakgep") {
                    MPM.addPass(BreakGEPPass());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getBreakGEPPassPluginInfo();
}

/*********************** dont look down *******************/
/* 

//				GlobalVariable *gVar = M.getNamedGlobal(si->getPointerOperand()->getName());
//				errs() << "gVar: " << *gVar << "\n";

#if 0
				int i = 0;
				for (Module::global_iterator GVI = M.global_begin(), E = M.global_end();  GVI != E; ) {
    				GlobalVariable *GV = &*GVI++;
					if( GV == gVar) {
						errs() << i <<  "\tGV: " << *GV << "\n";
					}
					i++;
				}
#endif

#if 0
			for (Module::global_iterator GVI = M.global_begin(), E = M.global_end();  GVI != E; ) {
    			GlobalVariable *GV = &*GVI++;
				errs() << "GV: " << *GV << "\n";
			}
#endif


//			FunctionType* FuncTy_0 = FunctionType::get(Int8PtrTy, false);
//			FunctionType* FuncTy_0 = FunctionType::get(Int64PtrTy, false);

	virtual bool runOnModule(Module &M) {
		bool ret = false;

		for (Module::iterator F = M.begin(), Fend = M.end(); F != Fend; ++F) {
			if (F->isDeclaration())
				continue;

//			ret = pass_func(M, *F);
		}

	  return ret;
	}

//					builder->SetInsertPoint(I.getNextNode());

//			checkBound = InlineAsm::get(FuncTy_0, asmString, "=C,C,~{dirflag},~{fpsr},~{flags}", true);


;  %i15 = load i64, i64 addrspace(200)* @tgv, align 8, !dbg !164, !tbaa !165
;  tail call void asm sideeffect "li $0, 0xaa", "=r,r,~{dirflag},~{fpsr},~{flags}"(i64 addrspace(200)* @tgv), !dbg !164

; get local-global from tls
  %iA = tail call i8 addrspace(200)* asm "", "={c4}"()
  %Aarrayidx = getelementptr inbounds i8, i8 addrspace(200)* %iA, i64 2720
  %iB = bitcast i8 addrspace(200)* %Aarrayidx to i8 addrspace(200)* addrspace(200)* addrspace(200)*
  %iC = load i8 addrspace(200)* addrspace(200)*, i8 addrspace(200)* addrspace(200)* addrspace(200)* %iB, align 16
;
  %jA = bitcast i64 addrspace(200)* @tgv to i8 addrspace(200)*
  %jB = tail call i64 @llvm.cheri.cap.address.get.i64(i8 addrspace(200)* %jA)
  %jC = urem i64 %jB, 4096
;
  %i0 = bitcast i8  addrspace(200)* addrspace(200)* %iC to i8 addrspace(200)*
  %kA = tail call i8 addrspace(200)* @llvm.cheri.cap.offset.increment.i64(i8 addrspace(200)* %i0, i64 %jC)
  %kB = bitcast i8  addrspace(200)* %kA to i64 addrspace(200)*
  %i15 = load i64, i64 addrspace(200)* %kB, align 8

;;;;;;;;
  %inc = add nsw i64 %i15, 1, !dbg !164


;  store i64 %inc, i64 addrspace(200)* @tgv, align 8, !dbg !164, !tbaa !165
  store i64 %inc, i64 addrspace(200)* %kB, align 8, !dbg !164, !tbaa !165

;;;;;



			tgv = tgv % 0x1000;
     160: 13 d6 f5 43  	srai	a2, a1, 63
     164: 51 92        	srli	a2, a2, 52
     166: 2e 96        	add	a2, a2, a1
     168: fd 76        	lui	a3, 1048575
     16a: 75 8e        	and	a2, a2, a3
     16c: 91 8d        	sub	a1, a1, a2

; 			tgv = tgv & 0xffff;
     148: 17 05 00 00  	auipcc	ca0, 0
     14c: 0f 25 05 00  	clc	ca0, 0(ca0)
     150: db 0f f5 fe  	cgetaddr	t6, ca0
     154: db 0f f2 23  	cincoffset	ct6, ctp, t6
     158: db 85 af fe  	cmove	ca1, ct6
     15c: 83 b5 05 00  	cld	a1, 0(ca1)
     160: 41 66        	lui	a2, 16
     162: 7d 36        	addiw	a2, a2, -1
     164: f1 8d        	and	a1, a1, a2


//			checkBound = InlineAsm::get(FuncTy_0, asmString, "=C,C,~{dirflag},~{fpsr},~{flags}", true);

*/ 