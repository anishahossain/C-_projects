/*Anisha Hossain (U43189731), Alina Pineda (U79400432), Tanisha Dutta (U31690052), Brielle Ashmeade (U38424858) 
File description:
This header file (.hpp) contains the abstract base class given in the assignment.
*/
#ifndef GRAPHBASE_H
#define GRAPHBASE_H
#include <vector>
#include <string>

//Abstract base class for a graph representation
class GraphBase {
    public:
    virtual void addVertex(std::string label) = 0; //Pure virtual function to add a vertex to the graph
    virtual void removeVertex(std::string label) = 0; //Pure virtual function to remove a vertex from the graph

    // Pure virtual function to add an edge between two vertices with a specified weight
    virtual void addEdge(std::string label1, std::string label2, unsigned long weight) = 0; 

    virtual void removeEdge(std::string label1, std::string label2) = 0; //Pure virtual function to remove an edge between two vertices

    // Pure virtual function to compute the shortest path between two vertices
    // Returns the distance of the shortest path and stores the path in the `path` vector
    virtual unsigned long shortestPath(std::string startLabel, std::string endLabel,
    std::vector<std::string> &path) = 0;

    virtual ~GraphBase() {} // Add virtual destructor
};
#endif
