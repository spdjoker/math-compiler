#ifndef MATH_LEXER_HPP
#define MATH_LEXER_HPP

#include <string>
#include <vector>

#include "types/Token.hpp"

constexpr char CHAR_OP_TERMINATOR     = ';';
constexpr char CHAR_OP_ASSIGNMENT     = '=';
constexpr char CHAR_OP_ADDITION       = '+';
constexpr char CHAR_OP_SUBTRACTION    = '-';
constexpr char CHAR_OP_MULTIPLICATION = '*';
constexpr char CHAR_OP_DIVISION       = '/';
constexpr char CHAR_OP_MODULO         = '%';

struct SymbolTable;

struct LexicalAnalyzer {
  std::vector<Token> tokens;
  SymbolTable& symbols;

  LexicalAnalyzer(SymbolTable& root_table);

  void tokenize(const std::string &filename);
  void print();

private:
  bool isWhitespace(char c) const { return c == ' ' || c == '\t'; }
};

#endif
