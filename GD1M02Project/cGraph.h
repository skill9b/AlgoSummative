#pragma once
#include<iostream> 
#include <list> 
#include <string>
using namespace std;


class cGraph
{
	//private:
		//Number of vertices
	int iVertices;

	//Pointer to adjacency list
	list<int>* adjList;

	std::string m_strDFSOutput;
	std::string m_strCurrentNode;
public:
	cGraph(int _v); //Constructor
	~cGraph(); //Destructor
	void addEdge(int _v, int _w); //Function to add edges to graph
	std::string BFS(int s); //Outputs bfs search passing in source node

	void DFSUtil(int v, bool visited[]); //Revursive function used by dfs search
	std::string DFS(int v); //Dfs traversal of vertices, from source v?
};

