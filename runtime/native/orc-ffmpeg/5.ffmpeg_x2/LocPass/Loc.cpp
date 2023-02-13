// USAGE:
//      $ opt -load-pass-plugin <BUILD_DIR>/lib/libLocPass.so `\`
//        -passes=-"localise" <bitcode-file>
//
// License: MIT
//========================================================================
#include "Loc.h"

//#define DEBUG

#define NO_ACTION

using namespace llvm;

#if 0
const char* asm_string =
						"cgetaddr t6, $1\t\n"			// t6 = addr(VAR)
						"cspecialr ct4, pcc\t\n"
						"cgetbase t4, ct4\t\n"
						"srli	t4, t4, 28\t\n"
						"slli	t4, t4, 5 \t\n"
						"addi	t4, t4, 128\t\n"
						"cincoffset ct4, ctp, t4\t\n"
						"cld a2, 16(ct4)\t\n"			// a2 = ctp[144] //beginning of data section
						"sub t6, t6, a2\t\n"  			// t6 = t6 - a2  //t6 is offset in the store
						"clc	ct5, 0(ct4)\t\n"		// ct5 = (cap *) ctp[128]  -- cap to shadow store
						"cincoffset	$0, ct5, t6\t\n"	// ct6 = ct5[t6]
			;
const char* asm_regs = "=C,C,~{t6},~{a2},~{t5},~{t4}";
#else
#define T3	x12
#define T4	x13
#define T5	x14
#define T6	x15

const char* asm_string =
						"adr c13, #0\t\n"
						"gcbase x13, c13\t\n"
						"lsr	x13, x13, 28\t\n"
						"lsl	x13, x13, 5 \t\n"
						"add	x13, x13, 128\t\n"
						"mrs c11,ctpidr_el0\t\n"
						"add c13, c11, x13\t\n"
// ret: c13 <-- cap to a adjustement array (cap + offset)
						"ldr x12, [c13, #16]\t\n"			// a2 = ctp[144] //beginning of data section
// ret: x12 <-- offset
						"ldr	c14, [c13, #0]\t\n"		// ct5 = (cap *) ctp[128]  -- cap to shadow store
// ret: c14 <-- cap to shadow store
//
//in: x12 -- offset of the store, c14 -- cap to the shadow store
						"gcvalue x15, $1\t\n"			// t6 = addr(VAR)
						"sub x15, x15, x12\t\n"  			// t6 = t6 - a2  //t6 is offset in the store
						"add	$0, c14, x15\t\n"	// ct6 = ct5[t6]
			;
const char* asm_regs = "=C,C,~{x15},~{x12},~{x14},~{x13},~{x11}";

const char* asm_get_off_cap = 
						"adr c13, #0\t\n"
						"gcbase x13, c13\t\n"
						"lsr	x13, x13, 28\t\n"
						"lsl	x13, x13, 5 \t\n"
						"add	x13, x13, 128\t\n"
						"mrs c11,ctpidr_el0\t\n"
						"add $0, c11, x13\t\n"
			    ;
const char* asm_regs_get_off_cap = "=C,~{x13},~{x11}";

const char* asm_get_offset =
				    "ldr $0, [$1, #16]\t\n"
			    ;
const char* asm_regs_get_offset = "=r,C";

const char* asm_get_sstore =
				    "ldr $0, [$1, #0]\t\n"
			    ;
const char* asm_regs_get_sstore = "=C,C";

const char* asm_translate_cap =
						"gcvalue x15, $1\t\n"			// t6 = addr(VAR)
						"sub x15, x15, $2\t\n"  			// t6 = t6 - a2  //t6 is offset in the store
						"add	$0, $3, x15\t\n"	// ct6 = ct5[t6]
			    ;
const char* asm_regs_translate_cap = "=C,C,r,C,~{x15}";
#endif

void LocalisePass::translatePointer(IRBuilder<> &builder, BasicBlock *bb, Instruction *I, Value *operand, int reg) {
	if(void_3 == NULL) {
		std::vector<Type*>FuncTy_0_args;
		PointerType* PointerTy_0 = dyn_cast<PointerType>(Int64PtrTy);
		FuncTy_0_args.push_back(PointerTy_0);

		FunctionType* FuncTy_0 = FunctionType::get(PointerTy_0, false);

		InlineAsm* translatePtr;
		std::string asmString;
		asmString = std::string(asm_get_off_cap);
		translatePtr = InlineAsm::get(FuncTy_0, asmString, asm_regs_get_off_cap, true);

		void_3 = builder.CreateCall(translatePtr);
		void_3->setCallingConv(CallingConv::C);
		void_3->setTailCall(true);

////////
		std::vector<Type*>FuncTy_1_args;
		PointerType* PointerTy_1 = dyn_cast<PointerType>(void_3->getType());
		FuncTy_1_args.push_back(PointerTy_1);
//
		FunctionType* FuncTy_1 = FunctionType::get(Int64Ty, FuncTy_1_args, false);

		InlineAsm* translatePtr1;
		std::string asmString1;
		asmString1 = std::string(asm_get_offset);
		translatePtr1 = InlineAsm::get(FuncTy_1, asmString1, asm_regs_get_offset, true);

		call_inst_off = builder.CreateCall(translatePtr1, void_3);
		call_inst_off->setCallingConv(CallingConv::C);
		call_inst_off->setTailCall(true);
////////
		FunctionType* FuncTy_2 = FunctionType::get(Int64PtrTy, FuncTy_1_args, false);

		InlineAsm* translatePtr2;
		std::string asmString2;
		asmString2 = std::string(asm_get_sstore);
		translatePtr2 = InlineAsm::get(FuncTy_2, asmString2, asm_regs_get_sstore, true);

		call_inst_cap = builder.CreateCall(translatePtr2, void_3);
		call_inst_cap->setCallingConv(CallingConv::C);
		call_inst_cap->setTailCall(true);
	}
//////////

		std::vector<Type*>FuncTy_3_args;
		PointerType* PointerTy_3a = dyn_cast<PointerType>(operand->getType());
//		PointerType* PointerTy_3b = dyn_cast<PointerType>(call_inst_off->getType());
		PointerType* PointerTy_3c = dyn_cast<PointerType>(call_inst_cap->getType());
		FuncTy_3_args.push_back(PointerTy_3a);
		FuncTy_3_args.push_back(Int64Ty); //I don't know what it doesn't ;ole by PointerTy_3b
		FuncTy_3_args.push_back(PointerTy_3c);

//		errs() << *call_inst_off->getType() << "\n";

		FunctionType* FuncTy_3 = FunctionType::get(PointerTy_3a, FuncTy_3_args, false); 

		InlineAsm* translatePtr3;
		std::string asmString3;
		asmString3 = std::string(asm_translate_cap);

		translatePtr3 = InlineAsm::get(FuncTy_3, asmString3, asm_regs_translate_cap, true);


		std::vector<Value*>FuncTy_3_args_values;
		FuncTy_3_args_values.push_back(operand);
		FuncTy_3_args_values.push_back(call_inst_off);
		FuncTy_3_args_values.push_back(call_inst_cap);

		CallInst* call_inst_trans = builder.CreateCall(translatePtr3, FuncTy_3_args_values);
		call_inst_trans->setCallingConv(CallingConv::C);
		call_inst_trans->setTailCall(true);

		I->setOperand(reg, call_inst_trans);
}


bool LocalisePass::visit_meminst(llvm::Function *F, llvm::BasicBlock *B, llvm::Instruction *I) {
	bool changed = false;
#ifdef NO_ACTION 
	return changed;
#endif

#ifdef DEBUG
	errs() << "	"<< I->getOpcodeName() << ":	"
//	<< *I 
	<< "\n";
#endif

	IRBuilder<> *builder = NULL;
	Value *operand = NULL;
	builder = new IRBuilder<>(I);

	for (unsigned index = 0; index < I->getNumOperands(); ++index) {
		operand = I->getOperand(index);

#ifdef DEBUG
		errs() << "	operand[" << index << "]:	";
		if(operand->getType()->isDoubleTy())
			errs() << ">>>> suppresed double instruction <<<<<\n";
		else
			errs() << *operand << "\n";

		errs() <<   "	    isGlobal: " << llvm::isa<llvm::GlobalVariable>(I->getOperand(index))  << "\n"
			    "	    isAlloca: " << llvm::isa<llvm::AllocaInst>(I->getOperand(index)) << "\n"
			    "	    isGEP: " << llvm::isa<llvm::GetElementPtrInst>(I->getOperand(index)) << "\n"
			    "	    isCall: " << llvm::isa<llvm::CallInst>(I->getOperand(index)) << "\n"
			    "	    isLoad: " << llvm::isa<llvm::LoadInst>(I->getOperand(index)) << "\n"
			    "	    isGEPOp: " << llvm::isa<llvm::GEPOperator>(I->getOperand(index)) << "\n"
			    "	    isConstantExpr: " << llvm::isa<llvm::ConstantExpr>(I->getOperand(index)) << "\n"
			    ;
#endif

	//easy case: we are loading a global variable
		if(GlobalVariable* gv = dyn_cast<GlobalVariable>(operand)) {
//			if(gv->isConstant())
//				continue; //it is a global constant --> ignore

			errs() << MY_YELLOW << F->getName() << "(): replacing '" << operand->getName() << "' in " <<  *I << MY_RESET << '\n';

			translatePointer(*builder, B, I, operand,index);
			changed = true;
			continue;
		}

//	all other cases are either unknown to me, impossible due to the work of the previous pass, or non-global

		if(ConstantExpr* ce = dyn_cast<ConstantExpr>(operand)) {
			errs() << " Constant Expression, impossible " << *ce << "\n";

			errs() << *I << "\n";
			while(1);
		}

		if(isa<CallInst>(operand)) {
			//the operand is the result of a call -- ignore
			continue;
		}


	}

    return changed;
}

bool LocalisePass::visit_meminst2(llvm::Function *F, llvm::BasicBlock *B, llvm::Instruction *I) {
	bool changed = false;
#ifdef NO_ACTION 
	return changed;
#endif

#ifdef DEBUG
	errs() << "	"<< I->getOpcodeName() << ":	"
	<< *I
	<< "\n";
#endif

	IRBuilder<> *builder = NULL;
	Value *operand = NULL;
	builder = new IRBuilder<>(I);

	for (unsigned index = 0; index < I->getNumOperands(); ++index) {
		operand = I->getOperand(index);

#if 0
		errs() << "	operand[" << index << "]:	";
		if(operand->getType()->isDoubleTy())
			errs() << ">>>> suppresed double instruction <<<<<\n";
		else
			errs() << *operand << "\n";

		errs() <<   "	    isGlobal: " << llvm::isa<llvm::GlobalVariable>(I->getOperand(index))  << "\n"
			    "	    isAlloca: " << llvm::isa<llvm::AllocaInst>(I->getOperand(index)) << "\n"
			    "	    isGEP: " << llvm::isa<llvm::GetElementPtrInst>(I->getOperand(index)) << "\n"
			    "	    isCall: " << llvm::isa<llvm::CallInst>(I->getOperand(index)) << "\n"
			    "	    isLoad: " << llvm::isa<llvm::LoadInst>(I->getOperand(index)) << "\n"
			    "	    isGEPOp: " << llvm::isa<llvm::GEPOperator>(I->getOperand(index)) << "\n"
			    "	    isConstantExpr: " << llvm::isa<llvm::ConstantExpr>(I->getOperand(index)) << "\n"
			    ;
#endif

	//easy case: we are loading a global variable
		if(GlobalVariable* gv = dyn_cast<GlobalVariable>(operand)) {

//			if(gv->isConstant())
//				continue; //it is a global constant --> ignore

			errs() << MY_YELLOW << F->getName() << "(): replacing '" << operand->getName() << "' in " <<  *I << MY_RESET << '\n';

			translatePointer(*builder, B, I, operand,index);
			changed = true;
			continue;
		}

//	all other cases are either unknown to me, impossible due to the work of the previous pass, or non-global

		if(ConstantExpr* ce = dyn_cast<ConstantExpr>(operand)) {
			errs() << " Constant Expression, impossible " << *ce << "\n";

			errs() << *I << "\n";
			while(1);
		}

		if(isa<CallInst>(operand)) {
			//the operand is the result of a call -- ignore
			continue;
		}


	}

    return changed;
}


bool LocalisePass::runOnModule(Module &M) {
	bool changed = false;



	for (auto &F : M) {
		if (F.isDeclaration())
			continue;

		auto B_b = F.begin();
		auto B_e = F.end();

		while (B_b != B_e) {

			void_3 = NULL; //so our variables exist inside a block. should be in a function, but it requires additional work
			auto &B = *B_b;
			for (auto &I : B) {

				switch (I.getOpcode()) {
					case Instruction::Load:
					case Instruction::Store:
					case Instruction::AtomicCmpXchg:
					case Instruction::AtomicRMW:
					case Instruction::GetElementPtr:
					case Instruction::BitCast:
					case Instruction::Ret:
	    					changed |= visit_meminst(&F, &B, &I);
						break;
					case Instruction::Call:
	    					changed |= visit_meminst2(&F, &B, &I);
						break;
					default:
						errs() << "******* "<< I.getOpcodeName() << "\n";
						break;
				}

			}
			B_b++;
		}
	}

	return changed;
}

PreservedAnalyses LocalisePass::run(llvm::Module &M,
                                       llvm::ModuleAnalysisManager &) {

  const DataLayout &DL = M.getDataLayout();
  unsigned AllocaAS = DL.getAllocaAddrSpace();


  VoidTy = Type::getVoidTy(M.getContext());
  Int64Ty = Type::getInt64Ty(M.getContext());

  Int8PtrTy = Type::getInt8PtrTy(M.getContext(), AllocaAS);
  Int64PtrTy = Type::getInt64PtrTy(M.getContext(), AllocaAS);

  bool Changed =  runOnModule(M);

  return (Changed ? llvm::PreservedAnalyses::none()
                  : llvm::PreservedAnalyses::all());
}

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getLocalisePassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "localise", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "localise") {
                    MPM.addPass(LocalisePass());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLocalisePassPluginInfo();
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

//			translatePtr = InlineAsm::get(FuncTy_0, asmString, "=C,C,~{dirflag},~{fpsr},~{flags}", true);


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


//			translatePtr = InlineAsm::get(FuncTy_0, asmString, "=C,C,~{dirflag},~{fpsr},~{flags}", true);

*/ 