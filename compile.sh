#! /bin/bash

#clang++ -std=c++2b -Wall -Wextra -pedantic -O2 toy.cpp -o myprogram
clang++ -g toy.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o toy
