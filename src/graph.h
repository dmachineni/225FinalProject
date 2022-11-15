#pragma once

#include "vertex.h"

#include <vector>
#include <string>
#include <map>
class Graph {
    public:
        Graph();
    private:
        void createAirports(std::string filename);
        std::vector<Vertex> airports;
        std::map<std::string, std::vector<std::string>> adjacency_list;
};