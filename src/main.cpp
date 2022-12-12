#include "graph.h"
#include "vertex.h"
#include <iostream>
#include <string>

int main() {
    // Graph g("data/airports_cleaned.csv", "data/adjacency_list.csv", "data/distance_matrix.csv"); // creates graph from correct data
    // Graph gg(true); // creates graph from scratch, should match correct data
    Graph g(false); // false for small dataset, large for true
    
//     gg.writeAdjListToFile("data/adjacency_list_large.csv");
//     gg.writeAirportsToFile("data/airports_cleaned_large.csv");
//    gg.writeDistMatrixToFile("data/distance_matrix_large.csv");
//    std::cout << g.adjlistSize() << std::endl; // should equal 220 (IT DOES)
//     std::cout << g.airportsSize() << std::endl; // shoudl equal 220 (IT DOES)
    
    // should print out same values (THEY DO) because the graphs should be the same
    std::cout << g.BFSTraversal(0).size() << std::endl;
    // std::cout << gg.BFSTraversal(0).size() << std::endl;
    
    std::cout << "distance: " << g.airports[0].calculateWeight(g.airports[206]) << std::endl; // distance between two airports
    std::cout << "distance: " << g.airports[206].calculateWeight(g.airports[114]) << std::endl;
    std::cout << "To get from " << g.airports[0].airport_name << " to " << g.airports[114].airport_name << ", you fly "
    <<g.getShortestPath(g.airports[0].airport_id, g.airports[114].airport_id) << " km"<< std::endl; //should equal sum of above 2 lines (IT DOES)
    // std::cout << "connection is: " << g.airports[206].airport_name << std::endl;
    // std::cout << gg.getShortestPath(g.airports[0].airport_id, g.airports[114].airport_id) << std::endl; // should be same as line above (IT IS)
    // Graph g2(true);
    // std::cout << g2.BFSTraversal(0).size() << std::endl;

    std::cout << "\n \n" << "------A* SEARCH------" << std::endl;

    std::cout << "start: " << g.airports[0].airport_name << " end: " <<g.airports[114].airport_name << '\n'; 
    std::vector<int> Asearch = g.AStarSearch(g.airports[0].airport_id, g.airports[114].airport_id);
    std::cout << "size: " << Asearch.size() << '\n';
    
    for(size_t i = 0 ; i < Asearch.size(); i++) {
        // std::cout << g.airports[i].airport_name << std::endl;
        std::cout << g.airports[g.idToIndex(Asearch[i])].airport_name << std::endl;
    }

    int nadi_distance = 0;
    nadi_distance += g.calculateHValues(0, Asearch[0]);
    nadi_distance += g.calculateHValues(Asearch[0], 114);
    std::cout << "nadi: " << nadi_distance << std::endl;

    int honiara_distance = 0;
    honiara_distance += g.calculateHValues(0, 4074);
    honiara_distance += g.calculateHValues(4074, 114);
    std::cout << "honiara: " << honiara_distance << std::endl;




    std::cout << "\n \n" << "------LANDMARK PATH------" << std::endl;

    std::cout <<  "---TEST CASE 1---" << std::endl;
    std::cout << "start: " << g.airports[0].airport_name << ", mid: " << g.airports[g.idToIndex(1960)].airport_name << ", end: " <<g.airports[114].airport_name << '\n';
    double a = g.getShortestPath(g.airports[0].airport_id, 1960);
    std::cout << "start to mid: " << a << "km" << std::endl;
    double b = g.getShortestPath(1960, g.airports[114].airport_id);
    std::cout << "mid to end: " << b << "km" << std::endl;
    double total1 = g.landmarkPath(g.airports[0].airport_id, 1960, g.airports[114].airport_id); 
    std::cout << "Landmark Path distance: " << a << " + " << b << " = " << total1 << std::endl;
    if (total1 == a + b) {
        std::cout << "TRUE" << std::endl;
    } else { std::cout << "FALSE" << std::endl; }


    std::cout << "\n ---TEST CASE 2---" << std::endl;
    std::cout << "start: " << g.airports[0].airport_name << ", mid: " << g.airports[g.idToIndex(4074)].airport_name << ", end: " <<g.airports[114].airport_name << '\n';
    // << ", mid: " << g.airports[4074].airport_name
    double x = g.getShortestPath(g.airports[0].airport_id, 4074);
    std::cout << "start to mid: " << x << "km" << std::endl;
    double y = g.getShortestPath(4074, g.airports[114].airport_id);
    std::cout << "mid to end: " << b << "km"  << std::endl;
    double total2 = g.landmarkPath(g.airports[0].airport_id, 4074, g.airports[114].airport_id); 
    std::cout << "Landmark Path distance: " << x << " + " << y << " = "  << total2 << std::endl;
    if (total2 == x + y) {
        std::cout << "TRUE" << std::endl;
    } else { std::cout << "FALSE" << std::endl; }

    std::cout <<  "---TEST CASE 3---" << std::endl;
    std::cout << "start: " << g.airports[0].airport_name << ", mid: " << g.airports[g.idToIndex(1960)].airport_name << ", end: " <<g.airports[114].airport_name << '\n';
    double c = g.getShortestPath(g.airports[0].airport_id, 1960);
    std::cout << "start to mid: " << c << "km" << std::endl;
    double d = g.getShortestPath(1960, g.airports[114].airport_id);
    std::cout << "mid to end: " << d << "km" << std::endl;
    std::vector<int> vec;
    vec.push_back(1960);
    double total3 = g.landmarkPath(g.airports[0].airport_id, vec, g.airports[114].airport_id); 
    std::cout << "Landmark Path distance: " << a << " + " << b << " = " << total3 << std::endl;
    if (total3 == a + b) {
        std::cout << "TRUE" << std::endl;
    } else { std::cout << "FALSE" << std::endl; }
}