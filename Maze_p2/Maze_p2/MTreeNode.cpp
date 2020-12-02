#include "MTreeNode.h"
#include <iostream>

int MTreeNode::i() const
{
	return this->m_i;
}

int MTreeNode::j() const
{
	return this->m_j;
}

const MTreeNode* MTreeNode::parent() const
{
	return this->m_parent;
}

const MTreeNode* MTreeNode::child(int i) const
{
	return this->m_children[i];
}

int MTreeNode::distance() const
{
	return this->m_distance;
}

int MTreeNode::childCount() const
{
	return (this->m_children[0] != nullptr) + (this->m_children[1] != nullptr);
}

bool MTreeNode::addChild(int i, int j)
{
	if (abs(this->i() - i) + abs(this->j() - j) != 1) return false;
	if (this->hasChild(i, j) != nullptr) return false;
	MTreeNode* newChild = new MTreeNode(this);
	newChild->m_i = i;
	newChild->m_j = j;
	if (this->i() == i)
	{
		this->m_children[1] = newChild; // child вправо - 1
	}
	else this->m_children[0] = newChild; // child вниз - 0
	return true;
}

MTreeNode* MTreeNode::hasChild(int i, int j)
{
	for (int k = 0; k < 2; k++)
	{
		MTreeNode* child = this->m_children[k];
		if (child != nullptr)
		{
			if (child->i() == i && child->j() == j)
				return child;
		}
	}
	return nullptr;
}

MTreeNode* MTreeNode::beginTree(int i, int j)
{
	MTreeNode* newNode = new MTreeNode(nullptr);
	newNode->m_i = i;
	newNode->m_j = j;
	return newNode;
}

MTreeNode::MTreeNode(MTreeNode* parent)
{
	this->m_parent = parent;
	if (parent != nullptr) this->m_distance = parent->distance() + 1;
	else this->m_distance = 0;
}