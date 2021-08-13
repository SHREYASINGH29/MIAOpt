<h1 align="center">MIAOpt: Modeling Implementation and Optimization for LLVM IR</h1>

## Table of Contents

- [Getting Started](#getting-started)
  - [Building from source](#building-from-sources)
  - [Using with LLVM opt](#using-with-llvm-opt)
  - [Running the demo](#running-the-demo)
 
## Getting Started

MIAOpt is a framework to automatically implement abstraction based on a human readable modeling input. It also optimizes it. 

### Building from sources
Install spatial from https://github.com/resharma/spatial
```sh
$ git clone this_repository.git
$ cd this_repository
$ mkdir build; cd build
$ cmake .. && make
$ make install
```

### Using with LLVM opt
* Path to shared libary and headers should be searchable by the compiler
* In your LLVM IR pass:
  * Include the header file, ```Representation.h```
* Load libSpatial.so and libMIAOpt.so before your pass's shared library
  * ``` opt -load /usr/local/lib/libSpatial.so -load libMIAOpt.so -load yourPass.so ... ```

### Running the demo 
```sh
$ cd MIAOpt
$ mkdir build; cd build
$ cmake .. && make
$ bash run.sh test/tc1.cpp
```
