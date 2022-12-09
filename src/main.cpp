#include "graph.h"
#include "vertex.h"
#include <iostream>

int main() {
    Graph g("data/airports_cleaned.csv", "data/adjacency_list.csv", "data/distance_matrix.csv"); // creates graph from correct data
    //Graph gg; // creates graph from scratch, should match correct data
    
    //gg.writeAdjListToFile("data/adjacency_list_large.csv");
    //gg.writeAirportsToFile("data/airports_cleaned_large.csv");
   // gg.writeDistMatrixToFile("data/distance_matrix_large.csv");
   //std::cout << g.adjlistSize() << std::endl; // should equal 220 (IT DOES)
    //std::cout << g.airportsSize() << std::endl; // shoudl equal 220 (IT DOES)
    
    // should print out same values (THEY DO) because the graphs should be the same
    //std::cout << g.BFSTraversal(0).size() << std::endl;
    //std::cout << gg.BFSTraversal(0).size() << std::endl;

    std::cout << "....." << std::endl;
    //std::cout << "distance: " << g.airports[0].calculateWeight(g.airports[206]) << std::endl; // distance between two airports
    //std::cout << "distance: " << g.airports[206].calculateWeight(g.airports[114]) << std::endl;
    std::cout << g.getShortestPath(g.airports[0].airport_id, g.airports[114].airport_id) << " km"<< std::endl; //should equal sum of above 2 lines (IT DOES)
    //std::cout << gg.getShortestPath(g.airports[0].airport_id, g.airports[114].airport_id) << std::endl; // should be same as line above (IT IS)
}