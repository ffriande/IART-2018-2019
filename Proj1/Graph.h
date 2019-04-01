#ifndef GRAPH_H
#define GRAPH_H

// C++ program to print DFS traversal from 
// a given vertex in a given graph 
#include<iostream> 
#include<list> 
using namespace std; 

// Graph class represents a directed graph 
// using adjacency list representation 
class Graph 
{ 
	int V; // No. of vertices 
	// Pointer to an array containing 
	// adjacency lists 
	list<int> *adj; 
	// A recursive function used by DFS 
	void DFSUtil(int v, bool visited[]); 
public: 
	Graph(int V); // Constructor 
	// function to add an edge to graph 
	void addEdge(int v, int w); 
	// DFS traversal of the vertices 
	// reachable from v 
	void DFS(int v); 
}; 

int testDFS();

#endif