cmake_minimum_required(VERSION 3.12)

project(MathCompiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

include_directories(src)

# Add the executable target
add_executable(solve 
  src/main.cpp

  # First Phase (Analysis)
  src/analysis/LexicalAnalyzer.cpp
  src/analysis/LexicalAnalyzer.hpp
  src/symbol_table/SymbolTable.cpp
  src/symbol_table/SymbolTable.hpp
  src/symbol_table/SymbolEntry.hpp

  # Intermediate Types
  src/types/Token.hpp
  )

