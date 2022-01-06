// FILE: main.cpp
// DESCRIPTION: Tests Graph class

// NOTE: You are not allowed to modify this file.

#include <iostream>
using namespace std;

#include "Graph.h"

int main(int argc, char *argv[])
{
  Graph g(argv[1]);

  cout << endl << "Adjacency Matrix" << endl;
  g.display();

  g.displayDFS(0);
  g.displayBFS(0);

  int cost = g.computeMSTCost();
  if (cost != -1)
    cout << "MST Cost: " << cost << endl;
  else
    cout << "Graph not connected - no MST" << endl;

  return 0;
}
