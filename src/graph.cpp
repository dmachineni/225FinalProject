#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Graph::Graph() {
    createAirports("/workspaces/VS CODE 225/225FinalProject/src/airports.dat");
    createAdjacency("routes.dat");
}
   
void Graph::createAirports(std::string filename) {
    std::ifstream airportFile(filename);
        //if not open throw an exception
    if(!airportFile.is_open()) std::cout << "File not open";

    std::string line;
    std::ifstream wordsFile(filename);
    
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, line)) {
            int comma = line.find(',');
            std::string id = line.substr(0, comma);
            int curr = comma + 2;
            std::string name;
            while (line[curr] != '"') {
                name += line[curr];
                curr++;
            }
            Vertex newAirport(id, name);
            std::vector<std::string> adj;
            adjacency_list.insert({newAirport.airport_name, adj});
            airports.push_back(newAirport);
        }
    }
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

int Graph::getadjacency_list() { return adjacency_list.size(); }
int Graph::getAirports() { return airports.size(); }
std::string Graph::getAirport(int idx) {
    return airports[idx].airport_name + " " + airports[idx].airport_id;
}