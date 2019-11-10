#include "Node.h"

Node::Node() {
	m_iX = 0;
	m_iY = 0;
	bObstacle = false;
	m_fCost = 0;
	m_gCost = 0;
	m_hCost = 0;
	m_previousNode = nullptr;
}

Node::Node(int _iX, int _iY) {
	m_iX = _iX;
	m_iY = _iY;
	bObstacle = false;
	m_fCost = 0;
	m_gCost = 0;
	m_hCost = 0;
	m_previousNode = nullptr;
}

Node::~Node() {  }

int Node::GetX() {
	return m_iX;
}

int Node::GetY() {
	return m_iY;
}

int Node::GetFCost() {
	return m_fCost;
}

int Node::GetGCost() {
	return m_gCost;
}

int Node::GetHCost() {
	return m_hCost;
}

void Node::SetFCost(int _fCost) {
	m_fCost = _fCost;
}

void Node::SetGCost(int _gCost) {
	m_gCost = _gCost;
}

void Node::SetHCost(int _hCost) {
	m_hCost = _hCost;
}

Node* Node::GetPreviousNode() {
	return m_previousNode;
}

bool Node::IsObstacle() {
	return bObstacle;
}

void Node::SetObstacle(bool _isObstacle) {
	bObstacle = _isObstacle;
}

void Node::SetPreviousNode(Node* _prevNode) {
	m_previousNode = _prevNode;
}
