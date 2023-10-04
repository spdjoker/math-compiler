#include "SymbolTable.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using hashmap = std::unordered_map<std::string, float>;

SymbolTable::SymbolTable()
  : symbols()
  , parent(nullptr)
  , count(0) {}

SymbolTable::SymbolTable(SymbolTable *parent)
  : symbols()
  , parent(parent)
  , count(parent->count) {}

bool SymbolTable::insert(const std::string &key) {
  std::pair<hashmap::iterator, bool> p;

  p = symbols.insert({key, 0.0f});

  if (p.second) {
    count += 1;
    return true;
  }

  return false;
}

bool SymbolTable::find(const std::string &key, float **value) {
  hashmap::iterator it = symbols.find(key);
  if (it == symbols.end()) {
    if (parent) {
      return parent->find(key, value);
    }
    return false;
  }
  *value = &it->second;
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

  hashmap::iterator it = symbols.begin();
  
  while (it != symbols.end()) {
    std::cout << std::left << std::setw(32) << it->first << std::setw(16) << std::setprecision(8) << it->second << '\n';
    it++;
  }
}

void SymbolTable::print() {
  std::cout << "========================================================================\n";
  std::cout << std::left << std::setw(32) << "identifier" << std::setw(16) << "value" << std::endl;
  std::cout << "========================================================================\n";
  printData();
  std::cout << "========================================================================\n";
}
