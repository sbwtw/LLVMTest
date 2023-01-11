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
tablegen(LLVM X86.inc -print-enums -class=Register)

message(${CMAKE_SOURCE_DIR})

add_executable(LLVMTest
        main.cpp
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