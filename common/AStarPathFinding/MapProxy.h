#pragma once

#include "MapConst.h"
#include "MapTileVO.h"
#include "MapAStarCompact.h"
#include "Coord.h"
#include <vector>
#include <set>


class MapProxy
{
private:
	class MapServerBlock
	{
	public:
		static const int WIDTH = 16;
		static const int HEIGHT = 16;
		static const float EXPIRE_TIME; // 1 min
	private:
		unsigned int blockId;
	public:
		const unsigned int &getBlockId() const;

		void ClearAll();

	private:
		unsigned long long GetKey(unsigned int x, unsigned int y);

	private:
		void InitializeInstanceFields();

	public:
		MapServerBlock()
		{
			InitializeInstanceFields();
		}
	};
public:
	

	// this array is arranged by coordinate
private:
	unsigned int _tiles[MapConst::MAP_WIDTH][MapConst::MAP_HEIGHT];
	unsigned int _tilesSprs[MapConst::MAP_SUBMAPS][MapConst::MAP_SUBMAPS];
	/// <summary>
	/// 不同区域之间的通路，先保留
	/// </summary>
	std::vector<MapTileVO*> _wayPoints;
	/// <summary>
	/// 按阵营和等级划分区域存储，快速索引区域，先保留
	/// </summary>
	std::set<unsigned int> visibleBlockIds;
public:
	static MapProxy* GetInstance();

	MapAStarCompact *mapAStar;

	void OnDestroy();

	void OnInit(unsigned char tiles[], unsigned char tileSprites[]);

	MapTileVO *GetWayPointsByCamp();

private:
	static MapProxy* instance;

	unsigned int GetTileBytes(int x, int y, unsigned char bytes[]);

	unsigned int GetTileSprBytes(int x, int y, unsigned char bytes[]);

	// coordinate x/y and data x/y is opposite because:
	// when encoding to binary, the 1st demension of array represents line while the 2nd represents col, that is,
	// when we say (x, y) in binary data, we mean the xth line and yth col.
	// in the other hand, when we get tile by coord from binary, for example, coord is c,
	// in this case, c.x represents col and c.y represents line
	MapTileVO *GetTile(int x, int y, unsigned char bytes[]);

	std::vector<MapTileVO*> GetWayPoints(unsigned char bytes[]);

public:
	MapTileVO *GetTile(int x, int y);

	std::vector<int> GetSprLists(Coord c);

	std::vector<int> GetSprLists(int x, int y);

	MapTileVO *GetTile(Coord coord);

	void SetVisibleBlocks(std::vector<Coord> &coords);


private:
	void InitializeInstanceFields();

public:
	MapProxy()
	{
		InitializeInstanceFields();
	}
};
