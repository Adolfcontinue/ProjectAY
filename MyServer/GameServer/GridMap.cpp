#include "pch.h"
#include "GridMap.h"



void GridMap::CreateGridNode(Vector3& start, Vector3& end)
{
}

void GridMap::CreateDefaultGridNode()
{
#ifdef DefaultMap
    for (int y = 0; y < MapSize; ++y)
    {
        vector<GridNode*> v;
        for (int x = 0; x < MapSize; ++x)
        {
            int minX = x * TileSize;
            int maxX = x + 1 * TileSize;

            int minY = y * TileSize;
            int maxY = y + 1 * TileSize;
            GridNode* node = new GridNode(minX, minY, maxX, maxY, x, y);
            v.push_back(node);
        }

        GridNodes.push_back(v);
    }
#else
    return;
#endif
}

GridNode* GridMap::GetGridNode(Vector3& pos) const
{
    int indexX = pos.X / TileSize;
    int indexY = pos.Y / TileSize;

    return GetGridNode(indexX, indexY);
}

GridNode* GridMap::GetGridNode(int indexX, int indexY) const
{
	if (indexX < 0 || indexX >= MapSize)
		return nullptr;

	if (indexY < 0 || indexY >= MapSize)
		return nullptr;

	return GridNodes[indexY][indexX];
}


