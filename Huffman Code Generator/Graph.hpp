/*Anisha Hossain (U43189731), Alina Pineda (U79400432), Tanisha Dutta (U31690052), Brielle Ashmeade (U38424858) 
File description:
This header file (.hpp) declares a Graph class that inherits from GraphBase, defining the structure for an undirected weighted graph. 
It declares the main interface including methods for vertex and edge manipulation, and shortest path finding. 
The class uses a private nested Vertex struct and an unordered map for efficient vertex storage. The public interface includes standard graph operations 
(add/remove vertices and edges) and Dijkstra's shortest path algorithm. 
All methods are declared as overrides of the base class's virtual functions.
*/
#ifndef GRAPH_HPP
#define GRAPH_HPP

//header files
#include "GraphBase.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>

class Graph : public GraphBase {
private:
    //Nested struct to represent a vertex and its edges
    struct Vertex {
        std::string label; //Label for the vertex
        std::unordered_map<std::string, unsigned long> edges; //Edges to other vertices with weights
    };

    //Hash map to store vertices by their labels for quick access
    std::unordered_map<std::string, Vertex> vertices; 

public:
    void addVertex(std::string label) override; //Adds a vertex with the givem label to the graph
    void removeVertex(std::string label) override; //Removes the vertex with the given label from the graph
    void addEdge(std::string label1, std::string label2, unsigned long weight) override; //Adds an edge with a specific weight between two vertices
    void removeEdge(std::string label1, std::string label2) override; //Removes the edge between two vertices

    // Finds the shortest path between two vertices using a suitable algorithm
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path) override;
    ~Graph() override; //Destructor to clean up
};

#endif