#include "MapProxy.h"
#include "Utils.h"

const float MapProxy::MapServerBlock::EXPIRE_TIME = 60.0f;
MapProxy* MapProxy::instance;

MapProxy* MapProxy::GetInstance()
{
	if(instance == nullptr)
	{
		instance = new MapProxy();
	}
	return instance;
}

const unsigned int &MapProxy::MapServerBlock::getBlockId() const
{
	return blockId;
}

void MapProxy::MapServerBlock::ClearAll()
{
	blockId = 0;
}

unsigned long long MapProxy::MapServerBlock::GetKey(unsigned int x, unsigned int y)
{
	return (static_cast<unsigned long long>(x) << 32) + y;
}

void MapProxy::MapServerBlock::InitializeInstanceFields()
{
	blockId = 0;
}

void MapProxy::OnDestroy()
{

}

void MapProxy::OnInit(unsigned char tiles[], unsigned char tileSprites[])
{
	if (tiles != nullptr)
	{
		for (int y = 0; y < MapConst::MAP_HEIGHT; ++y)
		{
			for (int x = 0; x < MapConst::MAP_WIDTH; ++x)
			{
				unsigned int tileBytes = GetTileBytes(x, y, tiles);
				_tiles[y][x] = tileBytes;
			}
		}
		_wayPoints = GetWayPoints(tiles);
	}
	else
	{
		Utils::LogError("Can't Load mapsource");
	}

	if (tileSprites != nullptr)
	{
		for (int y = 0; y < MapConst::MAP_SUBMAPS; ++y)
		{
			for (int x = 0; x < MapConst::MAP_SUBMAPS; ++x)
			{
				unsigned int tileBytes = GetTileSprBytes(x, y, tileSprites);
				_tilesSprs[y][x] = tileBytes;
			}
		}
	}
	else
	{
		Utils::LogError("Can't Load mapsprdata");
	}
}

MapTileVO *MapProxy::GetWayPointsByCamp()
{
	MapTileVO wayPoints[4];
	for (auto wayPoint : _wayPoints)
	{
		wayPoints[wayPoint->camp] = *wayPoint;
	}
	return wayPoints;
}

unsigned int MapProxy::GetTileBytes(int x, int y, unsigned char bytes[])
{
	int idx = y * MapConst::MAP_HEIGHT + x;
	unsigned int data = 0;
	data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[4 * idx + 3]) << 24);
	data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[4 * idx + 2]) << 16);
	data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[4 * idx + 1]) << 8);
	data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[4 * idx]) << 0);
	return data;
}

unsigned int MapProxy::GetTileSprBytes(int x, int y, unsigned char bytes[])
{
	int idx = y * MapConst::MAP_SUBMAPS + x;
	unsigned int data = 0;
	data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[4 * idx + 3]) << 24);
	data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[4 * idx + 2]) << 16);
	data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[4 * idx + 1]) << 8);
	data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[4 * idx]) << 0);
	return data;
}

MapTileVO *MapProxy::GetTile(int x, int y, unsigned char bytes[])
{
	unsigned int data = GetTileBytes(x, y, bytes);
	MapTileVO *re = MapTileVO::TileDecodeLocal(data, Coord(x, y));
	return re;
}

std::vector<MapTileVO*> MapProxy::GetWayPoints(unsigned char bytes[])
{
	std::vector<MapTileVO*> wayPoints = std::vector<MapTileVO*>();
	int idx = 4 * MapConst::MAP_HEIGHT * MapConst::MAP_WIDTH;
	int realBytesLen = MapConst::MAP_HEIGHT * MapConst::MAP_WIDTH * 4 + 4 * 4;
	while (idx + 3 < sizeof(bytes) / sizeof(bytes[0]) && idx + 3 < realBytesLen)
	{
		unsigned int data = 0;
		data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[idx]) << 0);
		data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[idx + 1]) << 8);
		data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[idx + 2]) << 16);
		data |= static_cast<unsigned int>(static_cast<unsigned int>(bytes[idx + 3]) << 24);
		wayPoints.push_back(MapTileVO::WayPointDecodeLocal(data));
		idx += 4;
	}
	return wayPoints;
}

MapTileVO *MapProxy::GetTile(int x, int y)
{
	if (x >= 0 && x < MapConst::MAP_WIDTH && y >= 0 && y < MapConst::MAP_HEIGHT)
	{
		return MapTileVO::TileDecodeLocal(_tiles[y][x], Coord(x, y));
	}
	else
	{
		return nullptr;
	}
}

std::vector<int> MapProxy::GetSprLists(Coord c)
{
	return GetSprLists(c.x, c.y);
}

std::vector<int> MapProxy::GetSprLists(int x, int y)
{
	if (x >= 0 && x < MapConst::MAP_SUBMAPS && y >= 0 && y < MapConst::MAP_SUBMAPS)
	{
		return MapTileVO::TileSprDecodeLocal(_tilesSprs[y][x]);
	}
	else
	{
		return std::vector<int>(0);
	}
}

MapTileVO *MapProxy::GetTile(Coord coord)
{
	return GetTile(coord.x, coord.y);
}

void MapProxy::SetVisibleBlocks(std::vector<Coord> &coords)
{
	visibleBlockIds.clear();
	for (auto c : coords)
	{
		visibleBlockIds.insert(static_cast<unsigned int>(c.y) * (MapConst::MAP_WIDTH / MapServerBlock::WIDTH) + static_cast<unsigned int>(c.x));
	}
}

void MapProxy::InitializeInstanceFields()
{
	visibleBlockIds = std::set<unsigned int>();
}
