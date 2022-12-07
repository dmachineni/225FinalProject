#include "vertex.h"
#include <cmath>

// default constructor
Vertex::Vertex() {
    airport_id = -1;
    airport_name = "";
    airport_lat = -1;
    airport_long = -1;
}

// construct new Vertex given parameters
Vertex::Vertex(std::string id, std::string name, long longitude, long latitude) {
    airport_id = id;
    airport_name = name;
    airport_lat = latitude;
    airport_long = longitude;
}

bool Vertex::same(Vertex other) {
    if (airport_id == other.airport_id && airport_name == other.airport_name && airport_lat == other.airport_lat && airport_long == other.airport_long) return true;
    return false;
}

long Vertex::calculateWeight(Vertex other) {
    long x = (airport_long - other.airport_long) * (airport_long - other.airport_long);
    long y = (airport_lat - other.airport_lat) * (airport_lat - other.airport_lat);
    return sqrt(x + y);
}