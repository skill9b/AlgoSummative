
#include <vector>
#include <set>
# include "Node.h"

class Pathfinding 
{
public:
	Pathfinding();
	Pathfinding(int _iSourceX, int _iSourceY, int _iGoalX, int _iGoalY);
	~Pathfinding();

	void FindPath();
	void DisplayPath();
	void DisplayGrid();
	int CalculateFCost(Node* _node);	
	int CalculateHCost(Node* _node);		// Manhattan distance
	int CalculateGCost(Node* _currentNode, Node* _neighbourNode);
	Node* GetLowestFCostNode();
	std::set<Node*>* GetNeighbourList(Node* _node);

	void AddObstacle(int _iX, int _iY);
	void DisplayObstacleList();
	void DisplayOpenList();
	void DisplayClosedList();
	void DisplayNeighbourList(std::set<Node*>* _neighbourList);

private:
	int m_iSourceX;
	int m_iSourceY;
	int m_iGoalX;
	int m_iGoalY;
	const int MOVE_STRAIGHT_COST = 10;
	const int MOVE_DIAGONAL_COST = 14;
	const int MAX_GCOST = 999;
	Node* endNode;
	std::set<Node*>* m_obstacleList;
	std::set<Node*>* m_openList;
	std::set<Node*>* m_closedList;
	
	Node* m_pGrid[10][10];
};