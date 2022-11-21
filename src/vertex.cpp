#include "vertex.h"


// default constructor
Vertex::Vertex() {
    airport_id = -1;
    airport_name = "";
}

// construct new Vertex given parameters
Vertex::Vertex(std::string id, std::string name) {
    airport_id = id;
    airport_name = name;
}