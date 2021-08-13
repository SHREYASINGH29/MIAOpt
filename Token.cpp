#include "Token.h"
#include "iostream"

Token::Token(std::string Name, Toktype Type) {
  this->Name = Name;
  this->Type = Type;
}

Token::Token(Toktype Type) {
  this->Name = "";
  this->Type = Type;
}

Toktype Token::getType() {
  return Type;
}

std::string Token::getName() {
  return Name;
}

void Token::print() {
  switch (Type) {
  case instruction:
    std::cout << "instruction " << Name << std::endl;
    break;
  case operand:
    std::cout << "operand " << Name << std::endl;
    break;
  case comma:
    std::cout << "comma " << std::endl;
    break;
  case equals:
    std::cout << "equals " << std::endl;
    break;
  case pointer:
    std::cout << "pointer " << std::endl;
    break;
  case newline:
    std::cout << "newline " << std::endl;
    break;
  case colon:
    std::cout << "colon " << std::endl;
    break;
  case address:
    std::cout << "address " << std::endl;
    break;
  }
}
