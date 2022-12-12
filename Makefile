CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++2a -g -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

exec: bin/exec
# tests: bin/tests

bin/exec: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/graph.cpp src/vertex.cpp -o $@

# bin/tests: ./tests/tests.cc ./src/dna_strand.cc ./includes/dna_strand.hpp
# 	$(CXX) $(CXXFLAGS) ./tests/tests.cc ./src/dna_strand.cc -o $@

.DEFAULT_GOAL := exec
# .PHONY: clean exec tests 
.PHONY: clean exec 

clean:
	rm -rf ./bin/*
