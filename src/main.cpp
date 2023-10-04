#include "Analysis/SymbolTable.hpp"
#include <cctype>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using string = std::string;
template <typename T> using stack = std::stack<T>;

bool isFileType(const string& filename, const string& extension) {
  stack<char> ext;

  for (string::const_reverse_iterator it = filename.rbegin(); it != filename.rend(); it++) {
    if (*it == '.') {
      break;
    }
    ext.push(*it);
  }

  if (ext.size() != extension.size()) {
    return false;
  }

  for (string::const_iterator it = extension.begin(); it != extension.end(); it++) {
    if (*it != ext.top()) {
      return false;
    }
    ext.pop();
  }

  return true;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cout << "\033[31mInvalid number of arguments, expected:\n    " << argv[0] << " <filename>\e[0m\n";
    return -1;
  }

  string filename(argv[1]);
  if (isFileType(filename, "math")) {
    std::cout << "File Detected\n";
  }

  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file '" << filename << "'\n";
    return 1;
  }
  
  SymbolTable symbols;
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
      
      if (!symbols.insert(word)) {
        std::cerr << 'L' << line << ": variable with name '" << word << "' already exists within this scope.\n";
        return -1;
      }

      word.clear();
      
    } else if (std::isdigit(file.peek())) {
      do {
        word.push_back(file.peek());
        file.get();
      } while (std::isdigit(file.peek()));

      if (file.peek() == '.') {
        word.push_back('.');
        file.get();
      }
      
      while (std::isdigit(file.peek())) {
        word.push_back(file.peek());
        file.get();
      }

      if (file.peek() == '_' || std::isalpha(file.peek())) {
        word.push_back(file.peek());
        std::cerr << 'L' << line << ": unknown symbol '" << (char)file.peek() << "' found in '" << word << "'.\n";
        return -1;
      }

    } else {
      word.push_back(file.peek());
      std::cerr << 'L' << line << ": unknown symbol '" << (char)file.peek() << "' found in '" << word << "'.\n";
      return -1;
    
    }
  }

  file.close();
  symbols.print();

  return 0;
}
