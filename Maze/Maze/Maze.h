#include "MCell.h"
#pragma once

#ifndef MAZE_H
#define MAZE_H

class Maze
{
public:
	Maze(int, int);
	~Maze();
	const MCell& cell(int, int) const;
	bool hasConnection(int i1, int j1, int i2, int j2);
	bool makeConnection(int i1, int j1, int i2, int j2);
	bool removeConnection(int i1, int j1, int i2, int j2);
	void printMaze();
	int height();
	int width();
private:
	MCell* m_field;
	int m_height;
	int m_width;
};

#endif MAZE_H
