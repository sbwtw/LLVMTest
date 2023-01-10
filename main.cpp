#include <iostream>

#include "llvm/MC/TargetRegistry.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCRegister.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;
using namespace std;

int main()
{
  InitializeAllTargets();
  InitializeAllTargetInfos();
  InitializeAllTargetMCs();
  InitializeAllTargetMCAs();

    // Print registered targets
    for (auto target : TargetRegistry::targets())
    {
        cout << target.getName() << ',' << target.getBackendName() << ',' << target.getShortDescription() << endl;
    }

    string triple("x86_64-unknown-linux-gnu");
    string error;
    const Target *target = TargetRegistry::lookupTarget(triple, error);
    if (target == nullptr)
    {
        cout << error;
        return -1;
    }

    cout << "Use Target: " << target->getName() << ',' << target->getBackendName() << ',' << target->getShortDescription() << endl;


    MCTargetOptions mcTargetOpt;
    auto *subTargetInfo = target->createMCSubtargetInfo(triple, "", "");
    auto *instrInfo = target->createMCInstrInfo();
    auto *regInfo = target->createMCRegInfo(triple);
    auto *mcAsmInfo = target->createMCAsmInfo(*regInfo, triple, mcTargetOpt);
    auto *mcCtx = new MCContext(Triple(triple), mcAsmInfo, regInfo, subTargetInfo);

    auto *mcCodeEmitter = target->createMCCodeEmitter(*instrInfo, *mcCtx);

    MCInst inst = MCInstBuilder(2440).addImm(1205);

    SmallVector<MCFixup, 0> fixups;
    auto buf = SmallVector<char, 1024>();
    raw_svector_ostream os(buf);
    mcCodeEmitter->encodeInstruction(inst, os, fixups, *subTargetInfo);

    auto *asmPrinter = target->createMCInstPrinter(Triple(triple), 1, *mcAsmInfo, *instrInfo, *regInfo);

    asmPrinter->printInst(&inst, 0, "", *subTargetInfo, llvm::outs());
    llvm::outs() << '\n';

    for (auto c : buf)
    {
        llvm::outs() << format_hex((unsigned char)c, 4) << ' ';
    }

    return 0;
}
