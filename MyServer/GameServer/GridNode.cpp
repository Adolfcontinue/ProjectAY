#include "pch.h"
#include "GridNode.h"

GridNode::GridNode(int minX, int minY, int maxX, int maxY, int indexX, int indexY) :
	Min(minX, minY, 0), Max(maxX, maxY, 0), IndexX(indexX), IndexY(indexY)
{
	Parent = nullptr;
	SetCenter();
}

GridNode::GridNode()
{
	Parent = nullptr;
}

GridNode::~GridNode()
{
}

int GridNode::GetFCost() const
{
	return G + H;
}

void GridNode::SetCenter()
{
	Center.X = (Min.X + Max.X) / 2;
	Center.Y = (Min.Y + Max.Y) / 2;
}

void GridNode::SetParent(GridNode* parent)
{
}
