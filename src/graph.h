#pragma once

#include "vertex.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>
class Graph {
    public:
        Graph();
    private:
        void createAirports(std::string filename);
        void createAdjacency(std::string filename);
        std::vector<Vertex> airports;
        std::map<std::string, std::vector<std::string>> adjacency_list;
};