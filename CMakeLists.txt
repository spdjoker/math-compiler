cmake_minimum_required(VERSION 3.12)

project(MathCompiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable target
add_executable(solve 
  src/main.cpp
  src/Lexer.hpp
  )

