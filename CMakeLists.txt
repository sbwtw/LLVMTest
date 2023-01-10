cmake_minimum_required(VERSION 3.24)

set(LLVM_LINK_COMPONENTS
        Core
        Support
        Target

        X86CodeGen
        X86AsmParser
        X86Desc
        X86Info
        X86Disassembler
        X86TargetMCA
        )

add_executable(LLVMTest
        main.cpp
        )
llvm_map_components_to_libnames(llvm_libs
        Core
        Support
        Target

        X86CodeGen
        X86AsmParser
        X86Desc
        X86Info
        X86Disassembler
        X86TargetMCA
        )
target_link_libraries(LLVMTest LLVM ${llvm_libs})