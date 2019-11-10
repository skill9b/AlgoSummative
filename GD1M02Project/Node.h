//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: Node.h
// Description	: This file contains the header class for the Node class
// Author		: Jay Patel, Vivian Xu
// Mail			: jay.pat8646@mediadesign.school.nz ,vivian.xu9501@mediadesign.school.nz
//


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

