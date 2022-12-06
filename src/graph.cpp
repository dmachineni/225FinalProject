#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Graph::Graph() {
    createAirports("src/airports.dat");
    createAdjacency("src/routes.dat");
    clean();
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
                if (adjacency_list.count(source) != 0 && adjacency_list.count(dest) != 0) { // ignore if source isn't in map because it's not in aiports either
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
    This function cleans airports and adjacency list by removing airports that aren't in routes.dat.
    If an airport's adjacency list is empty, then there are no routes to/from that airport. This means that it's not 
    connected to the other airports and can be removed for
*/
void Graph::clean() {
    std::map<std::string, std::vector<std::string>> tmp_adj;
    std::vector<Vertex> tmp_aps;
    int deleted = adjacency_list.size();
    for (auto adj : adjacency_list) {
        if (adj.second.size() > 0) {
            //std::cout << adj.first << " connected to " << adj.second.size() << std::endl;
            tmp_adj.insert(adj);
            deleted--;
        }
    }
    for (auto v : airports) {
        if(tmp_adj.count(v.airport_id) != 0) {
            tmp_aps.push_back(v);
        }
    }
    std::cout << "Deleted: " << deleted << std::endl;
    airports = tmp_aps;
    adjacency_list = tmp_adj;
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
    if (adjacency_list.count(std::to_string(idx)) == 0) return "Not valid index";
    Vertex v = idToAirport(std::to_string(idx));
    return v.airport_name + " " + v.airport_id;
}

/*
    Returns adjacency list of aiport at given index
*/
std::string Graph::getAdjList(int idx) {
    if (adjacency_list.count(std::to_string(idx)) == 0) return "Not valid index"; 
    std::string list;
    std::vector<std::string> rr = adjacency_list.at(std::to_string(idx));
    for (std::string ap : rr) {
        list += ap + ", ";
    }
    return list;
}

/*
    Returns the Vertex (airport) with that id
*/
Vertex Graph::idToAirport(std::string id) {
    for (Vertex v : airports) {
        if (v.airport_id == id) return v;
    }
    return Vertex();
}

/*
    BFS traversal of graph. Some airports are only connected to one other airport (two vertices and one edge)
    so they aren't included in the path. 
*/
std::vector<Vertex> Graph::BFS(int start) {
    std::queue<Vertex> q;
    std::vector<Vertex> path;
    std::map<std::string, bool> visited;
    for (Vertex v : airports) visited.insert({v.airport_id, false});
    visited.insert({airports[start].airport_id, true});
    q.push(airports[start]);
 
    while(!q.empty()) {
        // Dequeue a vertex from queue and print it
        Vertex top = q.front();
        q.pop();
        path.push_back(top);

        std::vector<std::string> adj = adjacency_list[top.airport_id];
        // Get all adjacent vertices of the dequeued vertex. 
        // If a adjacent has not been visited, then mark it visited and enqueue it
        for (auto neighbor: adj) {
            if (visited.count(neighbor) != 0 && visited.at(neighbor) == false) {
                visited.at(neighbor) = true;
                q.push(idToAirport(neighbor));
            }
        }
    }
    int missing = -1;
    // missing some airports because they're only connected to one other airport
    for (auto pair : visited) {
        if (pair.second == false) missing++;
    }
    std::cout << "Unconnected airports: " << missing << std::endl;
    return path;
}