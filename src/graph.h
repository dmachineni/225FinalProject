#pragma once

#include "vertex.h"

#include <vector>
#include <string>
class Graph {
    public:
    Graph();
    private:
    void createAirports(std::string filename);
    std::vector<Vertex> airports;
};