#include "SymbolTable.hpp"
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

SymbolTable::SymbolTable()
  : symbols()
  , parent(nullptr)
  , count(0) {}

SymbolTable::SymbolTable(SymbolTable *parent)
  : symbols()
  , parent(parent)
  , count(parent->count) {}

// Inserts a new variable into the local scope Symbol Table
bool SymbolTable::insert(const std::string &key, int* id) {
  auto p = symbols.insert({key, count});

  if (p.second) {
    auto d = values.insert({count, SymbolEntry::Data(key, count)});
    *id = count;
    count += 1;
    return true;
  }
  *id = p.first->second;
  return false;
}

// Finds the variable if it is defined locally, or the scope above recursively
SymbolEntry SymbolTable::find(const std::string &key) {
  symbol_map::iterator it = symbols.find(key);

  // If the key is not in this scope.
  if (it == symbols.end()) {
    // Check in parent scope if it exists
    if (parent) {
      return parent->find(key);
    }
    // Otherwise there is none, return an empty entry
    return SymbolEntry();
  }
  // Otherwise return the entry
  return SymbolEntry(&(*values.find(it->second)).second, true);
}

constexpr int SymbolTable::size() {
  return count;
}

void SymbolTable::printData() {
  entry_map::iterator it = values.begin();

  while (it != values.end()) {
    std::cout << std::left << " " 
      << std::setw(7) << it->second.id << "| \e[33m" 
      << std::setw(32) << it->second.name << "\e[0m| "
      << std::setw(5) << (it->second.init ? "\e[32mINIT" : "\e[31mNULL") << "\e[0m | "
      << std::setw(16) << std::setprecision(8) << it->second.value << "\n";
    it++;
  }
}

void SymbolTable::print() {
  std::cout << "========================================================================\n";
    std::cout << std::left 
    << std::setw(8) << " ID" 
    << std::setw(34) << "| Variable Name" 
    << std::setw(7) << "| Case"
    << std::setw(16) << "| Value" << '\n';
  std::cout << "========================================================================\n";
  printData();
  std::cout << "========================================================================\n";
}
