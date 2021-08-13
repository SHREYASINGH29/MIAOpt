#ifndef TOKEN_H
#define TOKEN_H

#include "string"

enum Toktype {
  instruction,
  operand,
  comma,
  equals,
  pointer,
  newline,
  colon,
  address,
  variable
};

class Token {
  std::string Name;
  Toktype Type;

public:
  Token(std::string Name, Toktype Type);
  Token(Toktype Type);
  Toktype getType();
  std::string getName();
  void print();
};
#endif
