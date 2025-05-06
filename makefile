llvm:
	clang++ -g -O3 toy_llvm.cpp `llvm-config --cxxflags --ldflags --system-libs --libs all` -o toy
toy:
	clang++ -g -O3 toy.cpp

