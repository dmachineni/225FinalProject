#pragma once
#include <string>
#include <vector>
class Vertex {
    public:
    Vertex();
    Vertex(std::string id, std::string name);
    
    std::string airport_id;
    std::string airport_name;

    
    bool same(Vertex other);
    
};