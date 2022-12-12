#include "graph.h"
#include "vertex.h"
#include <iostream>
#include <string>

int main() {
    // Constructs new Graph object
    // Changing boolean value to true, builds a large dataset
    // Changing boolean value to false, creates a condensed version of dataset that is only one airport per country
    Graph g(true); 



    //For all test cases, TRUE means the test case passed.



    // TEST CASES FOR BFS ALGORITHM
    std::cout << "\n \n" << "------BFS------" << std::endl;

    // Checks if an airport that isn’t in the start node’s connected component does not exist in the path returned by the BFS traversal
    std::cout <<  "---TEST CASE 1---" << std::endl;
    std::vector<Vertex> path1 = g.BFSTraversal(0);
    bool found = false; 
    for(Vertex a : path1) {
        if(a.airport_id == 3726) {
            found = true; 
        }
    }
    if(!found) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    // Checks if an airport that is within the start node’s connected component exists in the path returned by the BFS traversal
    std::cout <<  "---TEST CASE 2---" << std::endl;
    std::vector<Vertex> path2 = g.BFSTraversal(2400); 
    found = false; 
    for(Vertex a : path2) {
        if(a.airport_id == 1353) {
            found = true; 
        }
    }
    if(found) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    // Checks if an airport that is within the start node’s connected component exists in the path returned by the BFS traversal
    std::cout <<  "---TEST CASE 3---" << std::endl;
    std::vector<Vertex> path3 = g.BFSTraversal(83);
    found = false; 
    for(Vertex a : path3) {
        if(a.airport_id == 1330) {
            found = true; 
        }
    }
    if(found) { 
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    // Checks that the connected component contains the correct number of connected nodes
    std::cout <<  "---TEST CASE 4---" << std::endl; // 0, 3423
    std::vector<Vertex> path4 =  g.BFSTraversal(100);
    if(path4.size() == 3152) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }





    //SHORTEST PATH TEST CASES
    std::cout << "\n \n" << "------SHORTEST PATH------" << std::endl;
    // Checks shortest path of node to itself
    // Should return 0.
    std::cout <<  "---TEST CASE 1---" << std::endl; //0 for smaller dataset
    std::cout << "start: " << g.airports[4].airport_name << ", end: " << g.airports[4].airport_name << '\n';
    double shortestPathTest1_a = g.getShortestPath(g.airports[4].airport_id, g.airports[4].airport_id);
    if(shortestPathTest1_a == 0) {
        std::cout << "TRUE" << std::endl;
    } else {
        std::cout << "FALSE" << std::endl;
    }

    // Checks shortest path of adjacent nodes.
    std::cout <<  "---TEST CASE 2---" << std::endl;
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

    // Checks shortest path of two randomly chosen nodes. 
    std::cout <<  "---TEST CASE 3---" << std::endl; 
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




    // TEST CASES FOR LANDMARK PATH
    std::cout << "\n \n" << "------LANDMARK PATH------" << std::endl;

    // Tests landmark function with only one midpoint
    std::cout << "\n ---TEST CASE 1---" << std::endl;
    std::cout << "start: " << g.airports[0].airport_name << ", mid: " << g.airports[g.idToIndex(4074)].airport_name << ", end: " <<g.airports[114].airport_name << '\n';
    double x = g.getShortestPath(g.airports[0].airport_id, 4074);
    std::cout << "start to mid: " << x << "km" << std::endl;
    double y = g.getShortestPath(4074, g.airports[114].airport_id);
    std::cout << "mid to end: " << y << "km"  << std::endl;
    double total1 = g.landmarkPath(g.airports[0].airport_id, 4074, g.airports[114].airport_id); 
    std::cout << "Landmark Path distance: " << x << " + " << y << " = "  << total1 << std::endl;
    if (total1 == x + y) {
        std::cout << "TRUE" << std::endl;
    } else { std::cout << "FALSE" << std::endl; }

    // Tests landmark function with vector of size 1
    std::cout <<  "---TEST CASE 2---" << std::endl;
    std::cout << "start: " << g.airports[0].airport_name << ", mid: " << g.airports[g.idToIndex(1960)].airport_name << ", end: " <<g.airports[114].airport_name << '\n';
    double c = g.getShortestPath(g.airports[0].airport_id, 1960);
    std::cout << "start to mid: " << c << "km" << std::endl;
    double d = g.getShortestPath(1960, g.airports[114].airport_id);
    std::cout << "mid to end: " << d << "km" << std::endl;
    std::vector<int> vec;
    vec.push_back(1960);
    double total2 = g.landmarkPath(g.airports[0].airport_id, vec, g.airports[114].airport_id); 
    std::cout << "Landmark Path distance: " << c << " + " << d << " = " << total2 << std::endl;
    if (total2 == c + d) {
        std::cout << "TRUE" << std::endl;
    } else { std::cout << "FALSE" << std::endl; }

    // Tests landmark function with vector of size 2
    std::cout <<  "---TEST CASE 3---" << std::endl;
    std::cout << "start: " << g.airports[4].airport_name << ", mid: " << g.airports[5].airport_name << ", " << g.airports[6].airport_name << ", end: " <<g.airports[7].airport_name << '\n';
    double l = g.getShortestPath(g.airports[4].airport_id, g.airports[5].airport_id);
    std::cout << "start to mid1: " << l << "km" << std::endl;
    double m = g.getShortestPath(g.airports[5].airport_id, g.airports[6].airport_id);
    std::cout << "mid1 to mid2: " << m << "km" << std::endl;
    double n = g.getShortestPath(g.airports[6].airport_id, g.airports[7].airport_id);
    std::cout << "mid2 to end: " << n << "km" << std::endl;
    std::vector<int> vec2;
    vec2.push_back(g.airports[5].airport_id);
    vec2.push_back(g.airports[6].airport_id);
    double total3 = g.landmarkPath(g.airports[4].airport_id, vec2, g.airports[7].airport_id); 
    std::cout << "Landmark Path distance: " << l << " + " << m << " + " << n << " = " << total3 << std::endl;
    if (total3 == l + m + n) {
        std::cout << "TRUE" << std::endl;
    } else { std::cout << "FALSE" << std::endl; }

    // Tests landmark function with vector of size 3
    std::cout <<  "---TEST CASE 4---" << std::endl;
    std::cout << "start: " << g.airports[2].airport_name << ", mid: " << g.airports[66].airport_name << ", " << g.airports[73].airport_name << ", " << g.airports[92].airport_name << ", end: " <<g.airports[123].airport_name << '\n';
    double e = g.getShortestPath(g.airports[2].airport_id, g.airports[66].airport_id);
    std::cout << "start to mid1: " << e << "km" << std::endl;
    double j = g.getShortestPath(g.airports[66].airport_id, g.airports[73].airport_id);
    std::cout << "mid1 to mid2: " << j << "km" << std::endl;
    double h = g.getShortestPath(g.airports[73].airport_id, g.airports[92].airport_id);
    std::cout << "mid2 to mid3: " << h << "km" << std::endl;
    double f = g.getShortestPath(g.airports[92].airport_id, g.airports[123].airport_id);
    std::cout << "mid3 to end: " << f << "km" << std::endl;
    std::vector<int> vec1;
    vec1.push_back(g.airports[66].airport_id);
    vec1.push_back(g.airports[73].airport_id);
    vec1.push_back(g.airports[92].airport_id);
    double total4 = g.landmarkPath(g.airports[2].airport_id, vec1, g.airports[123].airport_id); 
    std::cout << "Landmark Path distance: " << e << " + " << j << " + " << h << " + " << f << " = " << total4 << std::endl;
    if (total4 == e + h + j + f) {
        std::cout << "TRUE" << std::endl;
    } else { std::cout << "FALSE" << std::endl; }
}