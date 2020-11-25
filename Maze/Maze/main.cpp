#include "Maze.h"
#include <iostream>

int main()
{
	auto maze = new Maze(5, 5);
	bool c = maze->makeConnection(0, 0, 0, 1);
	c = maze->makeConnection(0, 1, 1, 1);
	c = maze->makeConnection(1, 1, 1, 2);
	c = maze->makeConnection(1, 2, 2, 2);
	c = maze->makeConnection(2, 2, 2, 3);
	c = maze->makeConnection(2, 3, 3, 3);
	c = maze->makeConnection(3, 3, 3, 4);
	c = maze->makeConnection(3, 4, 4, 4);
	c = maze->makeConnection(3, 4, 4, 4);
	maze->printMaze();
}