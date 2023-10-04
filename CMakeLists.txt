cmake_minimum_required(VERSION 3.12)

project(MathCompiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# Add the executable target
add_executable(solve 
  src/main.cpp
  src/Analysis/Lexer.hpp
  src/Analysis/SymbolTable.hpp
  src/Analysis/SymbolTable.cpp
  )

