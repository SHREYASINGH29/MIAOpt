#ifndef PARSER_H 
#define PARSER_H 

#include "InstructionInfo.h"
#include "Mapping.h"
#include <string>
#include <vector>

std::vector<Mapping *> getModelInfo(std::string FileName);
#endif
