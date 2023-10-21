#include <stack>
#include <iostream>

#include "analysis/LexicalAnalyzer.hpp"
#include "symbol_table/SymbolTable.hpp"

using string = std::string;

constexpr int FLAG_PRINT_SYMBOL_TABLE = 1;
constexpr int FLAG_PRINT_TOKENS = 2;

void check(void* chunk1, void* chunk2) {
  std::cout << *((float*)chunk1) << ' ' << *((float*)chunk2) << '\n';
}

int main(int argc, char** argv) {
  
  void* chunk1 = new float(argc);
  void* chunk2 = malloc(sizeof(float));
  // float* fp1 = (float*)chunk1;
  float* fp2 = (float*)chunk2;
  // *fp1 = 2;
  *fp2 = 5;
  check(chunk1, chunk2);

  if (argc == 1) {
    std::cout << "\033[31mMissing required argument <filename0>\nUsage: " << argv[0] << "[-t] [-s] <filename0> [filename1...]\e[0m\n";
    return -1;
  }

  std::vector<string> filenames;
  int flags = 0;
  int i = 1;

  while (i < argc) {
    string arg = argv[i];
    // Process flags
    if (*arg.begin() == '-') {
      string::iterator it = arg.begin() + 1;
      switch(*it) {
        case 't': // Print Tokens
          flags |= FLAG_PRINT_TOKENS;
          it++;
          if (*it == 's') {
            flags |= FLAG_PRINT_SYMBOL_TABLE;
            it++;
          }
          break;
        case 's': // Print Symbol Table
          flags |= FLAG_PRINT_SYMBOL_TABLE;
          it++;
          if (*it == 't') {
            flags |= FLAG_PRINT_TOKENS;
            it++;
          }
          break;
      }
      // If flag has more characters than required by switch, error.
      if (it != arg.end()) {
        std::cout << "\033[31mInvalid option '" << arg << "'\nOptions: [-t] [-s]\e[0m\n";
        return -1;
      }
    } else {
      // Add filenames
      filenames.push_back(arg);
    }
    i++;
  }
  
  // No file provided
  if (!filenames.size()) {
    std::cout << "\033[31mMissing required argument <filename0>\nUsage: " << argv[0] << "[-t] [-s] <filename0> [filename1...]\e[0m\n";
    return -1;
  }
  
  SymbolTable rootScope;
  LexicalAnalyzer lexer(rootScope);
  lexer.tokenize(filenames[0]);
  
  if (flags & FLAG_PRINT_SYMBOL_TABLE) {
    rootScope.print();
  }
  if (flags & FLAG_PRINT_TOKENS) {
    lexer.print();
  }

  return 0;
}
