
# include <iostream>

# include "Pathfinding.h"

int main() {

	int iSourceX = 7;
	int iSourceY = 8;
	int iGoalX = 4;
	int iGoalY = 6;

	Pathfinding* path = new Pathfinding(iSourceX, iSourceY, iGoalX, iGoalY);

	path->AddObstacle(6,7); 
	path->AddObstacle(6,8); 
	path->AddObstacle(7,7); 

	path->DisplayObstacleList();
	path->DisplayGrid();

	path->FindPath();
	path->DisplayPath();

	int iTemp;
	std::cin >> iTemp;
	return(0);
}