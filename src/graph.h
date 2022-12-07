#pragma once

#include "vertex.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>
#include <limits>
class Graph {
    public:
        Graph();
        Graph(std::string airports_file, std::string adj_list_file, std::string adj_matrix_file); // creates graph from adjacency list and matrix files, saves time

        int airportsSize(); // returns size of airports, should match number in file (7698?)
        int adjlistSize(); // returns size of adjacency list map, should also match size of airports

        std::string getAirport(int idx); // returns airport at that index
        std::string getAdjList(int idx); // returns adjacency list of airport at that index, returns their ids 
        
        std::vector<Vertex> BFSTraversal(int start); // BFS traversal of connected components

        // writes to files so we don't have to keep calling it
        void writeAirportsToFile(std::string filename);
        void writeAdjListToFile(std::string filename); 
        void writeDistMatrixToFile(std::string filename);
        
        int idToIndex(int id); // returns index with id
        double getShortestPath(int start, int end); // returns distance in km between both airports
        std::vector<Vertex> airports; // vector of airports
        

        private:
        // creates from files from scratch
        void createAirports(std::string filename);
        void createAdjacencyList(std::string filename);
        void createDistMatrix();
        void clean(); // removes airports that aren't in both airports.dat and routes.dat
        
        // read from files so we don't have to keep recreating it
        void readAirportsFromFile(std::string filename);
        void readAdjListFromFile(std::string filename);        
        void readDistMatrixFromFile(std::string filename);
    
        void floydWarshall();
        std::map<int, std::vector<int>> adjacency_list; // collection of all adjacency lists
        Vertex idToAirport(int id); // returns index with id

        std::vector<std::vector<double>> distances; // matrix with distances as values
        std::map<std::string, std::vector<int>> countries; // keeps track of all the airports in each country, used in clean()
   
        
};