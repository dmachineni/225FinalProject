#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

Graph::Graph() {
    createAirports("airports.dat");
}
   
void Graph::createAirports(std::string filename) {
    std::ifstream airportFile(filename);
        //if not open throw an exception
    if(!airportFile.is_open()) std::cout << "File not open";
        
    std::string line;
    
            //file parsing
    std::stringstream ss(line);
    std::string skip;
    std::string ID, fname, lname, country, iata, icao;
    std::string number1, number2, number3;
    std::getline(ss, ID, ',');
    std::getline(std::getline(ss, skip, '"'), fname, '"');
    std::getline(ss, lname, ',');
    std::getline(std::getline(ss, skip, '"'), lname, '"');
    std::getline(ss, country, ',');
    std::getline(std::getline(ss, skip, '"'), country, '"');
            std::getline(ss, iata, ',');
            std::getline(std::getline(ss, skip, '"'), iata, '"');
            std::getline(ss, icao, ',');
            std::getline(std::getline(ss, skip, '"'), icao, '"');
            std::getline(ss, number1, ',');
            std::getline(ss, number2, ',');
            std::getline(ss, number3, ',');
            //vector fields
            Vertex newAirport(std::stoi(ID),fname,country, iata,icao,stod(number2),stod(number3));
            airports.at(newAirport.airport_id) = newAirport;
}

