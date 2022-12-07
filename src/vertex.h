#pragma once
#include <string>
#include <vector>
class Vertex {
    public:
    Vertex();
    Vertex(std::string id, std::string name, long longitude, long latitude);
    
    std::string airport_id;
    std::string airport_name;
    long airport_long = 0;
    long airport_lat = 0;
    
    bool same(Vertex other);
    long calculateWeight(Vertex other);
};