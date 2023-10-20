#ifndef MATH_LEXER_HPP
#define MATH_LEXER_HPP

#include "SymbolTable.hpp"
#include <string>
#include <vector>

using string = std::string;
template <typename T> using vector = std::vector<T>;

namespace Lexer {

struct Token {
  enum class Type {
    IDENTIFIER = 1,
    FLOAT_LITERAL = 2
  };

private:
  Type m_type;
  void* m_value;

public:
  Token(Type type, void* value);
  ~Token();

  Type type() const { return m_type; }
  void* value() const { return m_value; }

  bool isIdentifier() { return m_type == Type::IDENTIFIER; }
  bool isFloatLiteral() { return m_type == Type::FLOAT_LITERAL; }
};

struct Analysis {
  vector<Token> tokens;
  SymbolTable symbols;

  Analysis(const string& filename);

  void Tokenize(const string &filename);
  void PrintTokens();
  void PrintSymbols();
};

}

#endif
