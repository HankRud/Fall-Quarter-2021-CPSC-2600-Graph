// NAME:
// FILE: Graph.cpp
// DESCRIPTION: Implementation of the Graph class.

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include "Graph.h"
#include "QueueInt.h"
#include "StackInt.h"

// Constructor: load the graph from a file
Graph::Graph(char *filename)
{
  QueueInt neighbors = QueueInt();
  fstream fin;
  fin.open(filename);
  //string to read into
  string vertex;
  string adj;
  string weight;
  string size;
  
  // readin header

  getline(fin, size, '\n');
  n = stoi(size);

  //initialize adjacency array
  adjArray = new QueueInt[n];
  for (int i = 0; i < n; i++)
  {
    adjArray[i] = QueueInt();
  }

  //create matrix
  adjMatrix = new int *[n];
  for (int i = 0; i < n; ++i)
  {
    adjMatrix[i] = new int[n];
  }

  //fill adj matrix
  for (int row = 0; row < n; row++)
  {

    for (int col = 0; col < n; col++)
    {
      if (row == col)
      {
        adjMatrix[row][col] = 0;
      }
      else
      {
        adjMatrix[row][col] = -1;
      }
    }
  }

  //mark all as false for 
  //dfs visited
  visited = new bool[n];
  for (int i = 0; i < n; i++)
  {
    visited[i] = false;
  }

  string line;
  while (getline(fin, line))
  {

    stringstream lineStream(line);
    //convert values into integers
    int ver;
    int adjc;
    int wt;
    lineStream >> ver;
    lineStream >> adjc;
    lineStream >> wt;
    //input into array if inbounds
    if ((ver < n && adjc < n) && (ver >= 0 && adjc >= 0))
    {
      adjMatrix[ver][adjc] = wt;
      adjMatrix[adjc][ver] = wt;
    }
  }

  //create Queue array
  createQueueArray();
}

// Destructor
Graph::~Graph()
{
  for (int i = 0; i < n; ++i)
  {
    delete[] adjMatrix[i];
  }
  delete[] adjMatrix;
  delete[] visited;
  delete[] adjArray;
}

//creates an ascending ordered queue
void Graph::createQueueArray()
{
  for (int row = 0; row < n; row++)
  {
    for (int col = 0; col < n; col++)
    {
      if (adjMatrix[row][col] > 0)
      {
        adjArray[row].enqueue(col);
      }
    }
  }
}

// Display the adjacency matrix
void Graph::display() const
{
  for (int row = 0; row < n; row++)
  {

    for (int col = 0; col < n; col++)
    {
      if (adjMatrix[row][col] >= 0)
      {
        cout << adjMatrix[row][col] << " ";
      }
      else
      {
        cout << "x ";
      }
    }
    cout << endl;
  }
}

// Displays the depth first search starting at the given vertex
void Graph::displayDFS(int vertex) const
{
  cout << "DFS at vertex: ";
  dfs(vertex, true);
  cout << endl;
}

//performs depth first search
void Graph::dfs(int vertex, bool printOn) const
{

  visited[vertex] = true;
  if (printOn)
  {
    cout << vertex << " ";
  }

  StackInt dfStack = StackInt();
  //populate stack w/adjacent neighbors
  for (int col = 0; col < n; col++)
  {
    int element = adjMatrix[vertex][col];
    if (element > 0 && !(visited[col]))
    {
      dfStack.push(col);
    }
  }

  //sort the stack in ascending order
  dfStack = sortDFStack(dfStack, vertex);
  
  //perform depthfirst search at non visited incecies
  while (!dfStack.isEmpty())
  {
    if (!visited[dfStack.top()])
    {

      dfs(dfStack.pop(), printOn);
    }
    else
    {
      dfStack.pop();
    }
  }
}

//SortDFS Stack
StackInt Graph::sortDFStack(StackInt &stack, int vertex) const
{
  StackInt stack2 = StackInt();

  while (!stack.isEmpty())
  {
    
    int temp = stack.pop();
    
    while (!stack2.isEmpty() && stack2.top() < temp)
    {
      stack.push(stack2.pop());
    }

    stack2.push(temp);
  }
  return stack2;
}

// Perform breadth first search starting at the given vertex
void Graph::displayBFS(int vertex) const
{
  cout << "BFS at vertex: ";
  bfs(vertex);
  cout << endl
       << endl;
}

//Performs BFS
void Graph::bfs(int vertex) const
{

  QueueInt queue = QueueInt();
  //copy adjArray
  QueueInt * adjcopy= new QueueInt[n];
  for(int i= 0; i<n ;i++){
    adjcopy[i]= QueueInt(adjArray[i]);
  } 

  bool bfsvisited[n];
  //initialize bfs visited;
  for (int i = 0; i < n; i++)
  {
    bfsvisited[i] = false;
  }
  // mark first vertex as visited and enque
  bfsvisited[vertex] = true;
  
  queue.enqueue(vertex);
  
  //loop through outer queue
  //until all verticies are visited
  while (!queue.isEmpty())
  {
    int current = queue.front();
    cout << current << " ";
    queue.dequeue();
    //if theres an edge to an unvisted vertex
    //in adjacency queue of the current vertex
    //print and add to outer queue
    while (!adjcopy[current].isEmpty())
    {
      int element = adjcopy[current].front();
      if (element >= 0 && !(bfsvisited[element]))
      {
        bfsvisited[element] = true;
        queue.enqueue(element);
      }
      adjcopy[current].dequeue();
    }
    
  }
}

// Compute the cost of a minimum spanning tree.
int Graph::computeMSTCost() const
{
 //first check if graph is connected
  if (!isConnected())
  {
    return -1;
  }
  //initialize list of visited vertecies 
  //and weights
  bool mstVertecies[n];
  int weights [n];

 
  int count = 0;

  //set all weights tomax
  for (int ix = 0; ix < n; ix++)
  {
    weights[ix] = INT16_MAX;
    mstVertecies[ix] = false;
  }
  //set weight of first index to 0
  //and set visited to true
  weights[0] = 0;
  mstVertecies[0] = true;

  //loop n-1 times 
  for (int outer = 0; outer < n - 1; outer++)
  {
    //find the next edge and add its weight
    int vert = nextEdge(mstVertecies, weights);
    mstVertecies[vert] = true;

    //find all verticies of minimum selected vertex and change values
    //of the weight if it is smaller than previously recorded value
    QueueInt toUse = QueueInt(adjArray[vert]);
    while (!toUse.isEmpty())
    {
        int weight = adjMatrix[vert][toUse.front()];
        int adjVer= toUse.front();
        if (weight>0 && !mstVertecies[adjVer] && weights[adjVer] > weight)
        {
            weights[adjVer] = weight;
            toUse.dequeue();
        }  
        else{
          toUse.dequeue();
        }
      }    
  }
 
  //sum the weights
  for (int i = 0; i < n; i++)
  {
    count += weights[i];
    
  }
  return count;
}

//gets the minimum unvisited edge 
int Graph::nextEdge(bool mstVertecies[], int weights[]) const{

    int min = INT16_MAX;
    int min_index= 0;
 
    for (int v = 0; v < n; v++)
        if (!mstVertecies[v]  && weights[v] < min)
            min = weights[v], min_index = v;
 
    return min_index;

}

     
//checks if graph is connected using dfs
//since graphs are  assumed to not be directional
//only performs forward dfs
bool Graph ::isConnected() const
{
  //ensure dfs has been performed
  dfs(0, false);

  //loop through visited to see if any verticies are disconnected
  for (int i = 0; i < n; i++)
  {
    if (!visited[i])
    {
      return false;
    }
  }
  return true;
}
