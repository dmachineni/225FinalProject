#include "graph.h"
#include "vertex.h"
#include <iostream>
#include <string>

int main() {
    // Graph g("data/airports_cleaned_large.csv", "data/adjacency_list_large.csv", "data/distance_matrix_large.csv"); // creates graph from correct data
    Graph g(true); // false for small dataset, large for true
    // Graph gg(true); // creates graph from scratch, should match correct data
    // gg.writeAdjListToFile("data/adjacency_list_large.csv");
    // gg.writeAirportsToFile("data/airports_cleaned_large.csv");
    // gg.writeDistMatrixToFile("data/distance_matrix_large.csv");
    // std::cout << g.adjlistSize() << std::endl; // should equal 220 (IT DOES)
    // std::cout << g.airportsSize() << std::endl; // shoudl equal 220 (IT DOES)
    
    // should print out same values (THEY DO) because the graphs should be the same
    // std::cout << g.BFSTraversal(0).size() << std::endl;
    // std::cout << gg.BFSTraversal(0).size() << std::endl;
    
    std::cout << "distance: " << g.airports[0].calculateWeight(g.airports[206]) << std::endl; // distance between two airports
    std::cout << "distance: " << g.airports[206].calculateWeight(g.airports[114]) << std::endl;
    std::cout << "To get from " << g.airports[0].airport_name << " to " << g.airports[114].airport_name << ", you fly "
    <<g.getShortestPath(g.airports[0].airport_id, g.airports[114].airport_id) << " km"<< std::endl; //should equal sum of above 2 lines (IT DOES)
    // std::cout << "connection is: " << g.airports[206].airport_name << std::endl;
    // std::cout << gg.getShortestPath(g.airports[0].airport_id, g.airports[114].airport_id) << std::endl; // should be same as line above (IT IS)
    // Graph g2(true);
    // std::cout << g2.BFSTraversal(0).size() << std::endl;

    std::cout << "\n \n" << "------SHORTEST PATH------" << std::endl;

    std::cout <<  "---TEST CASE 1---" << std::endl; //0 for smaller dataset
    std::cout << "start: " << g.airports[4].airport_name << ", end: " << g.airports[4].airport_name << '\n';
    double shortestPathTest1_a = g.getShortestPath(g.airports[4].airport_id, g.airports[4].airport_id);
    if(shortestPathTest1_a == 0) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    std::cout <<  "---TEST CASE 2---" << std::endl; //0,206 for smaller dataset
    std::cout << "start: " << g.airports[4].airport_name << ", end: " <<g.airports[2045].airport_name << '\n';
    double shortestPathTest1_b = g.getShortestPath(g.airports[4].airport_id, g.airports[2045].airport_id);

    Vertex startVertex = g.idToAirport(g.airports[4].airport_id);
    double calculatedWeightB = startVertex.calculateWeight(g.idToAirport(g.airports[2045].airport_id));
    std::cout << "dist from 4 to 2045: " << calculatedWeightB << " ; shortest Path output: "  << shortestPathTest1_b<< '\n';

    if(std::abs(shortestPathTest1_b - calculatedWeightB) <= 1.5) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    std::cout <<  "---TEST CASE 3---" << std::endl; ////0,206,114 for smaller dataset
    std::cout << "start: " << g.airports[4].airport_name << ", end: " <<g.airports[928].airport_name << '\n';
    double shortestPathTest1_c = g.getShortestPath(g.airports[4].airport_id, g.airports[928].airport_id);

    startVertex = g.idToAirport(g.airports[4].airport_id);
    double calculatedWeightC = startVertex.calculateWeight(g.idToAirport(g.airports[2045].airport_id));
    Vertex midVertex =  g.idToAirport(g.airports[2045].airport_id);
    calculatedWeightC += midVertex.calculateWeight(g.idToAirport(g.airports[928].airport_id));
    std::cout << "dist from 0 to 928: " << calculatedWeightC << " ; shortest Path output: "  << shortestPathTest1_c<< '\n';

    if(std::abs(shortestPathTest1_c - calculatedWeightC) <= 1.5) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    std::cout << "\n \n" << "------BFS------" << std::endl;

    //working test case
    // Ciudad del Carmen International Airport - 805
    // "Osh Airport" - 1378
    std::cout <<  "---TEST CASE 1---" << std::endl;
    std::vector<Vertex> path1 = g.BFSTraversal(0); //takes in index
    bool found = false; 
    for(Vertex a : path1) {
        if(a.airport_id == 3726) {
            found = true; 
        }
    }
    if(!found) { //bc 3726 (id) is not in the connected component
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    std::cout <<  "---TEST CASE 2---" << std::endl; //
    std::vector<Vertex> path2 = g.BFSTraversal(345); //takes in index
    found = false; 
    for(Vertex a : path2) {
        if(a.airport_id == 1378) {
            found = true; 
        }
    }
    if(found) { //bc 1378 (id) is in the connected component
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    std::cout <<  "---TEST CASE 3---" << std::endl; // 0, 3423
    std::vector<Vertex> path3 = g.BFSTraversal(g.idToIndex(1291)); //takes in index
    found = false; 
    for(Vertex a : path3) {
        if(a.airport_id == 1330) {
            found = true; 
        }
    }
    if(found) { //bc 1330 (id) is in the connected component
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    std::cout <<  "---TEST CASE 4---" << std::endl; // 0, 3423
    std::vector<Vertex> path4 =  g.BFSTraversal(100);
    if(path4.size() == 3152) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }


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