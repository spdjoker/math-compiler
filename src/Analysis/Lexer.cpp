#include "Lexer.hpp"

#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "SymbolTable.hpp"

namespace Lexer {

Token::Token(Type type, void* id) 
  : m_type(type)
  , m_value(id)
{}

Token::~Token() {
  std::cout << "DEALLOC\n";
  if (!m_value) {
    return;
  }
  if (m_type == Type::IDENTIFIER) {
    delete (int*)m_value;
    return;
  }
  if (m_type == Type::FLOAT_LITERAL) {
    delete (float*)m_value;
    return;
  }
}

Analysis::Analysis(const string& filename) : tokens(), symbols() {
  Tokenize(filename);
}

void Analysis::Tokenize(const string& filename) {

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file '" << filename << "'\n";
    std::exit(1);
    return;
  }
  
  std::string word;
  word.reserve(8);
  unsigned int line = 1;

  while (!file.eof()) {
    if (file.peek() == '\n') {
      do {
        line++;
        file.get();
      } while (file.peek() == '\n');

    } else if (file.peek() == ' ' || file.peek() == '\t') {
      do { 
        file.get();
      } while (file.peek() == ' ' || file.peek() == '\t');
    
    } else if (file.peek() == ';') {
      file.get();

    } else if (std::isalpha(file.peek()) || file.peek() == '_') {
      do {
        word.push_back(file.peek());
        file.get();
      } while (std::isalnum(file.peek()) || file.peek() == '_');
      
      int id;
      if (!symbols.insert(word, &id)) {
        std::cerr << 'L' << line << ": variable with name '" << word << "' already exists within this scope.\n";
        std::exit(1);
        return;
      }
      
      int* ptr = new int(id);
      tokens.push_back(Lexer::Token(Lexer::Token::Type::IDENTIFIER, ptr));
      
      word.clear();
      
    } else if (std::isdigit(file.peek())) {
      // do {
      //   word.push_back(file.peek());
      //   file.get();
      // } while (std::isdigit(file.peek()));
      //
      // if (file.peek() == '.') {
      //   word.push_back('.');
      //   file.get();
      // }
      // 
      // while (std::isdigit(file.peek())) {
      //   word.push_back(file.peek());
      //   file.get();
      // }
      //
      // if (file.peek() == '_' || std::isalpha(file.peek())) {
      //   word.push_back(file.peek());
      //   std::cerr << 'L' << line << ": unknown symbol '" << (char)file.peek() << "' found in '" << word << "'.\n";
      //   std::exit(1);
      //   return;
      // }

    } else {
      word.push_back(file.peek());
      std::cerr << 'L' << line << ": unknown symbol '" << (char)file.peek() << "' found in '" << word << "'.\n";
      std::exit(1);
      return;
    
    }
  }
  
  file.close();
}

void Analysis::PrintTokens() {
  for (Token &t : tokens) {
    if (t.isIdentifier()) {
      std::cout << '<' << "IDENTIFIER," << (*((int*)t.value())) << ">\n";
      continue;
    }
    if (t.isFloatLiteral()) {
      std::cout << '<' << "FLOAT_LIT," << (*((float*)t.value())) << ">\n";
      continue;
    }
  }
}

void Analysis::PrintSymbols() {
  symbols.print();
}

}
