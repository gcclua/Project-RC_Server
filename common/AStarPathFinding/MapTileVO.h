#pragma once

#include "Coord.h"
#include "MapConst.h"
#include "Utils.h"
#include <string>
#include <vector>
#include <cmath>


/// <summary>
/// 地块数据结构
/// </summary>
class MapTileVO
{
	/// <summary>
	/// 坐标
	/// </summary>
public:
	Coord coord;
	/// <summary>
	/// 地表贴图
	/// </summary>
	unsigned char mat;
	/// <summary>
	/// 地表高度
	/// </summary>
	unsigned char height;
	/// <summary>
	/// 地块类型，标识地块行走、建城属性
	/// </summary>
	MapTileType type;
	/// <summary>
	/// 障碍物类型
	/// </summary>
	MapBlockType blockType;
	/// <summary>
	/// 区域索引
	/// </summary>
	int camp; // if block type is forest, specify the camp around the forest
	/// <summary>
	/// 区域等级
	/// </summary>
	int level;
	/// <summary>
	/// pve等级，暂时不用
	/// </summary>
	int pveLevel;
	/// <summary>
	/// 区域等级相关索引，暂时不用
	/// </summary>
	int camp1; // if block type is mountain, specify the camp at the other side of the mountain, 4 for neuatral

	~MapTileVO();

	int GetTileType();

	bool IsWater();

private:
	static bool mDecodeTestMode;
public:
	static unsigned int WayPointEncodeLocal(MapTileVO *tile);

	static MapTileVO *WayPointDecodeLocal(unsigned int bin);

	static unsigned int TileEncodeLocal(MapTileVO *tile);

	static MapTileVO *TileDecodeLocal(unsigned int bin, Coord coord);

	static unsigned int TileSprEncodeLocal(std::vector<int> &sprs);

	static std::vector<int> TileSprDecodeLocal(unsigned int bin);

	static Color *ColorDecode(unsigned short bin);

	static unsigned short ColorEncode(Color color);
	//	public const int MAP_CMAP_N = 0;
	//	public const int MAP_CMAP_W = 1;
	//	public const int MAP_CMAP_E = 2;
	//	public const int MAP_CMAP_S = 3;
	static const std::vector<int> OpenedCamp;
	static const std::string CampName[4];
	static std::string Camp2String(int camp);

private:
	void InitializeInstanceFields();

public:
	MapTileVO()
	{
		InitializeInstanceFields();
	}
};
