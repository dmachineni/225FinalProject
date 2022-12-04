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
        int airportsSize(); // returns size of airports, should match number in file (7698?)
        int adjlistSize(); // returns size of adjacency list map, should also match size of airports
        std::string getAirport(int idx); // returns airport at that index
        std::string getAdjList(int idx); // returns adjacency list of airport at that index, returns their ids 
        // may need to change how we implement this because if we return ids, then we have to search airports and check each
        // vertex's id to see if we get a match. maybe we create an adjacency list of vertices instead of strings??
        std::vector<Vertex> BFS(int start);
        void clean();
        int getShortestPath(std::string start, std::string end);
        std::vector<Vertex> airports; // vector of airports
    private:
        void createAirports(std::string filename);
        void createAdjacency(std::string filename);
        // std::vector<Vertex> airports; // vector of airports
        std::map<std::string, std::vector<std::string>> adjacency_list; // collection of all adjacency lists
        Vertex idToAirport(std::string id);
};