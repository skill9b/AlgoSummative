#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: Pathfinding.h
// Description	: This file contains the header class for the Pathfinding class for A* algorithm
// Author		: Jay Patel, Vivian Xu
// Mail			: jay.pat8646@mediadesign.school.nz ,vivian.xu9501@mediadesign.school.nz
//



#include <vector>
#include <set>

#include "Node.h"

class Pathfinding
{
public:
	Pathfinding();
	Pathfinding(int _iSourceX, int _iSourceY, int _iGoalX, int _iGoalY);
	~Pathfinding();

	void FindPath();
	int CalculateFCost(Node* _node);
	int CalculateHCost(Node* _node);		// Manhattan distance
	int CalculateGCost(Node* _currentNode, Node* _neighbourNode);
	Node* GetLowestFCostNode();
	Node* GetEndNode();
	std::set<Node*>* GetNeighbourList(Node* _node);

	void AddObstacle(int _iX, int _iY);
	std::set<Node*>* GetObstacleList();

private:
	int m_iSourceX;
	int m_iSourceY;
	int m_iGoalX;
	int m_iGoalY;
	const int MOVE_STRAIGHT_COST = 10;
	const int MOVE_DIAGONAL_COST = 14;
	const int MAX_GCOST = 999;
	Node* m_endNode;
	std::set<Node*>* m_obstacleList;
	std::set<Node*>* m_openList;
	std::set<Node*>* m_closedList;

	Node* m_pGrid[10][10]{ 0 };
};