#include "graph.h"
#include <iostream>

int main() {
    std::cout << "helloo" <<std::endl;
    Graph g;
    std::cout << g.getadjacency_lists() << std::endl;
    std::cout << g.getAirports() << std::endl;
    std::cout << g.getAirport(0)<< std::endl;
    std::cout << g.getAdjList(2810) << std::endl;
}