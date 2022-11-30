CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -pedantic $(INCLUDES)

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/graph.cpp src/vertex.cpp -o $@

bin/tests: tests/tests.cc 
	$(CXX) $(CXXFLAGS) tests/tests.cc src/main.cpp src/graph.cpp src/vertex.cpp -o $@
					

.DEFAULT_GOAL := exec
# .PHONY: clean exec tests 
.PHONY: clean exec 

clean:
	rm -rf ./bin/*
