#pragma once
#include <string>
#include <vector>
class Vertex {
    public:
    Vertex();
    Vertex(int id, std::string name, std::string country, double longitude, double latitude);
    
    int airport_id;
    std::string airport_name;
    std::string airport_country;
    double airport_long = 0;
    double airport_lat = 0;
    
    bool same(Vertex other);
    double calculateWeight(Vertex other);
};