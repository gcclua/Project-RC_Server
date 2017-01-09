#include "MapTileVO.h"


MapTileVO::~MapTileVO()
{
	InitializeInstanceFields();
}

int MapTileVO::GetTileType()
{
	return static_cast<int>(type);
}

bool MapTileVO::IsWater()
{
	return type == MapTileType::Block && (blockType == MapBlockType::WaterWave || blockType == MapBlockType::WaterNormal);
}

bool MapTileVO::mDecodeTestMode = false;

unsigned int MapTileVO::WayPointEncodeLocal(MapTileVO *tile)
{
	unsigned int re = 0;
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->coord.x) << 16);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->coord.y) << 4);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->camp) << 0);
	return re;
}

MapTileVO *MapTileVO::WayPointDecodeLocal(unsigned int bin)
{
	MapTileVO *tile = new MapTileVO();
	tile->camp = static_cast<int>((bin & 0xf) >> 0);
	Coord coord = Coord();
	coord.y = static_cast<int>((bin & 0xfff0) >> 4);
	coord.x = static_cast<int>((bin & 0xfff0000) >> 16);
	tile->coord = coord;
	return tile;
}

unsigned int MapTileVO::TileEncodeLocal(MapTileVO *tile)
{
	// mat-height-TileType-TileCamp-TileCamp1-TileLevel-PvELevel-BlockType
	//  4b-  4b  -   4b   -   4b   -    4b   -   4b    -   4b   -   4b   
	unsigned int re = 0;
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->mat) << 28);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->height) << 24);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->type) << 20);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->camp) << 16);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->camp1) << 12);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->level) << 8);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->pveLevel) << 4);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(tile->blockType) << 0);
	return re;
}

MapTileVO *MapTileVO::TileDecodeLocal(unsigned int bin, Coord coord)
{
	// mat-height-TileType-TileCamp-TileCamp1-TileLevel-PvELevel-BlockType
	//  4b-  4b  -   4b   -   4b   -    4b   -   4b    -   4b   -   4b   
	MapTileVO *tile = new MapTileVO();
	if (mDecodeTestMode)
	{
		tile->mat = 1;
		tile->height = MapConst::MAP_HEIGHT_HORIZON;
		tile->type = MapTileType::Normal;
		tile->camp = 0;
		tile->camp1 = 0;
		tile->level = 0;
		tile->pveLevel = 0;
		tile->blockType = MapBlockType::None;
	}
	else
	{
		tile->mat = static_cast<unsigned char>((bin & 0xf0000000) >> 28);
		tile->height = static_cast<unsigned char>((bin & 0xf000000) >> 24);
		tile->type = static_cast<MapTileType>(static_cast<int>((bin & 0xf00000) >> 20));
		tile->camp = static_cast<int>((bin & 0xf0000) >> 16);
		tile->camp1 = static_cast<int>((bin & 0xf000) >> 12);
		tile->level = static_cast<int>((bin & 0xf00) >> 8);
		tile->pveLevel = static_cast<int>((bin & 0xf0) >> 4);
		tile->blockType = static_cast<MapBlockType>(static_cast<int>((bin & 0xf) >> 0));
	}
	tile->coord = coord;
	return tile;
}

unsigned int MapTileVO::TileSprEncodeLocal(std::vector<int> &sprs)
{
	// spr1-spr2-spr3-spr4
	//  8b - 8b - 8b - 8b
	unsigned int re = 0;
	re |= static_cast<unsigned int>(static_cast<unsigned int>(sprs[0]) << 24);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(sprs[1]) << 16);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(sprs[2]) << 8);
	re |= static_cast<unsigned int>(static_cast<unsigned int>(sprs[3]) << 0);
	return re;
}

std::vector<int> MapTileVO::TileSprDecodeLocal(unsigned int bin)
{
	// spr1-spr2-spr3-spr4
	//  8b - 8b - 8b - 8b
	std::vector<int> ret = std::vector<int>(4);
	if (mDecodeTestMode)
	{
		ret.push_back(0);
		ret.push_back(1);
		ret.push_back(2);
		ret.push_back(3);
	}
	else
	{
		ret.push_back(static_cast<int>((bin & 0xff000000) >> 24));
		ret.push_back(static_cast<int>((bin & 0xff0000) >> 16));
		ret.push_back(static_cast<int>((bin & 0xff00) >> 8));
		ret.push_back(static_cast<int>((bin & 0xff) >> 0));
	}
	return ret;
}

Color *MapTileVO::ColorDecode(unsigned short bin)
{
	Color *re = new Color();
	re->r = ((bin & std::stoi("1111100000000000", nullptr, 2)) >> 11) / 31.0f;
	re->g = ((bin & std::stoi("0000011111000000", nullptr, 2)) >> 6) / 31.0f;
	re->b = ((bin & std::stoi("0000000000111110", nullptr, 2)) >> 1) / 31.0f;
	re->a = 1.0f;
	return re;
}

unsigned short MapTileVO::ColorEncode(Color color)
{
	//Utils::Log("");
	int r = Utils::Clamp(static_cast<int>(std::round(color.r * 31)), 0, 31);
	//int g = Utils::Clamp(static_cast<int>(std::round(color.g * 31)), 0, 31);
	//int b = Utils::Clamp(static_cast<int>(std::round(color.b * 31)), 0, 31);
	return 0;
	//return static_cast<unsigned short>((r << 11) | (g << 6) | (b << 1));
}

const int tempVector[] = { 0, 1, 2, 3, 4 };
const std::vector<int> MapTileVO::OpenedCamp = std::vector<int>(tempVector, tempVector + sizeof(tempVector) / sizeof(tempVector[0]));
const std::string MapTileVO::CampName[4] = { "north", "west", "east", "south" };

std::string MapTileVO::Camp2String(int camp)
{
	if (camp >= 0 && camp < 4)
	{
		return CampName[camp];
	}
	else
	{
		Utils::Log(std::string("camp = ") + std::to_string(camp));
		return "north";
	}
}

void MapTileVO::InitializeInstanceFields()
{
	mat = 0;
	height = 0;
	type = (MapTileType)0;
	blockType = (MapBlockType)0;
	camp = 0;
	level = 0;
	pveLevel = 0;
	camp1 = 0;
}
