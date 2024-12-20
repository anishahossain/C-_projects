/*Anisha Hossain (U43189731), Alina Pineda (U79400432), Tanisha Dutta (U31690052), Brielle Ashmeade (U38424858) 
File description:
This file contains the test cases and implementation of the code*/

#include "Graph.hpp" 
#include "GraphBase.hpp"     
#include "HeapQueue.hpp"     
#include <iostream>          
#include <vector>            
#include <cassert>           
#include <tuple>             

// Function to test the shortestPath method of the Graph class
void testShortestPath(Graph& g, std::string startLabel, std::string endLabel, 
    unsigned long expectedDistance, std::vector<std::string> expectedPath) {
    std::vector<std::string> path; // Container for storing the shortest path
    unsigned long distance = g.shortestPath(startLabel, endLabel, path); // Compute shortest path and distance
    
    // Validate the result. If the distance or path doesn't match expectations, throw an error.
    if (distance != expectedDistance || path != expectedPath) {
        throw std::runtime_error("Test failed: Incorrect shortest path or distance");
    }
}

int main() {
    try {
        //Test case 1: General graph with multiple paths
        Graph g1;
        g1.addVertex("1"); //Add vertices to the graph
        g1.addVertex("2");
        g1.addVertex("3");
        g1.addVertex("4");
        g1.addVertex("5");
        g1.addVertex("6");

        //Add edges with weights
        g1.addEdge("1", "2", 7);
        g1.addEdge("1", "3", 9);
        g1.addEdge("1", "6", 14);
        g1.addEdge("2", "3", 10);
        g1.addEdge("2", "4", 15);
        g1.addEdge("3", "4", 11);
        g1.addEdge("3", "6", 2);
        g1.addEdge("4", "5", 6);
        g1.addEdge("5", "6", 9);

        //Test the shortest path between vertex "1" and "5"
        testShortestPath(g1, "1", "5", 20, {"1", "3", "6", "5"});

        //Test case 2: Graph with no path between the start and end vertices
        Graph g2;
        g2.addVertex("A");
        g2.addVertex("B");
        g2.addVertex("C");
        g2.addEdge("A", "B", 5); // Add only one edge

        //Test shortest path where no path exists
        testShortestPath(g2, "A", "C", std::numeric_limits<unsigned long>::max(), {});

        //Test case 3: Start and end vertices are the same
        Graph g3;
        g3.addVertex("X"); // Single vertex
        testShortestPath(g3, "X", "X", 0, {"X"}); //Path should be zero distance and contain only the vertex

        //Test case 4: Graph with a single edge
        Graph g4;
        g4.addVertex("M");
        g4.addVertex("N");
        g4.addEdge("M", "N", 12); //Single edge between two vertices
        testShortestPath(g4, "M", "N", 12, {"M", "N"});

        //If all test cases pass
        std::cout << "All test cases passed!" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        //Handle any test failures
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
}
