#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Graph::Graph() {
    createAirports("src/airports.dat");
    createAdjacencyList("src/routes.dat");
    clean();
    for (size_t i = 0; i < 3200; i++) {
      distances[i] = new long[3200];
   }
    createAdjacencyMatrix();
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
            std::string name = temp[1]; // name of airport
            std::string id = temp[0]; // id of airport
            long lat; // latitude of airport
            long longt; // longitude of airport

            // some names have multiple commas in them so we included a try/catch block to account for that
            try {
                lat = std::stoi(temp[6]);
                longt = std::stoi(temp[7]);
            } catch (std::invalid_argument) {
                lat = std::stoi(temp[7]);
                longt = std::stoi(temp[8]);
            }
            
            Vertex newAirport(id, name, longt, lat); 
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
void Graph::createAdjacencyList(std::string filename) {
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

void Graph::createAdjacencyMatrix() {
    long max_dist = 100000;
    
    for (auto list : adjacency_list) {
        std::string s = list.first;
        //distances[idToIndex(s)][idToIndex(s)] = 0;
        for (std::string t : list.second) {
            distances[idToIndex(s)][idToIndex(t)] = idToAirport(s).calculateWeight(idToAirport(t));
            //distances[idToIndex(t)][idToIndex(s)] = idToAirport(t).calculateWeight(idToAirport(s));
        }
    }
    for (int i = 0; i < 3200; i++) {
        for (int j = 0; j < 3200; j++) {
            if (distances[i][j] == 0 && i != j) distances[i][j] = max_dist;
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
    int deleted = 0;
    for (auto adj : adjacency_list) {
        if (adj.second.size() > 0) {
            tmp_adj.insert(adj);
            deleted++;
        }
    }
    for (auto v : airports) {
        if(tmp_adj.count(v.airport_id) != 0) {
            tmp_aps.push_back(v);
        }
    }
    if (deleted != 0) {
        airports = tmp_aps;
        adjacency_list = tmp_adj;
        std::cout << "Deleted: " << deleted << std::endl;
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
    if (idx > airportsSize()) return "Not valid index";
    Vertex v = airports[idx];
    return v.airport_name + " " + v.airport_id;
}

/*
    Returns adjacency list of aiport at given index
*/
std::string Graph::getAdjList(int idx) {
    if (idx > airportsSize()) return "Not valid index"; 
    std::string list;
    Vertex v = airports[idx];
    std::cout << "start id: " + v.airport_id << std::endl;
    std::vector<std::string> rr = adjacency_list.at(v.airport_id);
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

int Graph::idToIndex(std::string id) {
    for (int i = 0; i < airportsSize(); i++) {
        if (airports[i].airport_id == id) return i;
    }
    return -1;
}

/*
    BFS traversal of graph. Some airports are only connected to one other airport (two vertices and one edge)
    so they aren't included in the path. 
*/
std::vector<Vertex> Graph::BFSTraversal(int start) {
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
    // std::cout << "Unconnected airports: " << missing << std::endl;
    return path;
}

std::vector<Vertex> Graph::BFSSearch(std::string start, std::string end) {
    std::queue<Vertex> q;
    std::vector<Vertex> path;
    std::map<std::string, bool> visited;
    for (Vertex v : airports) visited.insert({v.airport_id, false});
    visited.insert({start, true});
    q.push(idToAirport(start));
 
    while(!q.empty()) {
        // Dequeue a vertex from queue and print it
        Vertex top = q.front();
        q.pop();
        path.push_back(top);
        if (path.back().airport_id == end) break;
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
    // int missing = -1;
    // // missing some airports because they're only connected to one other airport
    // for (auto pair : visited) {
    //     if (pair.second == false) missing++;
    // }
    // std::cout << "Unconnected airports: " << missing << std::endl;
    return path;
}

void Graph::floydWarshall() {
    long max_dist = 100000;
    for (int w = 0; w < airportsSize(); w++) {
        for (int u = 0; u < airportsSize(); u++) {
            for (int v = 0; v < airportsSize(); v++) {
                if (distances[u][v] > distances[u][w] + distances[w][v]) { //&& distances[u][w] != max_dist && distances[w][v] != max_dist) {
                    distances[u][v] = distances[u][w] + distances[w][v];
                }
            }
        }
    }
}

// think i fixed it but its kinda slow...
// want to see if there's a way to create the adjacency matrix beforehand but it creates some problems
// find the shortest path between two airports, start and end
int Graph::getShortestPath(std::string start, std::string end) {
    std::cout << "start " << start << std::endl;
    floydWarshall();
    //std::vector<std::string> adj = adjacency_list.at(start);
    //static int distances[4000][4000]; //2d array of distance from adjacent vertex to end
    //distance from start to end = 1 + number from distances
    // initialize adjacency matrix. each item is the distance between the airports at those indices
    
    
    //populate adjacency matrix
    //find path for each adjacent vertex
    //count distance from adjacent vertex to end
    // for (std::string s : adj) {//go through the adjacency list. find distance for each path that starts with each adjacent vertex
    //     std::vector<Vertex> path = BFSSearch(s, end); //get all the airports that vertex is connected to
    //     // std::cout << "path size " << path.size() << std::endl;
    //     //find distance from vertex to end
        
    //     //int d = idToAirport(s).calculateWeight(idToAirport(end));
    //     for (Vertex v : path) {
    //         distances[idToIndex(s)][idToIndex(v.airport_id)] = idToAirport(s).calculateWeight(idToAirport(v.airport_id));
    //         distances[idToIndex(v.airport_id)][idToIndex(s)] = idToAirport(s).calculateWeight(idToAirport(v.airport_id));
    //     }

    // }
    
    
    // std::cout << "start " << start << " end " << end << std::endl;
    // std::cout << "result " << distances[std::stoi(start)][std::stoi(end)] << std::endl;

    return distances[idToIndex(start)][idToIndex(end)];
}