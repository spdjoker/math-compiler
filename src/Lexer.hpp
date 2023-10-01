#ifndef MATH_LEXER_HPP
#define MATH_LEXER_HPP

namespace Lexer {

enum class TokenType {
  IDENTIFIER,
  DOUBLE_LITERAL,
  ASSIGN_OPERATOR
};

class Token {
  TokenType m_type;
  void* m_data;

public:
  Token(TokenType type, void* data) : m_type(type), m_data(data) {}

  constexpr TokenType type() {
    return m_type;
  }

  
};

}

#endif
