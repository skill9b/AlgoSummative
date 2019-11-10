#include "cGraph.h"

cGraph::cGraph(int _v)
{
	this->iVertices = _v;
	adjList = new list<int> [_v];
}

void cGraph::resetVertices(int _v)
{
	this->iVertices = _v;
	adjList = new list<int>[_v];
}

cGraph::~cGraph()
{
	delete adjList;
}

void cGraph::addEdge(int _v, int _w)
{
	//Done twice in opposite so that it becomes unidirection rather than bidirectional

	adjList[_v].push_back(_w); //Add w to v's list of edges
	adjList[_w].push_back(_v); //Add v to w's list of edges
}

std::string cGraph::BFS(int s)
{
	std::string strBFS;
	std::string strNodeToAdd; //String stores current node to add to strBFS
	m_bOneTimeUse = true;
	//Mark all vertices as not visited 
	bool* verticesVisited = new bool[iVertices];
	for (int i = 0; i < iVertices; i++)
	{
		verticesVisited[i] = false;
	}

	//Create queue 
	list<int> Queue;

	//Mark source node as visited and add to queue
	verticesVisited[s] = true;
	Queue.push_back(s);

	//Iterator to get all adjacent vectors of vertex
	list<int>::iterator Iterator;

	while (!Queue.empty())
	{
		s = Queue.front(); //Make sure current visited vertex is front of queue
		//cout << s << " "; //Output vertex

		//Combine all into string here and return at the end
		strNodeToAdd = std::to_string(s);

		if (m_bOneTimeUse)
		{
			strBFS = strNodeToAdd; //Set it once to start
			m_bOneTimeUse = false;
		}
		else
		{
			strBFS = strBFS + ", " + strNodeToAdd; //Updates return string with current node every loop
		}
		
		Queue.pop_front(); //Dequeue current visited vertex

		//Get all adjecent vertices of matrix just dequeued
		for (Iterator = adjList[s].begin(); Iterator != adjList[s].end(); Iterator++)
		{
			//If adjacent vertex has not been visited 
			if (!verticesVisited[*Iterator])
			{
				//then mark as visited 
				verticesVisited[*Iterator] = true;
				//and enqueue it
				Queue.push_back(*Iterator);
			}
		}

		

	}

	//return string version of output
	return (strBFS);
}

void cGraph::clearStrings()
{
	m_strDFSOutput = "";
	m_strBFSOutput = "";
	m_strDFSOutput.clear();
	m_strBFSOutput.clear();

	m_strDFSCurrentNode = "";
	m_strBFSCurrentNode = "";
	m_strDFSCurrentNode.clear();
	m_strBFSCurrentNode.clear();
}

void cGraph::DFSUtil(int v, bool _verticesVisited[])
{
	//Mark current node as visited and output
	_verticesVisited[v] = true;
	//cout << v << " ";

	m_strDFSCurrentNode = std::to_string(v);

	if (m_bOneTimeUse)
	{
		m_strDFSOutput = m_strDFSCurrentNode; //Set it once to start
		m_bOneTimeUse = false;
	}
	else
	{
		m_strDFSOutput = m_strDFSOutput + ", " + m_strDFSCurrentNode; //Updates return string with current node every loop
	}


	//Call recursive for all adjacent vertices using iterator
	list<int>::iterator Iterator;
	for (Iterator = adjList[v].begin(); Iterator != adjList[v].end(); Iterator++)
	{
		if (!_verticesVisited[*Iterator])
		{
			DFSUtil(*Iterator, _verticesVisited);
		}
	}
}

std::string cGraph::DFS(int v)
{
	//Mark all vertices as not visited 
	bool* verticesVisited = new bool[iVertices];
	for (int i = 0; i < iVertices; i++)
	{
		verticesVisited[i] = false;
	}

	m_bOneTimeUse = true;
	//Call recursive function to output traversal
	DFSUtil(v, verticesVisited);

	
	return (m_strDFSOutput);
}
