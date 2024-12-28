toy:
	clang++ -g -O3 toy.cpp
llvm:
	clang++ -g -O3 toy_llvm.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o toy

