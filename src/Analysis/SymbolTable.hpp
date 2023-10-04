#ifndef MATH_SYMBOL_TABLE
#define MATH_SYMBOL_TABLE

#include <unordered_map>
#include <string>

class SymbolTable {
  std::unordered_map<std::string, float> symbols;
  SymbolTable *parent;
  unsigned int count;

  void printData();

public:
  SymbolTable();
  SymbolTable(SymbolTable *parent);

  bool insert(const std::string& key);
  bool find(const std::string& key, float **value);
  
  constexpr int size();

  void print();
};

#endif
