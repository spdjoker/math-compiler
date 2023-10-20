#include "SymbolTable.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using symbol_map = std::unordered_map<std::string, int>;
using value_map = std::unordered_map<int, float>;

SymbolTable::SymbolTable()
  : symbols()
  , parent(nullptr)
  , count(0) {}

SymbolTable::SymbolTable(SymbolTable *parent)
  : symbols()
  , parent(parent)
  , count(parent->count) {}

bool SymbolTable::insert(const std::string &key, int* id) {
  std::pair<symbol_map::iterator, bool> p;

  p = symbols.insert({key, count});

  if (p.second) {
    values.insert({count, 0.0f});
    *id = count;
    count += 1;
    return true;
  }

  return false;
}

bool SymbolTable::find(const std::string &key, float** value) {
  symbol_map::iterator it = symbols.find(key);
  if (it == symbols.end()) {
    if (parent) {
      return parent->find(key, value);
    }
    return false;
  }
  *value = &values.find(it->second)->second;
  return true;
}

constexpr int SymbolTable::size() {
  return count;
}

void SymbolTable::printData() {
  if (parent) {
    std::cout << "------------------------------------------------------------------------\n";
    parent->print();
    std::cout << "------------------------------------------------------------------------\n";
  }

  symbol_map::iterator it = symbols.begin();

  while (it != symbols.end()) {
    std::cout << std::left 
      << std::setw(8) << it->second 
      << std::setw(32) << it->first 
      << std::setw(16) << std::setprecision(8) << values.find(it->second)->second << '\n';
    it++;
  }
}

void SymbolTable::print() {
  std::cout << "========================================================================\n";
  std::cout << std::left << std::setw(8) << "id" << std::setw(32) << "name" << std::setw(16) << "value" << std::endl;
  std::cout << "========================================================================\n";
  printData();
  std::cout << "========================================================================\n";
}
