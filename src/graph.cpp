#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Graph::Graph() {
    createAirports("airports.dat");
}
   
void Graph::createAirports(std::string filename) {
    std::ifstream airportFile(filename);
        //if not open throw an exception
    if(!airportFile.is_open()) std::cout << "File not open";
        
    // std::string line;
    // //file parsing
    // std::stringstream ss(line);
    // std::string skip;
    // std::string ID, fname, lname, country, iata, icao;
    // std::string number1, number2, number3;
    // std::getline(ss, ID, ',');
    // std::getline(std::getline(ss, skip, '"'), fname, '"');
    // std::getline(ss, lname, ',');
    // std::getline(std::getline(ss, skip, '"'), lname, '"');
    // std::getline(ss, country, ',');
    // std::getline(std::getline(ss, skip, '"'), country, '"');
    // std::getline(ss, iata, ',');
    // std::getline(std::getline(ss, skip, '"'), iata, '"');
    // std::getline(ss, icao, ',');
    // std::getline(std::getline(ss, skip, '"'), icao, '"');
    // std::getline(ss, number1, ',');
    // std::getline(ss, number2, ',');
    // std::getline(ss, number3, ',');

    std::string line;
    std::ifstream wordsFile(filename);
    
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, line)) {
            auto comma = std::find(begin(line), end(line), ',');
            std::string id = line.substr(0, comma);
            std::string name = line.substr(id.length(), std::find(','));
            Vertex newAirport(id,name);
            std::vector<std::string> adj;
            adjacency_list.insert({newAirport.airport_name, adj});
            // airports.push_back(newAirport);
        }
    }

    

    //vector fields
    // Vertex newAirport(std::stoi(ID),fname,country, iata,icao,stod(number2),stod(number3));
    // airports.at(newAirport.airport_id) = newAirport;
}

void Graph::createAdjacency(std::string filename) {
    std::string line;
    std::ifstream wordsFile(filename);
    
    if (wordsFile.is_open()) {
        while (getline(wordsFile, line)) {
            std::vector<std::string> temp;
            std::string word = "";
            for (size_t i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    temp.push_back(word);
                    word = "";
                } else {
                    word += line[i];
                }
            }
            std::string source = temp[3];
            std::string dest = temp[5];
            std::vector<std::string> list = adjacency_list[source];
            if (std::find(list.begin(), list.end(), dest) == list.end()) {
                // doesn't already contains it
                adjacency_list.at(source).push_back(dest);
            }
            
            
        }
    }

}


