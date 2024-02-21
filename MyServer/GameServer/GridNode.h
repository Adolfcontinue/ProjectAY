#pragma once
#include "Math.h"

class GridNode
{
public:
	GridNode(int minX, int minY, int maxX, int maxY, int indexX, int indexY);
	GridNode();
	~GridNode();

public:
	GridNode* Parent;
	Vector3 Min;
	Vector3 Max;
	Vector3 Center;
	int IndexX;
	int IndexY;
	int G;
	int H;
	int F;

public:
	int GetFCost() const;
	void SetParent(GridNode* parent);

private:
	void SetCenter();

};

