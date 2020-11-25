#include <iostream>
#include "Maze.h"

Maze::Maze(int n, int m)
{
	this->m_field = new MCell[n*m];
	this->m_width = n;
	this->m_height = m;
}

Maze::~Maze()
{
	delete this->m_field;
	delete this;
}

const MCell& Maze::cell(int i, int j) const
{
	if (i < 0 && j < 0) return *(new MCell());
	return this->m_field[i * this->m_width + j];
}

bool Maze::hasConnection(int i1, int j1, int i2, int j2)
{
	if (((abs(i1 - i2) + abs(j1 - j2)) != 1) || i1 < 0 || i2 < 0 || j1 < 0 || j2 < 0)
		return false;
	MCell c;
	if (i1 != i2)
	{
		if (i1 > i2)
			c = this->cell(i2, j2);
		else c = this->cell(i1, j1);
		return c.m_down;
	}
	else
	{
		if (j1 > j2)
			c = this->cell(i2, j2);
		else c = this->cell(i1, j1);
		return c.m_right;
	}
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2)
{
	MCell* c;
	if (abs(i1 - i2) + abs(j1 - j2) != 1)
		return false;
	if (i1 != i2)
	{
		if (i1 > i2)
			c = &this->m_field[i2 * this->m_width + j2];
		else c = &this->m_field[i1 * this->m_width + j1];
		c->m_down = true;
	}
	else
	{
		if (j1 > j2)
			c = &this->m_field[i2 * this->m_width + j2];
		else c = &this->m_field[i1 * this->m_width + j1];
		c->m_right = true;
	}
	return this->hasConnection(i1, j1, i2, j2);
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2)
{
	MCell c;
	if (abs(i1 - i2) + abs(j1 - j2) != 1)
		return false;
	if (i1 != i2)
	{
		if (i1 > i2)
			c = this->cell(i2, j2);
		else c = this->cell(i1, j1);
		c.m_down = false;
	}
	else
	{
		if (j1 > j2)
			c = this->cell(i2, j2);
		else c = this->cell(i1, j1);
		c.m_right = false;
	}
	return true;
}

void Maze::printMaze()
{
	for (int i = 0; i < this->height(); i++)
	{
		for (int j = 0; j < this->width(); j++)
		{
			bool cLeft = this->hasConnection(i, j, i, j - 1);
			bool cRight = this->hasConnection(i, j, i, j + 1);
			bool cDown = this->hasConnection(i, j, i + 1, j);
			bool cUp = this->hasConnection(i, j, i - 1, j);
			char output = (char)248;
			if (cUp && cRight) output = (char)192;
			if (cUp && cDown) output = (char)179;
			if (cUp && cLeft) output = (char)217;
			if (cRight && cDown) output = (char)218;
			if (cRight && cLeft) output = (char)196;
			if (cDown && cLeft) output = (char)191;
			if (cUp && cRight && cDown) output = (char)195;
			if (cUp && cRight && cLeft) output = (char)193;
			if (cUp && cDown && cLeft) output = (char)180;
			if (cRight && cDown && cLeft) output = (char)194;
			if (cUp && cRight && cDown && cLeft) output = (char)197;
			std::cout << output;
		}
		std::cout << std::endl;
	}
}

int Maze::width()
{
	return this->m_width;
}

int Maze::height()
{
	return this->m_height;
}
