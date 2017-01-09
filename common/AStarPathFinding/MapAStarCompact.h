#pragma once

#include "Coord.h"
#include "MapConst.h"
#include "MinHeap.h"
#include <unordered_map>
#include <vector>
#include <algorithm>


class MapAStarCompact
{
private:
	std::vector<Coord> _waypoints[5][5];
	unsigned int _cellmasks[MapConst::MAP_WIDTH][MapConst::MAP_HEIGHT];
	std::unordered_map<unsigned int, float> _footprints;

public:
	void ResetContext();

	MapAStarCompact();

	std::vector<Coord> CalcPath(Coord src, Coord dst);

	static MapAStarCompact* GetInstance();

private:
	static MapAStarCompact* instance;

	float GetFootprintLen(unsigned int mask);

	void SetFootprintLen(unsigned int mask, float value);

	int ReversePredecessor(int p);

public:
	std::vector<Coord> CalcPathImp(Coord src, Coord dst);

private:
	void TouchNext(MinHeap<unsigned int> *opened, unsigned int curMask, unsigned int nextMask, int predecessor, bool adjacent);

	std::vector<Coord> ConstructPath(int dstX, int dstY);

	static int adjacentOffsetX[7];
	static int adjacentOffsetY[7];
	static int leapfrogOffsetX[7];
	static int leapfrogOffsetY[7];
	int NextX(int curX, int curY, int code, bool adjacent);
	int NextY(int curX, int curY, int code, bool adjacent);

	static const unsigned int ACTIVE_MASK = 0x00000001;
	static const unsigned int OPENED_MASK = 0x00000002;
	static const unsigned int PREDECESSOR_MASK = 0x70000000;
	static const unsigned int PREDECESSOR_TYPE_MASK = 0x80000000;
	static const unsigned int COORDX_MASK = 0x0FFC0000;
	static const unsigned int COORDY_MASK = 0x0003FF00;

	bool IsActive(unsigned int mask);

	unsigned int SetActiveMask(int x, int y, bool isActive);

	unsigned int SetActiveMask(unsigned int mask, bool isActive);

	unsigned int GetCellMask(int x, int y);

	void ExtractCoord(unsigned int mask, int &x, int &y);

	bool isOpened(unsigned int mask);

	unsigned int SetOpenMask(unsigned int mask, bool isOpen);

	unsigned int SetOpenMask(int x, int y, bool isOpen);

	unsigned int SetPredecessor(int x, int y, int p, bool adjacent);

	unsigned int SetPredecessor(unsigned int mask, int p, bool adjacent);

	int GetPredecessor(unsigned int mask, bool &adjacent);

	int GetPredecessor(int x, int y, bool &adjacent);

private:
	void InitializeInstanceFields();
};
