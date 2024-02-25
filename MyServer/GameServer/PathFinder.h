#pragma once

#include <memory>
#include <list>
#include "Math.h"

using namespace std;

class PathFinder : public enable_shared_from_this<PathFinder>
{
public:
	PathFinder();
	~PathFinder();

public:
	bool IsPathFinder(Vector3& start, Vector3& end, class GridMap* map);
	Vector3 FindTargetPos(Vector3& start, Vector3& end, class GridMap* map);

private:
	class GridNode* FindPath(Vector3& start, Vector3& end, class GridMap* map);
	GridNode* GetAstarNode(class GridNode* targetNode);
	int GCost(class GridNode* startNode, class GridNode* endNode);
	int HCost(class GridNode* startNode, class GridNode* endNode);
	list<class GridNode*> GetNeighborNodeList(class GridNode* center, class GridMap* map);
};

