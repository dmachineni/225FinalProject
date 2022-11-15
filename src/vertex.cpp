#include "vertex.h"


// default constructor
Vertex::Vertex() {
    airport_id = -1;
    airport_name = "";
    location = "";
    // IATA_code = "";
    // ICAO_code = "";
    longitude = 0.0;
    latitude = 0.0;

}

// construct new Vertex given parameters
Vertex::Vertex(int id, std::string name, std::string loc, std::string IATA, std::string ICAO, double lat, double longt) {
    airport_id = id;
    airport_name = name;
    location = loc;
    // IATA_code = IATA;
    // ICAO_code = ICAO;
    longitude = longt;
    latitude = lat;
}