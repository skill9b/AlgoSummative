
# include <iostream>

# include "Pathfinding.h"

Pathfinding::Pathfinding() {
	m_iSourceX = 0;
	m_iSourceY = 0;
	m_iGoalX = 0;
	m_iGoalY = 0;
	endNode = nullptr;
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
	endNode = nullptr;
	m_obstacleList = new std::set<Node*>();
	m_openList = new std::set<Node*>();
	m_closedList = new std::set<Node*>();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			m_pGrid[i][j] = new Node(i,j);
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
	// std::cout << "Adding source node to open list: " << std::endl;

	m_pGrid[m_iSourceX][m_iSourceY]->SetGCost(0);						// Start node cost
	m_pGrid[m_iSourceX][m_iSourceY]->SetHCost(CalculateHCost(m_pGrid[m_iSourceX][m_iSourceY]));
	m_pGrid[m_iSourceX][m_iSourceY]->SetFCost(CalculateFCost(m_pGrid[m_iSourceX][m_iSourceY]));

	while (!m_openList->empty()) {
		Node* currentNode = GetLowestFCostNode(); // make sure there is no other node that is lower???
		if ((currentNode->GetX() == m_iGoalX) && (currentNode->GetY() == m_iGoalY)) {
			endNode = currentNode;
			return;
		}

		// Remove current node from open list, add to closed list
		std::set<Node*>::iterator nodeVisited = m_openList->find(currentNode);
		m_openList->erase(nodeVisited);
		m_closedList->insert(currentNode);

		std::set<Node*>* neighbourList = GetNeighbourList(currentNode);
		std::set<Node*>::iterator neighbourNode = neighbourList->begin();

		// For each neighbour of current node...
		for (neighbourNode; neighbourNode != neighbourList->end(); neighbourNode++) {
			
			//if ((*neighbourNode)->IsObstacle()) {
			//	m_closedList->insert(*neighbourNode);
			//	continue;
			//}
			
			// if already in closed list, continue
			//if (m_closedList->find(*neighbourNode) != m_closedList->end()) {	
			//	continue;
			//}
			
			int tempGCost = currentNode->GetGCost() + CalculateGCost(currentNode, *neighbourNode);
			if (tempGCost < (*neighbourNode)->GetGCost()) {
				(*neighbourNode)->SetPreviousNode(currentNode);
				(*neighbourNode)->SetGCost(tempGCost);
				(*neighbourNode)->SetHCost(CalculateHCost(*neighbourNode));
				(*neighbourNode)->SetFCost(CalculateFCost(*neighbourNode));

				if (m_openList->find(*neighbourNode) == m_openList->end()) {	// If open list does not contain neighbour node
					m_openList->insert(*neighbourNode);
				}
			}
		}

		 //DisplayOpenList();
		 //std::cout << std::endl;
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
}

Node* Pathfinding::GetLowestFCostNode() {
	Node* lowestFCostNode = *(m_openList->begin());

	std::set<Node*>::iterator it = m_openList->begin();

	while (it != m_openList->end()) {
		if (((*it)->GetFCost()) < ((lowestFCostNode)->GetFCost()) ) {
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

	if ((iX - 1) >= 0) {		// Left

		if (!m_pGrid[iX - 1][iY]->IsObstacle()) {				

			neighbourList->insert(m_pGrid[iX - 1][iY]);							// Insert left

			if ((iY - 1) >= 0) {												// Top (check)
				if (!m_pGrid[iX][iY - 1]->IsObstacle()) {						
					if (!m_pGrid[iX - 1][iY - 1]->IsObstacle()) {				// Left Top
						neighbourList->insert(m_pGrid[iX - 1][iY - 1]);
					}
					else 
					{
						m_closedList->insert(m_pGrid[iX - 1][iY - 1]);
					}
				}
			}

			if ((iY + 1) < 10) {
				if (!m_pGrid[iX][iY + 1]->IsObstacle()) {					// Bottom (check)						
					if (!m_pGrid[iX - 1][iY + 1]->IsObstacle()) {			
						neighbourList->insert(m_pGrid[iX - 1][iY + 1]);		// Left bottom
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

	if ((iX + 1) < 10) {			// Right
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


	if ((iY - 1) >= 0) {		// Top node
		if (!m_pGrid[iX][iY - 1]->IsObstacle()) {		
			neighbourList->insert(m_pGrid[iX][iY - 1]);			
		}
		else
		{
			// Add top node to closed list
			m_closedList->insert(m_pGrid[iX][iY - 1]);
		}
	}

	if ((iY + 1) < 10) {			// Bottom node
		if (!m_pGrid[iX][iY + 1]->IsObstacle()) {
			neighbourList->insert(m_pGrid[iX][iY + 1]);
		}
		else
		{
			// Add bottom node to closed list
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

	 //std::cout << "CurrentNode: " << _currentNode->GetX() << "," << _currentNode->GetY() << std::endl;
	 //DisplayClosedList();
	 //DisplayNeighbourList(finalNeighbourList);

	return neighbourList;
}


void Pathfinding::DisplayPath() {

	std::vector<Node*>* path = new std::vector<Node*>();

	path->push_back(endNode);
	Node* currentNode = endNode;

	if (currentNode == nullptr) {
		std::cout << "ERROR: The A* algorithm cannot find a valid path!" << std::endl;
		return;
	}

	std::cout << "Total A* Path Cost: " << currentNode->GetFCost() << std::endl;

	while (currentNode->GetPreviousNode() != nullptr) {
		path->push_back(currentNode->GetPreviousNode());
		currentNode = currentNode->GetPreviousNode();
	}

	std::cout << "A* Output: " << std::endl;
	std::reverse(path->begin(), path->end());
	std::vector<Node*>::iterator it = path->begin();
	while (it != path->end())
	{
		std::cout << (*it)->GetX() << "," << (*it)->GetY() << std::endl;
		it++;
	}
	return;
}



void Pathfinding::DisplayGrid() {
	std::cout << "A Star Grid: " << std::endl;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << m_pGrid[i][j]->GetX() << "," << m_pGrid[i][j]->GetY() << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void Pathfinding::AddObstacle(int _iX, int _iY) {
	m_obstacleList->insert(new Node(_iX, _iY));

	m_pGrid[_iX][_iY]->SetObstacle(true);
}

void Pathfinding::DisplayObstacleList() {
	std::cout << "Obstacle List: " << std::endl;

	std::set<Node*>::iterator it = m_obstacleList->begin();

	while (it != m_obstacleList->end()) {
		std::cout << (*it)->GetX() << "," << (*it)->GetY() << " ";
		it++;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void Pathfinding::DisplayOpenList() {
	std::cout << "Open List: ";

	std::set<Node*>::iterator it = m_openList->begin();

	while (it != m_openList->end()) {
		std::cout << (*it)->GetX() << "," << (*it)->GetY() << " ";
		it++;
	}
	std::cout << std::endl;
}

void Pathfinding::DisplayClosedList() {
	std::cout << "Closed List: ";

	std::set<Node*>::iterator it = m_closedList->begin();

	while (it != m_closedList->end()) {
		std::cout << (*it)->GetX() << "," << (*it)->GetY() << " ";
		it++;
	}
	std::cout << std::endl;
}

void Pathfinding::DisplayNeighbourList(std::set<Node*>* _neighbourList) {
	std::cout << "Neighbour List: ";

	std::set<Node*>::iterator it = _neighbourList->begin();

	while (it != _neighbourList->end()) {
		std::cout << (*it)->GetX() << "," << (*it)->GetY() << " ";
		it++;
	}
	std::cout << std::endl;
}


