#include "graph.h"
#include "vertex.h"
#include <iostream>
#include <string>

int main() {
    //Graph g("data/airports_cleaned.csv", "data/adjacency_list.csv", "data/distance_matrix.csv"); // creates graph from correct data
    //Graph gg; // creates graph from scratch, should match correct data
    Graph g(true); // false for small dataset, large for true
    
    //gg.writeAdjListToFile("data/adjacency_list_large.csv");
    //gg.writeAirportsToFile("data/airports_cleaned_large.csv");
   // gg.writeDistMatrixToFile("data/distance_matrix_large.csv");
   //std::cout << g.adjlistSize() << std::endl; // should equal 220 (IT DOES)
    //std::cout << g.airportsSize() << std::endl; // shoudl equal 220 (IT DOES)
    
    // should print out same values (THEY DO) because the graphs should be the same
    //std::cout << g.BFSTraversal(0).size() << std::endl;
    //std::cout << gg.BFSTraversal(0).size() << std::endl;
    
    // std::cout << "distance: " << g.airports[0].calculateWeight(g.airports[206]) << std::endl; // distance between two airports
    // std::cout << "distance: " << g.airports[206].calculateWeight(g.airports[114]) << std::endl;
    // std::cout << "To get from " << g.airports[0].airport_name << " to " << g.airports[114].airport_name << ", you fly "
    // <<g.getShortestPath(g.airports[0].airport_id, g.airports[114].airport_id) << " km"<< std::endl; //should equal sum of above 2 lines (IT DOES)
    // std::cout << gg.getShortestPath(g.airports[0].airport_id, g.airports[114].airport_id) << std::endl; // should be same as line above (IT IS)
    // Graph g2(true);
    // std::cout << g2.BFSTraversal(0).size() << std::endl;

    // std::cout << "start: " << g.airports[0].airport_name << " end: " <<g.airports[114].airport_name << '\n'; 
    // std::vector<int> Asearch = g.AStarSearch(g.airports[0].airport_id, g.airports[114].airport_id);
    std::cout << "start: " << g.airports[g.idToIndex(2965)].airport_name << " end: " <<g.airports[g.idToIndex(6160)].airport_name << '\n'; 
    std::vector<int> Asearch = g.AStarSearch(2965, 6160);
    std::cout << "size: " << Asearch.size() << '\n';
    std::cout << "from main: " << '\n';
    for(size_t i = 0 ; i < Asearch.size(); i++) {
        if(Asearch[i] == -400) {
            std::cout << -400 << std::endl;
            continue;
        }
        std::cout << g.airports[g.idToIndex(Asearch[i])].airport_name << std::endl;
    }
}


/*
    Notes: 
        - airports takes in an index
        - 
*/