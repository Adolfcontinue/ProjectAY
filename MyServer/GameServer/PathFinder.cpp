#include "pch.h"
#include "PathFinder.h"
#include "GridMap.h"


PathFinder::PathFinder()
{
}

PathFinder::~PathFinder()
{
}

Vector3 PathFinder::FindTargetPos(Vector3& start, Vector3& end, GridMap* map)
{
	GridNode* endNode = FindPath(start, end, map);
	if (endNode == nullptr)
		return NULL;
	
	GridNode* targetNode = GetAstarNode(endNode);
	if (targetNode == nullptr)
		return NULL;

	return targetNode->Center;
}

GridNode* PathFinder::FindPath(Vector3& start, Vector3& end, GridMap* map)
{
	GridNode* startNode = map->GetGridNode(start);
	if (startNode == nullptr)
		return nullptr;

	GridNode* endNode = map->GetGridNode(end);
	if (endNode == nullptr)
		return nullptr;

	list<GridNode*> openList;
	unordered_set<GridNode*> closeList;

	startNode->Parent = nullptr;
	startNode->G = GCost(startNode, startNode);
	startNode->H = HCost(startNode, endNode);

	openList.push_back(startNode);

	GridNode* retNode = nullptr;
	while (openList.size() > 0)
	{
		auto findIt = min_element(openList.begin(), openList.end(),
			[](GridNode* src, GridNode* desc) {
				return src->GetFCost() < desc->GetFCost();
			});

		GridNode* curNode = *findIt;
		if (curNode == nullptr)
			break;

		openList.remove(curNode);
		closeList.insert(curNode);

		if (curNode == endNode)
		{
			retNode = curNode;
			break;
		}

		auto neighborNodelist = GetNeighborNodeList(curNode, map);
		for (auto iter : neighborNodelist)
		{
			GridNode* neighborNode = iter;

			if (closeList.find(neighborNode) != closeList.end())
				continue;

			int curToNeighberGCost = GCost(curNode, neighborNode);
			int neighborToStartGCost = curNode->G + curToNeighberGCost;

			auto findIter = find(openList.begin(), openList.end(), neighborNode);
			if (findIter == openList.end())
			{
				neighborNode->Parent = curNode;
				neighborNode->G = neighborToStartGCost;
				neighborNode->H = HCost(neighborNode, endNode);

				openList.push_back(neighborNode);
			}
			else
			{
				if (neighborToStartGCost < neighborNode->G)
				{
					neighborNode->G = neighborToStartGCost;
					neighborNode->Parent = curNode;
				}
			}
		}
	}

	return retNode;
}

GridNode* PathFinder::GetAstarNode(GridNode* targetNode)
{
	if (targetNode == nullptr)
		return nullptr;

	GridNode* node = targetNode;
	GridNode* retNode = nullptr;
	while (true)
	{
		if (node->Parent == nullptr)
			break;

		node = node->Parent;
		retNode = node;
	}

	return retNode;
}

int PathFinder::GCost(GridNode* startNode, GridNode* endNode)
{
	int xDiff = abs(endNode->IndexX - startNode->IndexX);
	int yDiff = abs(endNode->IndexY - startNode->IndexY);

	if (xDiff > yDiff)
		return (yDiff * 14) + (abs(xDiff - yDiff) * 10);
	else
		return (xDiff * 14) + (abs(yDiff - xDiff) * 10);
}

int PathFinder::HCost(GridNode* startNode, GridNode* endNode)
{
	int xDiff = abs(endNode->IndexX - startNode->IndexX);
	int yDiff = abs(endNode->IndexY - startNode->IndexY);

	return (xDiff + yDiff) * 10;
}

list<GridNode*> PathFinder::GetNeighborNodeList(GridNode* center, GridMap* map)
{
	list<GridNode*> retList;

	for (int i = center->IndexY - 1; i <= center->IndexY + 1; ++i)
	{
		for (int j = center->IndexX - 1; j <= center->IndexX + 1; ++j)
		{
			if (i == center->IndexY && j == center->IndexX)
				continue;

			GridNode* neighborNode = map->GetGridNode(j, i);
			if (neighborNode == nullptr)
				continue;

			retList.push_back(neighborNode);
		}
	}

	return retList;
}

