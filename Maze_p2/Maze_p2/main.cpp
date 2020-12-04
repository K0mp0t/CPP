#include "MTreeNode.h"
#include "Maze.h"
#include <iostream>


int main()
{
	const int size = 5; //влияет на все, работает со всеми не слишком большими неотрцательными целыми числами, если поменять, дерево станет больше/меньше.
	auto root = MTreeNode::beginTree(0, 0);
	MTreeNode* rootCopy = root;
	MTreeNode* rootCopyCopy = rootCopy;
	bool c;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++) // вниз
		{
			c = rootCopy->addChild(j, i);
			rootCopy = rootCopy->hasChild(j, i);
		}
		rootCopy = rootCopyCopy;
		if (i != size - 1) // цепляемся за новую ноду, от которой будем дальше плясать
		{
			c = rootCopy->addChild(i, i + 1);
			rootCopy = rootCopy->hasChild(i, i + 1);
			c = rootCopy->addChild(i + 1, i + 1);
			rootCopyCopy = rootCopy->hasChild(i + 1, i + 1);
		}
		for (int j = i + 2; j < size; j++) // вправо
		{
			c = rootCopy->addChild(i, j);
			rootCopy = rootCopy->hasChild(i, j);
		}
		rootCopy = rootCopyCopy;
	}
	Maze* maze = new Maze(size, size);
	rootCopy = root;
	for (int i = 0; i < size; i++)
	{
		int j = rootCopy->j();
		rootCopyCopy = rootCopy;
		int k = i+1;
		MTreeNode* child = rootCopyCopy->hasChild(k, j);
		while (child != nullptr)
		{
			c = maze->makeConnection(k-1, j, k, j);
			rootCopyCopy = child;
			k++;
			child = rootCopyCopy->hasChild(k, j);
		}
		k = i + 1;
		rootCopyCopy = rootCopy;
		child = rootCopyCopy->hasChild(i, k);
		if (i < size-1)
		{
			rootCopy = child->hasChild(i + 1, i + 1);
			c = maze->makeConnection(i, k, k, k);
		}
		while (child != nullptr)
		{
			c = maze->makeConnection(j, k - 1, j, k);
			rootCopyCopy = child;
			k++;
			child = rootCopyCopy->hasChild(i, k);
		}
	}
	maze->printMaze();
	int** distances;
	distances = new int* [size];
	for (int i = 0; i < size; i++)
	{
		distances[i] = new int[size];
	}
	distances[0][0] = 0;
	rootCopy = root;
	rootCopyCopy = rootCopy;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++) // вниз
		{
			rootCopy = rootCopy->hasChild(j, i);
			distances[j][i] = rootCopy->distance();
		}
		rootCopy = rootCopyCopy;
		if (i != size - 1) // цепляемся за новую ноду, от которой будем дальше плясать
		{
			rootCopy = rootCopy->hasChild(i, i + 1);
			distances[i][i + 1] = rootCopy->distance();
			rootCopyCopy = rootCopy->hasChild(i + 1, i + 1);
			distances[i + 1][i + 1] = rootCopyCopy->distance();
		}
		for (int j = i + 2; j < size; j++) // вправо
		{
			rootCopy = rootCopy->hasChild(i, j);
			distances[i][j] = rootCopy->distance();
		}
		rootCopy = rootCopyCopy;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << distances[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}