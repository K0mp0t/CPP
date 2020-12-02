#include "MTreeNode.h"
#include "Maze.h"
#include <iostream>


Maze* goingDeep(MTreeNode* root, Maze* maze)
{
	bool down = false;
	bool right = false;
	int i = root->i();
	int j = root->j();
	if (root->child(0) != nullptr) 
	{ 
		down = true;
		maze = goingDeep((MTreeNode*)(root->child(0)), maze);
	}
	if (root->child(1) != nullptr)
	{
		right = true;
		maze = goingDeep((MTreeNode*)(root->child(1)), maze);
	}
	if (down) bool c = maze->makeConnection(i, j, i + 1, j);
	if (right) bool c = maze->makeConnection(i, j, i, j + 1);
	return maze;
}

Maze* convert(MTreeNode* root, int size)
{
	MTreeNode* currentNode = root;
	auto maze = new Maze(size, size);
	maze = goingDeep(currentNode, maze);
	return maze;
}


MTreeNode* makeTree(MTreeNode* root, int size)
{
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
		if (i != size-1) // цепляемся за новую ноду, от которой будем дальше плясать
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
	return root;
}

int** treeWalk(MTreeNode* root, int size)
{
	int** distances;
	distances = new int* [size];
	for (int i = 0; i < size; i++)
	{
		distances[i] = new int[size];
	}
	distances[0][0] = 0;
	MTreeNode* rootCopy = root;
	MTreeNode* rootCopyCopy = rootCopy;
	bool c;
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
	return distances;
}

void print2DArray(int** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	const int size = 10; //влияет на все, работает со всеми не слишком большими неотрцательными целыми числами, если поменять, дерево станет больше/меньше.
	auto root = MTreeNode::beginTree(0, 0);
	root = makeTree(root, size);
	Maze* maze = convert(root, size);
	maze->printMaze();
	int** distances = treeWalk(root, size);
	print2DArray(distances, size);
}