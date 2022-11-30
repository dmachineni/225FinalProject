#include "graph.h"
#include <iostream>

int main() {
    std::cout << "helloo" <<std::endl;
    Graph g;
    std::cout << g.adjlistSize() << std::endl; // this can be a test case, should equal 7698
    std::cout << g.airportsSize() << std::endl; // can also be test case, should equal 7698
    std::cout << g.getAirport(0)<< std::endl; // should equal "Goroka Airport 1"
    std::cout << g.getAdjList(2810) << std::endl; // should equal "2990, 2979, 1735, 2954, 2983, 1726, 3964, 2960, 4029, 1701, 2948, 2958, 2985, 2975, 6147, 2988, 4374, "
}