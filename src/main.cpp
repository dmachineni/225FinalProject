#include "graph.h"
#include "vertex.h"
#include <iostream>

int main() {
    Graph g;
    // std::cout << g.adjlistSize() << std::endl; // this can be a test case, should equal 3199
    // std::cout << g.airportsSize() << std::endl; // can also be test case, should equal 3199
    // std::cout << g.getAirport(1)<< std::endl; // should equal "Goroka Airport 1"
    //std::cout << g.getAdjList(0) << std::endl; // should equal "2990, 2979, 1735, 2954, 2983, 1726, 3964, 2960, 4029, 1701, 2948, 2958, 2985, 2975, 6147, 2988, 4374, "
    //std::cout << g.getAdjList(4) << std::endl;
    // std::cout << g.BFS(0).size() << std::endl;
    //std::cout << "before" << std::endl;
    std::cout << g.getAdjList(0) << std::endl;
    std::cout << "..." << std::endl;
    std::cout << g.getAdjList(8) << std::endl;
    std::cout << "..." << std::endl;
    std::cout << "distance: " << g.airports[0].calculateWeight(g.airports[8]) << std::endl;
    // std::cout << g.getAdjList(g.idToIndex("2")) << std::endl; 
    // std::cout << "..." << std::endl;
    // std::cout << g.getAdjList(g.idToIndex("3")) << std::endl;
    // std::cout << "..." << std::endl;
    // std::cout << g.getAdjList(g.idToIndex("4")) << std::endl;
    // std::cout << "..." << std::endl;
    // std::cout << g.getAdjList(g.idToIndex("5")) << std::endl;
    //std::cout << "..." << std::endl;
    // std::cout << g.getAdjList(g.idToIndex("5447")) << std::endl;
    // std::cout << "..." << std::endl;
    // std::cout << g.getAdjList(g.idToIndex("5443")) << std::endl;
    // std::cout << "..." << std::endl;
    // std::cout << g.getAdjList(g.idToIndex("7")) << std::endl;
    std::cout << g.getShortestPath(g.airports[0].airport_id, g.airports[8].airport_id) << std::endl;
}