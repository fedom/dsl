cmake_minimum_required(VERSION 2.8)
project(Lexer)

#add_definitions()

add_compile_options(-pipe -Wall -g -std=c++11)
include_directories(
	./
)

set(SRC_LIST lexer.cpp list_lexer.cpp parser.cpp list_parser.cpp)

add_executable(lexer ${SRC_LIST} main.cpp)
