#pragma once

class MapConst
{
public:
	static const int MAP_WIDTH = 1024;
	static const int MAP_HEIGHT = 1024;

	static const int MAP_SUBMAPS = 64;
	static const int MAP_TILES_PER_SUB = 16;

	/// <summary>
	/// ��ͼ��λ�߶ȣ�����1�߶����߻������ݶ�����
	/// </summary>
	static const float MAP_HEIGHT_UNIT;
	static const unsigned char MAP_HEIGHT_HORIZON = 8;
};

enum class MapTileType
{
	Normal = 0, // �����ߣ��ɽ���
	Block = 1, // �������ߣ����ɽ���
	Walkable = 2 // �����ߣ����ɽ���
};

enum class MapBlockType
{
	None = 0,
	Mountain = 1,
	Forest = 2,
	WaterWave = 3,
	WaterNormal = 4
};

enum class CampType
{
	CAMP_TYPE_N = 0,

	CAMP_TYPE_W = 1,

	CAMP_TYPE_E = 2,

	CAMP_TYPE_S = 3,

	CAMP_TYPE_NEUTRAL = 4
};
