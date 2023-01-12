cmake_minimum_required(VERSION 3.24)

project(LLVMTest)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")

#set(LLVM_LINK_COMPONENTS
#        Core
#        Support
#        Target
#
#        AllTargetsCodeGens
#        AllTargetsAsmParsers
#        AllTargetsDescs
#        AllTargetsInfos
#        AllTargetsDisassemblers
#        AllTargetsMCAs
#        )

include_directories(
        ${CMAKE_SOURCE_DIR}/lib/Target/X86
)

set(LLVM_TARGET_DEFINITIONS ${CMAKE_SOURCE_DIR}/lib/Target/X86/X86.td)
tablegen(LLVM X86Registers.inc -gen-register-info)
tablegen(LLVM X86InstrInfo.inc -gen-instr-info -instr-info-expand-mi-operand-info=0)

add_public_tablegen_target(LLVMTestTableGen)

add_llvm_example(LLVMTest
        main.cpp

        DEPENDS
        LLVMTestTableGen
        )
llvm_map_components_to_libnames(llvm_libs
        Core
        Support
        Target

        AllTargetsCodeGens
        AllTargetsAsmParsers
        AllTargetsDescs
        AllTargetsInfos
        AllTargetsDisassemblers
        AllTargetsMCAs
        )
target_link_libraries(LLVMTest ${llvm_libs})