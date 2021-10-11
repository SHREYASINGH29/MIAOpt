#!/bin/bash

set -x
LLVM_HOME=/usr/lib/llvm-12
CC=$LLVM_HOME/bin/clang
OPT=$LLVM_HOME/bin/opt

mkdir -p build
pushd build
cmake ..
make
popd
$CC -O0 -Xclang -disable-O0-optnone -S -emit-llvm -o test.ll $1
$OPT -S -instnamer -load /usr/local/lib/libSpatial.so -load ../build/*MIAOpt* --model-input=test/input.txt --print-inst -load build/*Demo* -demo test.ll -o test-out.ll
