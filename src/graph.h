#pragma once

#include "vertex.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>
class Graph {
    public:
        Graph();
        int airportsSize(); 
        int adjlistSize();
        std::string getAdjList(int idx); // returns adjacency list of airport at that index, returns their ids 
        // may need to change how we implement this because if we return ids, then we have to search airports and check each
        // vertex's id to see if we get a match. maybe we create an adjacency list of vertices instead of strings??
    private:
        void createAirports(std::string filename);
        void createAdjacency(std::string filename);
        std::vector<Vertex> airports; // vector of airports
        std::map<std::string, std::vector<std::string>> adjacency_list; // collection of all adjacency listst
};