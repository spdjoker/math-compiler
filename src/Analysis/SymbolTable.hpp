#ifndef MATH_SYMBOL_TABLE
#define MATH_SYMBOL_TABLE

#include <unordered_map>

#include "types/SymbolEntry.hpp"

using symbol_map = std::unordered_map<std::string, int>;
using entry_map = std::unordered_map<int, SymbolEntry::Data>;

struct SymbolTable {
  SymbolTable(SymbolTable *parent);
  SymbolTable();

  bool insert(const std::string& key, int* id);
  SymbolEntry find(const std::string& key);

  constexpr int size();

  void print();

private:
  SymbolTable *parent;
  unsigned int count;

  symbol_map symbols;
  entry_map values;

  void printData();
};

#endif
