#pragma once

#ifndef MCELL_H
#define MCELL_H

class MCell
{
public:
	bool right();
	bool down();
private:
	bool m_down = false;
	bool m_right = false;

	friend class Maze;
};

#endif MCELL_H
