#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: Graph.h
// Description	: This file contains the header file for the Graph class (for BFS and DFS)
// Author		: Jay Patel, Vivian Xu
// Mail			: jay.pat8646@mediadesign.school.nz ,vivian.xu9501@mediadesign.school.nz
//


#include <iostream>
#include <list>
#include <string>
using namespace std;


class Graph
{
	//private:
	//Number of vertices
	int iVertices;

	//Pointer to adjacency list
	list<int>* adjList;

	std::string m_strDFSOutput;
	std::string m_strDFSCurrentNode;

	std::string m_strBFSOutput;
	std::string m_strBFSCurrentNode;
public:
	Graph(int _v); //Constructor
	void resetVertices(int _v); 
	~Graph(); //Destructor
	void addEdge(int _v, int _w); //Function to add edges to graph
	std::string BFS(int s); //Outputs bfs search passing in source node
	void clearStrings();
	void DFSUtil(int v, bool visited[]); //Revursive function used by dfs search
	std::string DFS(int v); //Dfs traversal of vertices, from source v?
	bool m_bOneTimeUse;
};

