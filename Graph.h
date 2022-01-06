// NAME: 
// FILE: Graph.h
// DESCRIPTION: Definition of the Graph class.

#ifndef GRAPH_H
#define GRAPH_H

#include "QueueInt.h"
#include "StackInt.h"

class Graph {

  public:

    // Constructor: load the graph from a file
    Graph(char *fileName);

    // Destructor
    ~Graph();

    // Display the adjacency matrix
    void display() const;

    // Display the depth first search from the given vertex
    void displayDFS(int vertex) const;

    // Display the breadth first search from the given vertex
    void displayBFS(int vertex) const;

    // Compute the cost of a minimum spanning tree.
    int computeMSTCost() const;

  private:
    // TODO: Complete the private section of the class.
    //the number of vertecies
    int n;
    //the adjacency matrix
    int** adjMatrix;
    //store if vertex visited for recursive dfs
    bool * visited;
    //Array of QueueInt's storing vertecies adjacent to 
    //given vertex
    QueueInt * adjArray;

    //helper function to sort stacks
   StackInt sortDFStack( StackInt &stack, int vertex)  const;

   //helper function to perform dfs
   void dfs(int vertex, bool printOn) const;

   //helper fucntion to perform bf
   void bfs(int vertex) const;

  //creates an array of sorted QueueInts 
   void createQueueArray();

  //returns if graph is connected
   bool isConnected() const;

  //helper funtion for mst
   int nextEdge( bool mstVertecies[], int *weights) const;
};

#endif
