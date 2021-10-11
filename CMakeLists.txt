cmake_minimum_required(VERSION 3.4)
project(PROJECT)
# we need LLVM_HOME in order not automatically set LLVM_DIR
if(NOT DEFINED ENV{LLVM_HOME})
    message(FATAL_ERROR "$LLVM_HOME is not defined")
else ()
    set(ENV{LLVM_DIR} $ENV{LLVM_HOME}/lib/cmake/llvm)
endif()

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
include_directories("/usr/local/include/spatial")

add_library(MIAOpt MODULE
    Inst.cpp
    InstRep.cpp
    InstructionInfo.cpp
    IMParser.cpp
    IMLexer.cpp
    Parser.cpp
    Substitution.cpp
    Token.cpp
    Mapping.cpp
    Representation.cpp
)

set_target_properties(MIAOpt PROPERTIES
    COMPILE_FLAGS "-fno-rtti -std=c++14 -g -lfl"
)

