#pragma once
#include <vector>
#include "GridNode.h"

#define MapSize 64
#define TileSize 400
#define DefaultMap

using namespace std;

class GridMap
{
public:
	GridMap() {};
	~GridMap() {};

private:
	vector<vector<GridNode*>> GridNodes;

public:
	void CreateGridNode(Vector3& start, Vector3& end);
	void CreateDefaultGridNode();
	GridNode* GetGridNode(Vector3& pos) const;
	GridNode* GetGridNode(int indexX, int indexY) const;
};

