#include "LexicalAnalyzer.hpp"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

LexicalAnalyzer::LexicalAnalyzer(SymbolTable& root_table) : tokens(), symbols(root_table) {}

void LexicalAnalyzer::tokenize(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file '" << filename << "'\n";
    std::exit(1);
    return;
  }

  std::cout << "Opening file '" << filename << "'...\n";
  
  std::string word;
  word.reserve(8);
  unsigned int line = 1, col = 1, columnStart;

  while (file.peek() != -1) {
    // Line break
    if (file.peek() == '\n') {
      do {
        line++;
        col = 1;
        file.get();
      } while (file.peek() == '\n');
      continue;
    } 

    // Remove Whitespace;
    if (isWhitespace(file.peek())) {
      do { 
        file.get();
        col++;
      } while (isWhitespace(file.peek()));
      continue;
    }

    // Get Identifiers
    if (std::isalpha(file.peek()) || file.peek() == '_') {
      columnStart = col;
      do {
        word.push_back(file.peek());
        file.get();
        col++;
      } while (std::isalnum(file.peek()) || file.peek() == '_');
      int id;
      symbols.insert(word, &id);
      tokens.push_back(Token(Type::IDENTIFIER, id, line, columnStart));
      word.clear();
      continue;
    } 

    // Convert Float Literals
    if (std::isdigit(file.peek())) {
      columnStart = col;
      // Consume first digit
      word.push_back(file.peek());
      file.get();
      col++;
      // Consume any trailing digits
      while (std::isdigit(file.peek()) || file.peek() == '_') {
        if (file.peek() == '_') {
          file.get();
          col++;
          continue;
        }
        word.push_back(file.peek());
        file.get();
        col++;
      }
      // Specify precision indicator
      if (file.peek() == '.') {
        word.push_back('.');
        file.get();
        col++;
      }
      // Consume any remaining digits (precision)
      while (std::isdigit(file.peek())) {
        word.push_back(file.peek());
        file.get();
        col++;
      }
      // If there is anything else following the float, invalid symbol.
      if (file.peek() == '_' || std::isalpha(file.peek())) {
        std::cerr << "[L" << line << ':' << col 
          << "]: Unknown symbol '" << (char)file.peek() 
          << "' found in '" << word << (char)file.peek() 
          << "'. Did you mean '" << word << "'\n";
        std::exit(1);
        return;
      }
      tokens.push_back(Token(Type::FLOAT_LITERAL, std::stof(word), line, columnStart));
      word.clear();
      continue;
    }

    // Statement Terminator
    if (file.peek() == CHAR_OP_TERMINATOR) {
      columnStart = col;
      tokens.push_back(Token(Type::OP_TERMINATOR, line, columnStart));
      file.get();
      col++;
      continue;
    } 

    // Assignment Operator
    if (file.peek() == CHAR_OP_ASSIGNMENT) {
      columnStart = col;
      tokens.push_back(Token(Type::OP_ASSIGNMENT, line, columnStart));
      file.get();
      col++;
      continue;
    } 

    // Addition Operator
    if (file.peek() == CHAR_OP_ADDITION) {
      columnStart = col;
      tokens.push_back(Token(Type::OP_ADDITION, line, columnStart));
      file.get();
      col++;
      continue;
    } 

    // Subtraction Operator
    if (file.peek() == CHAR_OP_SUBTRACTION) {
      columnStart = col;
      tokens.push_back(Token(Type::OP_SUBTRACTION, line, columnStart));
      file.get();
      col++;
      continue;
    } 

    // Multiplication Operator
    if (file.peek() == CHAR_OP_MULTIPLICATION) {
      columnStart = col;
      tokens.push_back(Token(Type::OP_MULTIPLICATION, line, columnStart));
      file.get();
      col++;
      continue;
    } 

    // Division Operator
    if (file.peek() == CHAR_OP_DIVISION) {
      columnStart = col;
      tokens.push_back(Token(Type::OP_DIVISION, line, columnStart));
      file.get();
      col++;
      continue;
    } 

    // Modulo Operator
    if (file.peek() == CHAR_OP_MODULO) {
      columnStart = col;
      tokens.push_back(Token(Type::OP_MODULO, line, columnStart));
      file.get();
      col++;
      continue;
    } 

    // Any unspecified rules, throw error
    else {
      std::cerr << "[L" << line << ':' << col << "]: Unknown symbol '" << (char)file.peek() << "' found in '" << word << (char)file.peek() << "'.\n";
      std::exit(1);
      return;
    
    }
  }
  
  file.close();
}

// Wayyyyy too useless to keep :P
const char* FG_RESET            = "\e[0m";
const char* FG_BLACK            = "\e[30m";
const char* FG_RED              = "\e[31m";
const char* FG_GREEN            = "\e[32m";
const char* FG_YELLOW           = "\e[33m";
const char* FG_BLUE             = "\e[34m";
const char* FG_MAGENTA          = "\e[35m";
const char* FG_CYAN             = "\e[36m";
const char* FG_WHITE            = "\e[37m";
const char* FG_BRIGHT_BLACK     = "\e[90m";
const char* FG_BRIGHT_RED       = "\e[91m";
const char* FG_BRIGHT_GREEN     = "\e[92m";
const char* FG_BRIGHT_YELLOW    = "\e[93m";
const char* FG_BRIGHT_BLUE      = "\e[94m";
const char* FG_BRIGHT_MAGENTA   = "\e[95m";
const char* FG_BRIGHT_CYAN      = "\e[96m";
const char* FG_BRIGHT_WHITE     = "\e[97m";

void LexicalAnalyzer::print() {
  for (Token& t : tokens) {
    switch (t.type()) {
      case Type::IDENTIFIER:
        printf("<%s%s%s, %d", FG_MAGENTA, t.typeName(), FG_RESET, t.valueAs<int>());
        break;
      case Type::FLOAT_LITERAL:
        printf("<%s%s%s, %.4ff", FG_CYAN, t.typeName(), FG_RESET, t.valueAs<float>());
        break;
      case Type::OP_TERMINATOR:
      case Type::OP_ASSIGNMENT:
      case Type::OP_ADDITION:
      case Type::OP_SUBTRACTION:
      case Type::OP_MULTIPLICATION:
      case Type::OP_DIVISION:
      case Type::OP_MODULO:
        printf("<%s%s", FG_RED, t.typeName());
        break;
      
      default:
        printf("<%sUNKNOWN", FG_BLUE);
        break;
    }
    printf("%s, %sL%d:%d%s>\n", FG_RESET, FG_BRIGHT_YELLOW, t.line(), t.column(), FG_RESET);
  }
}
