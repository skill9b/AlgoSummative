#pragma once
class Node
{
public:
	Node();
	Node(int _iX, int _iY);
	~Node();

	int GetX();
	int GetY();
	int GetFCost();
	int GetGCost();
	int GetHCost();
	void SetFCost(int _fCost);
	void SetGCost(int _gCost);
	void SetHCost(int _hCost);
	bool IsObstacle();
	void SetObstacle(bool _isObstacle);
	Node* GetPreviousNode();
	void SetPreviousNode(Node* _prevNode);

private:
	int m_iX;
	int m_iY;
	int m_fCost;
	int m_gCost;
	int m_hCost;
	bool bObstacle;
	Node* m_previousNode;
};

