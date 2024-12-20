/*Anisha Hossain (U43189731), Alina Pineda (U79400432), Tanisha Dutta (U31690052), Brielle Ashmeade (U38424858) 
File description:
This source file (.cpp) implements an undirected weighted graph using adjacency lists. It includes basic operations for 
adding and removing vertices and edges, with the main feature being Dijkstra's shortest path algorithm. The graph is stored 
in an unordered map, where each vertex maintains its connections and edge weights. The shortestPath function uses a priority 
queue to efficiently find the shortest route between two points, while keeping track of distances and path reconstruction. 
Error handling is implemented throughout to manage invalid inputs and edge cases.
*/
#include "Graph.hpp"
#include "GraphBase.hpp"
#include "HeapQueue.hpp"


//Adds a new vertex to the graph with the given label
void Graph::addVertex(std::string label) {
    if (vertices.find(label) == vertices.end()) { //Checks if the vertex does not already exist before adding
        vertices[label] = Vertex{label};//Creates a new vertex and adds it to the map
    }
}

//Removes a vertex and all edges connected to it
void Graph::removeVertex(std::string label) {
    if (vertices.find(label) != vertices.end()) { // Check if the vertex exists
        for (auto& v : vertices) { //Remove the vertex from all adjacency lists of other vertices
            v.second.edges.erase(label);
        }
        vertices.erase(label); //Remove the vertex itself

    }
}

//Adds an edge with a specific weight between two vertices
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight) {
    // Ensure both vertices exist and the edge is not a self-loop
    if (vertices.find(label1) != vertices.end() && vertices.find(label2) != vertices.end() && label1 != label2) {
        //Add the edge in both directions for an undirected graph
        vertices[label1].edges[label2] = weight;
        vertices[label2].edges[label1] = weight; // Undirected graph
    }
}

//Removes the edge between two vertices
void Graph::removeEdge(std::string label1, std::string label2) {
    //Ensure both vertices exist
    if (vertices.find(label1) != vertices.end() && vertices.find(label2) != vertices.end()) {
        //Remove the edge from both adjacency lists
        vertices[label1].edges.erase(label2);
        vertices[label2].edges.erase(label1); // Undirected graph
    }
}

// Calculates the shortest path between two vertices using Dijkstra's algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) {
    //Return infinity if either vertex does not exist
    if (vertices.find(startLabel) == vertices.end() || vertices.find(endLabel) == vertices.end()) {
        return std::numeric_limits<unsigned long>::max();
    }

    //Maps to store distances and predecessors
    std::unordered_map<std::string, unsigned long> distances;
    std::unordered_map<std::string, std::string> previous;

    //Priority queue for Dijkstra's algorithm
    HeapQueue<std::pair<unsigned long, std::string>, CompareNodes> pq;

    //Initialize distances
    for (const auto& pair : vertices) {
        distances[pair.first] = std::numeric_limits<unsigned long>::max();
        previous[pair.first] = "";
    }

    //Start node has distance 0
    distances[startLabel] = 0;
    pq.insert({0, startLabel});

    // Main Dijkstra loop
    while (!pq.empty()) {
        unsigned long dist = pq.min().first; //Current shortest distance
        std::string current = pq.min().second; //Current vertex
        pq.removeMin();

        if (current == endLabel) {
            break;
        }
        
        //Stop if the current distance exceeds the known distance
        if (dist > distances[current]) {
            continue;
        }

        //Update distances for neighbors of the current vertex
        for (const auto& neighbor : vertices[current].edges) {
            unsigned long newDist = dist + neighbor.second; //Calculate new distance
            if (newDist < distances[neighbor.first]) {
                distances[neighbor.first] = newDist; //Update shortest distance
                previous[neighbor.first] = current; //Update path
                pq.insert({newDist, neighbor.first}); //Push updated distance to the queue
            }
        }
    }

    // Construct path
    path.clear();
    if (distances[endLabel] == std::numeric_limits<unsigned long>::max()) {
        return distances[endLabel];
    }

    // Special case when start and end are the same
    if (startLabel == endLabel) {
        path.push_back(startLabel);
        return 0;
    }

    // Reconstruct path from end to start using previous map
    std::string current = endLabel;
    while (!current.empty()) {
        path.insert(path.begin(), current); //Insert the vertex at the beginning of the path
        if (current == startLabel) break; //Stop when the start vertex is reached
        current = previous[current];
    }

    return distances[endLabel]; //Return the total shortest distance
}

//Destructor to clean up resources
Graph::~Graph() {
    vertices.clear(); //Clear all vertices and their associated data
}
