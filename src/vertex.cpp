#include "vertex.h"
#include <cmath>

// default constructor
Vertex::Vertex() {
    airport_id = -1;
    airport_name = "";
    airport_country = "";
    airport_lat = -1;
    airport_long = -1;
}

// construct new Vertex given parameters
Vertex::Vertex(int id, std::string name, std::string country, double longitude, double latitude) {
    airport_id = id;
    airport_name = name;
    airport_country = country;
    airport_lat = latitude;
    airport_long = longitude;
}

/*
    Checks if two vertices are the same.
*/
bool Vertex::same(Vertex other) {
    if (airport_id == other.airport_id && airport_name == other.airport_name && airport_lat == other.airport_lat && airport_long == other.airport_long) return true;
    return false;
}

/*
    Uses haversine distance formula to figure out distance in km between two airports.
*/
double Vertex::calculateWeight(Vertex other) {
    //calculating latitude and longitude
    double dLat = (other.airport_lat - airport_lat) * M_PI / 180.0;
    double dLon = (other.airport_long - airport_long) * M_PI / 180.0;
 
    // convert to radians
    double lat1_rad = (airport_lat) * M_PI / 180.0;
    double lat2_rad = (other.airport_lat) * M_PI / 180.0;
 
    // apply formulae
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1_rad) * cos(lat2_rad);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}