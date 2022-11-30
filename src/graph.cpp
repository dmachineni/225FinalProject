#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Graph::Graph() {
    createAirports("src/airports.dat");
    createAdjacency("src/routes.dat");
}


/*
    This function creates airport Vertices from "airport.dat". When every airport is created,
    it is pushed to adjacency_list.
*/
void Graph::createAirports(std::string filename) {
    std::ifstream airportFile(filename);
    if(!airportFile.is_open()) std::cout << "File not open";

    std::string line;
    std::ifstream wordsFile(filename);
    
    if (wordsFile.is_open()) {
        while (getline(wordsFile, line)) {
            int comma = line.find(',');
            std::string id = line.substr(0, comma); // first entry in file is airport id
            int curr = comma + 2; // skips over comma and "
            std::string name;
            // second entry in file is airport name, 
            // loops through until comma is found (end of entry)
            while (line[curr] != '"') { 
                name += line[curr];
                curr++;
            }
            Vertex newAirport(id, name); 
            std::vector<std::string> adj;
            adjacency_list.insert({newAirport.airport_id, adj});
            airports.push_back(newAirport);
        }
    }
}
/*
    This function populates adjacency_list using "routes.dat". Destination airports are
    pushed to the source's adjacency list. Null values and airports that aren't in airports are
    skipped.
*/
void Graph::createAdjacency(std::string filename) {
    std::string line;
    std::ifstream wordsFile(filename);
    
    if (wordsFile.is_open()) {
        while (getline(wordsFile, line)) {
            std::vector<std::string> temp;
            std::string word = "";
            // breaks up line into entries, stores entries in temp
            for (size_t i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    temp.push_back(word);
                    word = "";
                } else {
                    word += line[i];
                }
            }
            std::string source = temp[3]; // id of source airport
            std::string dest = temp[5]; // id of destination airport
            
            if (temp[3] != "\\N" && temp[5] != "\\N") { // skips over null values (\N)
                if (adjacency_list.count(source) != 0) { // ignore if source isn't in map because it's not in aiports either
                    std::vector<std::string> list = adjacency_list[source];
                    if (std::find(list.begin(), list.end(), dest) == list.end()) {
                        adjacency_list.at(source).push_back(dest);
                    }
                }
            }
            
        }
    }

}

/*
    Returns size of adjacency_list
*/
int Graph::adjlistSize() { return adjacency_list.size(); }

/*
    Returns size of airports
*/
int Graph::airportsSize() { return airports.size(); }

/*
    Returns airport at given index
*/
std::string Graph::getAirport(int idx) {
    return airports[idx].airport_name + " " + airports[idx].airport_id;
}

/*
    Returns adjacency list of aiport at given index
*/
std::string Graph::getAdjList(int idx) { 
    std::string list;
    std::vector<std::string> rr = adjacency_list.at(airports[idx].airport_id);
    std::cout << airports[idx].airport_id << std::endl;
    for (std::string ap : rr) {
        list += ap + ", ";
    }
    return list;
}