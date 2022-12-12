#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ostream>
#include <iterator>

/*
    Default constructor. If true, then using  all airports. If false, only using most connected
    from each country. 
*/
Graph::Graph(bool all_airports) {
    createAirports("src/airports.dat");
    createAdjacencyList("src/routes.dat");
    // distances.resize(220) if sorting by country (recommended because it literally corrups)
    distances.resize(airportsSize());
    for (unsigned i = 0; i < distances.size(); i++) distances[i].resize(airportsSize());
    for (int i = 0; i < airportsSize(); i++) {
        for (int j = 0; j < airportsSize(); j++) {
            distances[i][j] = INT16_MAX;
        }
    }
    if (all_airports) cleanToLarge();
    else cleanToSmall();
    std::cout << "26" << '\n';
    createDistMatrix();
    std::cout << "28" << '\n';
    floydWarshall();
}

/*
    Constructor that creates airports, adjacency list, and distance matrix from files rather than creating from scratch.
    Saves times.
*/
Graph::Graph(std::string airports_file, std::string adj_list_file, std::string adj_matrix_file) {
    readAirportsFromFile(airports_file);
    readAdjListFromFile(adj_list_file);
    readDistMatrixFromFile(adj_matrix_file); // graph already has floyd warshall values, don't need to call again
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
            int id = std::stoi(temp[0]); // id of airport
            std::string country;
            double lat; // latitude of airport
            double longt; // longitude of airport

            // some names have multiple commas in them so we included a try/catch block to account for that
            try {
                country = temp[3];
                lat = std::stod(temp[6]);
                longt = std::stod(temp[7]);
            } catch (std::invalid_argument) {
                country = temp[4];
                lat = std::stod(temp[7]);
                longt = std::stod(temp[8]);
            }
            
            Vertex newAirport(id, name, country, longt, lat);  
            // keeps track of airports in each country, used in clean()
            if (countries.count(country) != 0) countries.at(country).push_back(id);
            else countries.insert({country, {id}});

            adjacency_list.insert({newAirport.airport_id, {}});
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
            if (temp[3] != "\\N" && temp[5] != "\\N") {
                int source = std::stoi(temp[3]); // id of source airport
                int dest = std::stoi(temp[5]); // id of destination airport
                if (adjacency_list.count(source) != 0 && adjacency_list.count(dest) != 0) { // ignore if source isn't in map because it's not in aiports either
                    std::vector<int> list = adjacency_list[source];
                    if (std::find(list.begin(), list.end(), dest) == list.end()) {
                        adjacency_list.at(source).push_back(dest);
                    }
                }
            }   
        }
    }

}
/*
    Creates adjacency matrix with distances as weights.
*/
void Graph::createDistMatrix() {
    for (auto list : adjacency_list) {
        int s= list.first;
        distances[idToIndex(s)][idToIndex(s)] = 0;
        for (int t : list.second) {
            int dist = idToAirport(s).calculateWeight(idToAirport(t));
            distances[idToIndex(s)][idToIndex(t)] = dist;
        }
    }
}

/*
    This function cleans airports and adjacency list by removing airports that aren't in routes.dat and only using the most connected
    airport in each country. If we didn't check for this, then the graph would be too large, take too long to run, and eventually crash.
    If an airport's adjacency list is empty, then there are no routes to/from that airport. This means that it's not 
    connected to the other airports and can be removed.
*/
void Graph::cleanToSmall() {
    std::map<int, std::vector<int>> tmp_adj;
    std::map<int, std::vector<int>> tmp_adj2;
    std::vector<Vertex> tmp_aps;
    // gets the largest/most connected airport from each country
    for (auto c : countries) {
        int most_routes = c.second[0];
        for (int s : c.second) {
            if (adjacency_list.at(s).size() > adjacency_list.at(most_routes).size()) most_routes = s;
        }
        
        tmp_adj.insert({most_routes, {}});
    }
    // removes airports from adjacency list if they're not in the updated list
    for (auto adj : adjacency_list) {
        if (tmp_adj.count(adj.first) != 0) {
            int s = adj.first;
            for (auto d : adj.second) {
                if (tmp_adj.count(d) != 0) {
                    tmp_adj.at(s).push_back(d);
                }
            }
        }
    }
    // only keeps airports that aren't connected to any other airport
    for (auto adj : tmp_adj) {
        if (adj.second.size() > 0) {
            tmp_adj2.insert(adj);
        }
    }
    // adds airports from updated adjacency list2
    for (auto v : airports) {
        if(tmp_adj2.count(v.airport_id) != 0) {
            tmp_aps.push_back(v);
        }
    }
    int deleted = airports.size() - tmp_adj.size();
    airports = tmp_aps;
    adjacency_list = tmp_adj2;
    // std::cout << "Deleted: " << deleted << std::endl;
}

void Graph::cleanToLarge() {
    std::map<int, std::vector<int>> tmp_adj;
    std::vector<Vertex> tmp_aps;
    
    // only keeps airports that aren't connected to any other airport
    for (auto adj : adjacency_list) {
        if (adj.second.size() > 0) {
            tmp_adj.insert(adj);
        }
    }
    // adds airports from updated adjacency list2
    for (auto v : airports) {
        if(tmp_adj.count(v.airport_id) != 0) {
            tmp_aps.push_back(v);
        }
    }
    int deleted = airports.size() - tmp_adj.size();
    airports = tmp_aps;
    adjacency_list = tmp_adj;
    // std::cout << "Deleted: " << deleted << std::endl;
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
    return v.airport_name + " " + std::to_string(v.airport_id);
}

/*
    Returns adjacency list of aiport at given index
*/
std::string Graph::getAdjList(int idx) {
    if (idx > airportsSize()) return "Not valid index"; 
    std::string list;
    Vertex v = airports[idx];
    std::vector<int> rr = adjacency_list.at(v.airport_id);
    for (int ap : rr) {
        list += std::to_string(ap) + ", ";
    }
    return list;
}

/*
    Returns the Vertex (airport) with that id
*/
Vertex Graph::idToAirport(int id) {
    for (Vertex v : airports) {
        if (v.airport_id == id) return v;
    }
    return Vertex();
}

int Graph::idToIndex(int id) {
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
    std::map<int, bool> visited;
    for (Vertex v : airports) visited.insert({v.airport_id, false});
    visited.insert({airports[start].airport_id, true});
    q.push(airports[start]);
 
    while(!q.empty()) {
        // Dequeue a vertex from queue and print it
        Vertex top = q.front();
        q.pop();
        path.push_back(top);

        std::vector<int> adj = adjacency_list[top.airport_id];
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


/*
    Floyd Warshall algorithm
*/
void Graph::floydWarshall() {
    for (int w = 0; w < airportsSize(); w++) {
        for (int u = 0; u < airportsSize(); u++) {
            for (int v = 0; v < airportsSize(); v++) {
                if (distances[u][v] > distances[u][w] + distances[w][v] && distances[u][w] != INT16_MAX && distances[w][v] != INT16_MAX) {
                    distances[u][v] = distances[u][w] + distances[w][v];
                }
            }
        }
    }
}
/*
    Returns value of distance[start][end] because it has the value of Floyd Warshall
*/
double Graph::getShortestPath(int start, int end) {
    return distances[idToIndex(start)][idToIndex(end)];
}
/*
    Writes airports to file for future use. Don't need to keep recreating it.
*/
void Graph::writeAirportsToFile(std::string filename) {
    std::ofstream stream(filename);
    for (Vertex v : airports) {
        stream << v.airport_id << "," << v.airport_name << "," << v.airport_country << "," << v.airport_lat << "," << v.airport_long;
        stream << "\n";
    }
    stream.close();
}
/*
    Creates airports from file
*/
void Graph::readAirportsFromFile(std::string filename) {
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
            temp.push_back(word);
            int id = std::stoi(temp[0]);
            std::string name = temp[1];
            std::string country = temp[2];
            double lat = std::stod(temp[3]);
            double longt = std::stod(temp[4]);
            Vertex v(id, name, country, longt, lat);
            airports.push_back(v);
        }
    }
}

/*
    Writes adjacency list to file for future use. Don't need to keep recreating it.
*/
void Graph::writeAdjListToFile(std::string filename) {
    std::ofstream stream(filename);
    for (auto a : adjacency_list) {
        std::vector<int> tmp = a.second;
        tmp.insert(tmp.begin(), a.first); // 0th col is source airport id
        for (unsigned i = 0; i < tmp.size(); i++) {
            stream << tmp[i];
            if (i != tmp.size() - 1) stream << ",";
        }
        stream << "\n";
    }
    stream.close();
}
/*
    Creates adjacency list from file.
*/
void Graph::readAdjListFromFile(std::string filename) {
    std::string line;
    std::ifstream wordsFile(filename);
    if (wordsFile.is_open()) {
        while (getline(wordsFile, line)) {
            std::vector<int> temp;
            std::string word = "";
            // breaks up line into entries, stores entries in temp
            for (size_t i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    temp.push_back(std::stoi(word));
                    word = "";
                } else {
                    word += line[i];
                }
            }
            temp.push_back(std::stoi(word));
            int start = temp[0]; // source airport
            temp.erase(temp.begin());
            adjacency_list.insert({start, temp});
        }
    }
}

/*
    Writes distance matrix to file for future use.
*/
void Graph::writeDistMatrixToFile(std::string filename) {
    std::ofstream stream(filename);
    for (unsigned i = 0; i < distances.size(); i++) {
        for (unsigned j = 0; j < distances.size(); j++) {
            stream << distances[i][j];
            if (j != distances.size() - 1) stream << ",";
        }
        stream << "\n";
    }
    stream.close();
}
/*
    Creates distance matrix from file. // NOT WORKING FULLY
*/
void Graph::readDistMatrixFromFile(std::string filename) {
    std::string line;
    std::ifstream wordsFile(filename);
    distances.resize(220);
    if (wordsFile.is_open()) {
        int s = 0;
        while (getline(wordsFile, line)) {
            std::vector<double> temp;
            std::string word = "";
            // breaks up line into entries, stores entries in temp
            for (size_t i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    temp.push_back(std::stod(word));
                    word = "";
                } else {
                    word += line[i];
                }
            }
            temp.push_back(std::stod(word));
            distances[s] = temp;
            s++;
        }
    }
}


//A* algo functions
double Graph::calculateHValues(int start, int dest) {
    Vertex startVertex = idToAirport(start);
    return startVertex.calculateWeight(idToAirport(dest));
}

double Graph::landmarkPath(int start, int mid, int end) {
    // if shortest path does not exist, return empty vector
    // double Graph::getShortestPath(int start, int end)
    double final_distance = 0;
    final_distance += getShortestPath(start, mid);
    final_distance += getShortestPath(mid, end);
    
    // confirm that shortest path will return 0 if there are no connections
    if (getShortestPath(start, mid) == 0 || getShortestPath(mid, end) == 0) {
        return 0;
    }

    return final_distance;
}

double Graph::landmarkPath(int start, std::vector<int> mid, int end) {
    // if shortest path does not exist between two points, return 0
    // double Graph::getShortestPath(int start, int end)
    double final_distance = 0;
    final_distance += getShortestPath(start, mid[0]);
    for (size_t i = 0; i < mid.size() - 1; i++) {
        if (getShortestPath(mid[i], mid[i+1]) == 0) {
            return 0;
        }
        final_distance += getShortestPath(mid[i], mid[i+1]);
    }
    final_distance += getShortestPath(mid[mid.size()-1], end);
    
    // confirm that shortest path will return 0 if there are no connections
    if (getShortestPath(start, mid[0]) == 0 || getShortestPath(mid[mid.size()-1], end) == 0) {
        return 0;
    }

    return final_distance;
}

