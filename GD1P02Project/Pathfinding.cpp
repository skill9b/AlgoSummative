//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: Pathfinding.cpp
// Description	: This file contains the Pathfinding class for the A* algorithm
// Author		: Jay Patel, Vivian Xu
// Mail			: jay.pat8646@mediadesign.school.nz ,vivian.xu9501@mediadesign.school.nz
//


# include <iostream>

# include "Pathfinding.h"

Pathfinding::Pathfinding() {
	m_iSourceX = 0;
	m_iSourceY = 0;
	m_iGoalX = 0;
	m_iGoalY = 0;
	m_endNode = nullptr;
	m_obstacleList = new std::set<Node*>();
	m_openList = new std::set<Node*>();
	m_closedList = new std::set<Node*>();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m_pGrid[i][j] = new Node(i, j);
			m_pGrid[i][j]->SetGCost(MAX_GCOST);
			m_pGrid[i][j]->SetFCost(CalculateFCost(m_pGrid[i][j]));
		}
	}
}

Pathfinding::Pathfinding(int _iSourceX, int _iSourceY, int _iGoalX, int _iGoalY) {
	m_iSourceX = _iSourceX;
	m_iSourceY = _iSourceY;
	m_iGoalX = _iGoalX;
	m_iGoalY = _iGoalY;
	m_endNode = nullptr;
	m_obstacleList = new std::set<Node*>();
	m_openList = new std::set<Node*>();
	m_closedList = new std::set<Node*>();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m_pGrid[i][j] = new Node(i, j);
			m_pGrid[i][j]->SetGCost(MAX_GCOST);
			m_pGrid[i][j]->SetFCost(CalculateFCost(m_pGrid[i][j]));
		}
	}
}

Pathfinding::~Pathfinding() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			delete m_pGrid[i][j];
		}
	}

	delete m_obstacleList;
	delete m_openList;
	delete m_closedList;
}

void Pathfinding::FindPath() {
	// Get Source node and add to open list
	m_openList->insert(m_pGrid[m_iSourceX][m_iSourceY]);											
																									
	m_pGrid[m_iSourceX][m_iSourceY]->SetGCost(0);													// Set Source node's G cost
	m_pGrid[m_iSourceX][m_iSourceY]->SetHCost(CalculateHCost(m_pGrid[m_iSourceX][m_iSourceY]));		// Set Source node's H cost
	m_pGrid[m_iSourceX][m_iSourceY]->SetFCost(CalculateFCost(m_pGrid[m_iSourceX][m_iSourceY]));		// Set Source node's F cost
																									
	while (!m_openList->empty()) {																	// While there are nodes discovered/in open list
		Node* currentNode = GetLowestFCostNode(); 													// Set current node to node with lowest F cost
		if ((currentNode->GetX() == m_iGoalX) && (currentNode->GetY() == m_iGoalY)) {				// Check if current node is End node
			m_endNode = currentNode;																// If it is return node 
			return;																					
		}																							
																									
		// Remove current node from open list, add to closed list									
		std::set<Node*>::iterator nodeVisited = m_openList->find(currentNode);						 
		m_openList->erase(nodeVisited);																
		m_closedList->insert(currentNode);															
																									
		std::set<Node*>* neighbourList = GetNeighbourList(currentNode);								// Get neighbourList of current node
		std::set<Node*>::iterator neighbourNode = neighbourList->begin();							// Set beginning of iterator
																									
		for (neighbourNode; neighbourNode != neighbourList->end(); neighbourNode++) {				// Loop until no more neighbours left in neighbourList of current node
																									
			// Update G cost for each neighbour														
			int tempGCost = currentNode->GetGCost() + CalculateGCost(currentNode, *neighbourNode);	// Calculte G cost to see if other nodes' costs need to be updates
			if (tempGCost < (*neighbourNode)->GetGCost()) {											// If new G cost is greater update
				(*neighbourNode)->SetPreviousNode(currentNode);										// Set parent to create path
				(*neighbourNode)->SetGCost(tempGCost);												// Set new G cost
				(*neighbourNode)->SetHCost(CalculateHCost(*neighbourNode));							// Calculate new H cost
				(*neighbourNode)->SetFCost(CalculateFCost(*neighbourNode));							// Calculate new F cost
																									
				// If open list does not contain neighbour node										
				if (m_openList->find(*neighbourNode) == m_openList->end()) {						// If no more neighbours for current node
					m_openList->insert(*neighbourNode);												// Insert neighbours of current node to open list as they're discorvered 
				}
			}
		}
	}

	return;
}


int Pathfinding::CalculateFCost(Node* _currentNode) {
	return (_currentNode->GetGCost() + _currentNode->GetHCost());
}

int Pathfinding::CalculateHCost(Node* _currentNode) {
	// Calculates the manhattan distance between the current node and the goal node
	int hCost = abs(_currentNode->GetX() - m_iGoalX) + abs(_currentNode->GetY() - m_iGoalY);
	return hCost;
}

int Pathfinding::CalculateGCost(Node* _currentNode, Node* _neighbourNode) {
	int iX = _currentNode->GetX();
	int iY = _currentNode->GetY();
	int nX = _neighbourNode->GetX();
	int nY = _neighbourNode->GetY();

	if ((iX - nX == 1) && ((iY - nY) == 0)) {			// Left neighbour
		return MOVE_STRAIGHT_COST;
	}
	else if ((iX - nX == 1) && ((iY - nY) == 1)) {		// Left top neighbour
		return MOVE_DIAGONAL_COST;
	}
	else if ((iX - nX == 1) && ((iY - nY) == -1)) {		// Left bottom neighbour
		return MOVE_DIAGONAL_COST;
	}
	else if ((iX - nX == -1) && ((iY - nY) == 0)) {		// Right neighbour
		return MOVE_STRAIGHT_COST;
	}
	else if ((iX - nX == -1) && ((iY - nY) == 1)) {		// Right top neighbour
		return MOVE_DIAGONAL_COST;
	}
	else if ((iX - nX == -1) && ((iY - nY) == -1)) {	// Right bottom neighbour
		return MOVE_DIAGONAL_COST;
	}
	else if ((iX - nX == 0) && ((iY - nY) == 1)) {		// Top neighbour
		return MOVE_STRAIGHT_COST;
	}
	else if ((iX - nX == 0) && ((iY - nY) == -1)) {		// Bottom neighbour
		return MOVE_STRAIGHT_COST;
	}

	return 0;
}

Node* Pathfinding::GetLowestFCostNode() {
	Node* lowestFCostNode = *(m_openList->begin());

	std::set<Node*>::iterator it = m_openList->begin();

	while (it != m_openList->end()) {
		if (((*it)->GetFCost()) < ((lowestFCostNode)->GetFCost())) {
			lowestFCostNode = *it;
		}
		it++;
	}

	return lowestFCostNode;
}

std::set<Node*>* Pathfinding::GetNeighbourList(Node* _currentNode) {
	std::set<Node*>* neighbourList = new std::set<Node*>();
	std::set<Node*>* finalNeighbourList = new std::set<Node*>();
	int iX = _currentNode->GetX();
	int iY = _currentNode->GetY();

	// Left
	if ((iX - 1) >= 0) {														// Checks if Left is out of bounds	

		if (!m_pGrid[iX - 1][iY]->IsObstacle()) {								// Checks if Left is obstacle

			neighbourList->insert(m_pGrid[iX - 1][iY]);							// Insert Left node 

			if ((iY - 1) >= 0) {												// Checks node Above is out of bounds
				if (!m_pGrid[iX][iY - 1]->IsObstacle()) {						// Checks if Above is not obstacle
					if (!m_pGrid[iX - 1][iY - 1]->IsObstacle()) {				// Checks if Top Left is not obstacle
						neighbourList->insert(m_pGrid[iX - 1][iY - 1]);			// Inserts Top Left 
					}
					else
					{
						m_closedList->insert(m_pGrid[iX - 1][iY - 1]);			//If Top Left is obstacle add to Closed list
					}
				}
			}

			if ((iY + 1) < 10) {												// Checks if node Above is out of bounds
				if (!m_pGrid[iX][iY + 1]->IsObstacle()) {						// Checks if Bottom node is obstacle						
					if (!m_pGrid[iX - 1][iY + 1]->IsObstacle()) {				// Checks if Bottom Left node is Obstacle
						neighbourList->insert(m_pGrid[iX - 1][iY + 1]);			// Insert 
					}
					else
					{
						m_closedList->insert(m_pGrid[iX - 1][iY + 1]);
					}
				}
			}
		}
		else
		{
			m_closedList->insert(m_pGrid[iX - 1][iY]);
		}

	}
	// Right
	if ((iX + 1) < 10) {			
		if (!m_pGrid[iX + 1][iY]->IsObstacle()) {

			neighbourList->insert(m_pGrid[iX + 1][iY]);						// Insert right

			if ((iY - 1) >= 0) {
				if (!m_pGrid[iX][iY - 1]->IsObstacle()) {					// Top (check)
					if (!m_pGrid[iX + 1][iY - 1]->IsObstacle()) {
						neighbourList->insert(m_pGrid[iX + 1][iY - 1]);		// Right top
					}
					else
					{
						m_closedList->insert(m_pGrid[iX + 1][iY - 1]);
					}
				}
			}

			if ((iY + 1) < 10) {
				if (!m_pGrid[iX][iY + 1]->IsObstacle()) {					// Bottom (check)
					if (!m_pGrid[iX + 1][iY + 1]->IsObstacle()) {
						neighbourList->insert(m_pGrid[iX + 1][iY + 1]);		// Right bottom
					}
					else
					{
						m_closedList->insert(m_pGrid[iX + 1][iY + 1]);
					}
				}
			}
		}
		else
		{
			m_closedList->insert(m_pGrid[iX + 1][iY]);
		}
	}

	// Insert Top node if not obstacle
	if ((iY - 1) >= 0) {		
		if (!m_pGrid[iX][iY - 1]->IsObstacle()) {
			neighbourList->insert(m_pGrid[iX][iY - 1]);
		}
		else
		{
			m_closedList->insert(m_pGrid[iX][iY - 1]);
		}
	}
	// Insert Bottom node if not obstacle
	if ((iY + 1) < 10) {			
		if (!m_pGrid[iX][iY + 1]->IsObstacle()) {
			neighbourList->insert(m_pGrid[iX][iY + 1]);
		}
		else
		{
			m_closedList->insert(m_pGrid[iX][iY + 1]);
		}
	}

	std::set<Node*>::iterator it = neighbourList->begin();

	while (it != neighbourList->end()) {
		if (m_closedList->find(*it) == m_closedList->end()) {	// If not in closed list, add to finalNeighbourList
			finalNeighbourList->insert(*it);
		}
		it++;
	}

	return neighbourList;
}

void Pathfinding::AddObstacle(int _iX, int _iY) {
	m_obstacleList->insert(new Node(_iX, _iY));

	m_pGrid[_iX][_iY]->SetObstacle(true);
}

std::set<Node*>* Pathfinding::GetObstacleList() {
	return m_obstacleList;
}

Node* Pathfinding::GetEndNode() {
	return m_endNode;
}

