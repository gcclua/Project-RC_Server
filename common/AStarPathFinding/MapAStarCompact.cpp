#include "MapAStarCompact.h"
#include "MapProxy.h"
#include "MapTileVO.h"
#include "MapLayout.h"
#include "Utils.h"
#include <functional>

MapAStarCompact* MapAStarCompact::instance;

void MapAStarCompact::ResetContext()
{
std:memset(_cellmasks, 0, sizeof(_cellmasks));
	_footprints.clear();
}

MapAStarCompact::MapAStarCompact()
{
	InitializeInstanceFields();
	auto waypointTiles = MapProxy::GetInstance()->GetWayPointsByCamp();
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i == j)
			{
				continue;
			}
			if (_waypoints[i][j].empty())
			{
				_waypoints[i][j] = std::vector<Coord>();
			}
			if (i != 4)
			{
				_waypoints[i][j].push_back(waypointTiles[i].coord);
			}
			if (j != 4)
			{
				_waypoints[i][j].push_back(waypointTiles[j].coord);
			}
		}
	}
}

std::vector<Coord> MapAStarCompact::CalcPath(Coord src, Coord dst)
{
	bool reverse = dst < src;
	if (reverse)
	{
		Coord temp = src;
		src = dst;
		dst = temp;
	}
	MapTileVO *srcTile = MapProxy::GetInstance()->GetTile(src);
	MapTileVO *dstTile = MapProxy::GetInstance()->GetTile(dst);
	int srcCamp = srcTile->camp;
	int dstCamp = dstTile->camp;

	std::vector<Coord> transitions = std::vector<Coord>();
	transitions.push_back(src);
	if (_waypoints[srcCamp][dstCamp].size() > 0)
	{
		transitions.insert(transitions.end(), _waypoints[srcCamp][dstCamp].begin(), _waypoints[srcCamp][dstCamp].end());
	}
	transitions.push_back(dst);

	std::vector<Coord> paths = std::vector<Coord>();
	// merge transitions near each other
	while (transitions.size() > 2)
	{
		bool merged = false;
		for (int i = 0; i + 1 < transitions.size(); ++i)
		{
			if (transitions[i].Near(transitions[i + 1], 100))
			{
				if (i + 1 == transitions.size() - 1)
				{
					// the last transition
					merged = true;
					transitions.erase(transitions.begin() + i);
					break;
				}
				else
				{
					merged = true;
					transitions.erase(transitions.begin() + i + 1);
					break;
				}
			}
		}
		if (!merged)
		{
			break;
		}
	}
	for (int i = 0; i + 1 < transitions.size(); ++i)
	{
		auto subPath = CalcPathImp(transitions[i], transitions[i + 1]);
		if (subPath.size() > 0)
		{
			paths.insert(paths.end(), subPath.begin(), subPath.end());
		}
		else
		{
			paths.clear();
			break;
		}
	}
	ResetContext();
	if (reverse)
	{
		std::reverse(paths.begin(), paths.end());
	}
	return paths;
}

MapAStarCompact* MapAStarCompact::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new MapAStarCompact();
	}
	return instance;
}

float MapAStarCompact::GetFootprintLen(unsigned int mask)
{
	unsigned int key = 0;
	key |= (mask & COORDX_MASK);
	key |= (mask & COORDY_MASK);
	return _footprints[key];
}

void MapAStarCompact::SetFootprintLen(unsigned int mask, float value)
{
	unsigned int key = 0;
	key |= (mask & COORDX_MASK);
	key |= (mask & COORDY_MASK);
	if (_footprints.find(key) != _footprints.end())
	{
		_footprints[key] = value;
	}
	else
	{
		_footprints.insert(std::make_pair(key, value));
	}
}

int MapAStarCompact::ReversePredecessor(int p)
{
	p = (p + 3) % 6;
	p = (0 == p) ? 6 : p;
	return p;
}

std::vector<Coord> MapAStarCompact::CalcPathImp(Coord src, Coord dst)
{
	ResetContext();

	auto sharedLayout = new MapLayout(1.0f / 1.732f);
	std::function<float(int, int)> distanceCalculator = [&](int x, int y)
	{
		return (sharedLayout->HexCenter(Coord(x, y)) - sharedLayout->HexCenter(dst)).getmagnitude();
	};

	MinHeap<unsigned int> *opened = new MinHeap<unsigned int>([&](unsigned int lhr, unsigned int rhr)
	{
		int lhr_x = 0, lhr_y = 0, rhr_x = 0, rhr_y = 0;
		ExtractCoord(lhr, lhr_x, lhr_y);
		ExtractCoord(rhr, rhr_x, rhr_y);
		auto lhr_dis = GetFootprintLen(lhr) + distanceCalculator(lhr_x, lhr_y);
		auto rhr_dis = GetFootprintLen(rhr) + distanceCalculator(rhr_x, rhr_y);
		return lhr_dis < rhr_dis;
	});

	std::function<bool(int, int, int)> adjacentChecker = [&](int x, int y, int radition)
	{
		MapTileVO *tileVO = MapProxy::GetInstance()->GetTile(NextX(x, y, radition, true), NextY(x, y, radition, true));
		return (tileVO != nullptr && tileVO->type != MapTileType::Block);
	};

	std::function<bool(int, int, int)> leapfrogChecker = [&](int x, int y, int leap)
	{
		int p1 = (leap + 4) % 6;
		p1 = (0 == p1) ? 6 : p1;
		int p2 = (leap + 5) % 6;
		p2 = (0 == p2) ? 6 : p2;

		return adjacentChecker(NextX(x, y, leap, false), NextY(x, y, leap, false), 0) && adjacentChecker(x, y, p1) && adjacentChecker(x, y, p2);
	};

	if(!Utils::Assert(adjacentChecker(dst.x, dst.y, 0), "Destination is a block."))
	{
		return std::vector<Coord>(0);
	}
	SetActiveMask(src.x, src.y, true);
	opened->Insert(GetCellMask(src.x, src.y));
	SetOpenMask(src.x, src.y, true);
	SetFootprintLen(GetCellMask(src.x, src.y), 0.0f);

	while (opened->getHeapLen() > 0)
	{
		unsigned int curMask = opened->ExtractMin();
		int curX = 0, curY = 0;
		ExtractCoord(curMask, curX, curY);

		for (int i = 1; i <= 6; ++i)
		{
			int adjacentX = NextX(curX, curY, i, true);
			int adjacentY = NextY(curX, curY, i, true);
			if (adjacentX < 0 || adjacentX >= MapConst::MAP_WIDTH || adjacentY < 0 || adjacentY >= MapConst::MAP_HEIGHT)
			{
				continue;
			}
			unsigned int adjacentMask = GetCellMask(adjacentX, adjacentY);
			if (IsActive(adjacentMask) && !isOpened(adjacentMask))
			{
				continue;
			}
			if (adjacentX == dst.x && adjacentY == dst.y)
			{
				curMask = SetPredecessor(adjacentX, adjacentY, ReversePredecessor(i), true);
				return ConstructPath(adjacentX, adjacentY);
			}
			if (!adjacentChecker(curX, curY, i))
			{
				continue;
			}
			TouchNext(opened, curMask, GetCellMask(adjacentX, adjacentY), ReversePredecessor(i), true);
		}

		for (int i = 1; i <= 6; ++i)
		{
			int leapfrogX = NextX(curX, curY, i, false);
			int leapfrogY = NextY(curX, curY, i, false);
			if (leapfrogX < 0 || leapfrogX >= MapConst::MAP_WIDTH || leapfrogY < 0 || leapfrogY >= MapConst::MAP_HEIGHT)
			{
				continue;
			}
			unsigned int leapfrogMask = GetCellMask(leapfrogX, leapfrogY);
			if (IsActive(leapfrogMask) && !isOpened(leapfrogMask))
			{
				continue;
			}
			if (leapfrogX == dst.x && leapfrogY == dst.y)
			{
				curMask = SetPredecessor(leapfrogX, leapfrogY, ReversePredecessor(i), false);
				return ConstructPath(leapfrogX, leapfrogY);
			}
			if (!leapfrogChecker(curX, curY, i))
			{
				continue;
			}
			TouchNext(opened, curMask, GetCellMask(leapfrogX, leapfrogY), ReversePredecessor(i), false);
		}
		curMask = SetOpenMask(curMask, false);
	}

	return std::vector<Coord>(0);
}

void MapAStarCompact::TouchNext(MinHeap<unsigned int> *opened, unsigned int curMask, unsigned int nextMask, int predecessor, bool adjacent)
{
	bool check1 = false;
	int check2 = GetPredecessor(curMask, check1);
	auto distance = adjacent ? 1.0f : 1.732f;
	if (check1 == adjacent && check2 == predecessor)
	{
		distance *= 0.8f;
	}
	if (!IsActive(nextMask))
	{
		nextMask = SetActiveMask(nextMask, true);
		nextMask = SetOpenMask(nextMask, true);
		nextMask = SetPredecessor(nextMask, predecessor, adjacent);
		SetFootprintLen(nextMask, GetFootprintLen(curMask) + distance);
		opened->Insert(nextMask);
	}
	else if (isOpened(nextMask))
	{
		if (GetFootprintLen(nextMask) > (GetFootprintLen(curMask) + distance))
		{
			SetFootprintLen(nextMask, GetFootprintLen(curMask) + distance);
			nextMask = SetPredecessor(nextMask, predecessor, adjacent);
			opened->Heapify();
		}
	}
}

std::vector<Coord> MapAStarCompact::ConstructPath(int dstX, int dstY)
{
	unsigned int curMask = GetCellMask(dstX, dstY);
	std::vector<Coord> ret = std::vector<Coord>();
	std::vector<bool> tmp = std::vector<bool>();
	ret.push_back(Coord(dstX, dstY));
	bool adjacent = false;
	int predecessor = 0;
	do
	{
		int curX, curY;
		ExtractCoord(curMask, curX, curY);
		predecessor = GetPredecessor(curMask, adjacent);
		if (predecessor != 0)
		{
			int prevX = NextX(curX, curY, predecessor, adjacent);
			int prevY = NextY(curX, curY, predecessor, adjacent);
			curMask = GetCellMask(prevX, prevY);
			ret.push_back(Coord(prevX, prevY));
			tmp.push_back(adjacent);
		}
	} while (predecessor > 0);
	std::reverse(ret.begin(), ret.end());
	return ret;
}

int MapAStarCompact::adjacentOffsetX[7] = { 0, -1, -1, 0, 1, 0, -1 };
int MapAStarCompact::adjacentOffsetY[7] = { 0, 0, -1, -1, 0, 1, 1 };
int MapAStarCompact::leapfrogOffsetX[7] = { 0, 0, -2, -2, 0, 1, 1 };
int MapAStarCompact::leapfrogOffsetY[7] = { 0, 2, 1, -1, -2, -1, 1 };

int MapAStarCompact::NextX(int curX, int curY, int code, bool adjacent)
{
	if (0 == code)
	{
		return curX;
	}
	if (adjacent)
	{
		int ret = curX + adjacentOffsetX[code];
		if (0 == (curY % 2) && 0 != adjacentOffsetY[code])
		{
			ret += 1;
		}
		return ret;
	}
	else
	{
		int ret = curX + leapfrogOffsetX[code];
		if (0 == (curY % 2) && 0 != leapfrogOffsetX[code])
		{
			ret += 1;
		}
		return ret;
	}
}

int MapAStarCompact::NextY(int curX, int curY, int code, bool adjacent)
{
	if (0 == code)
	{
		return curY;
	}
	if (adjacent)
	{
		return curY + adjacentOffsetY[code];
	}
	else
	{
		return curY + leapfrogOffsetY[code];
	}
}

bool MapAStarCompact::IsActive(unsigned int mask)
{
	return (mask & ACTIVE_MASK) > 0;
}

unsigned int MapAStarCompact::SetActiveMask(int x, int y, bool isActive)
{
	unsigned int tmp = _cellmasks[x][y];
	tmp &= ~ACTIVE_MASK;
	if (isActive)
	{
		tmp |= ACTIVE_MASK;
	}
	_cellmasks[x][y] = tmp;
	return tmp;
}

unsigned int MapAStarCompact::SetActiveMask(unsigned int mask, bool isActive)
{
	int x = 0, y = 0;
	ExtractCoord(mask, x, y);
	return SetActiveMask(x, y, isActive);
}

unsigned int MapAStarCompact::GetCellMask(int x, int y)
{
	unsigned int tmp = _cellmasks[x][y];
	tmp |= static_cast<unsigned int>(x << 18);
	tmp |= static_cast<unsigned int>(y << 8);
	_cellmasks[x][y] = tmp;
	return tmp;
}

void MapAStarCompact::ExtractCoord(unsigned int mask, int &x, int &y)
{
	x = static_cast<int>((mask & COORDX_MASK) >> 18);
	y = static_cast<int>((mask & COORDY_MASK) >> 8);
}

bool MapAStarCompact::isOpened(unsigned int mask)
{
	return (mask & OPENED_MASK) > 0;
}

unsigned int MapAStarCompact::SetOpenMask(unsigned int mask, bool isOpen)
{
	int x = 0, y = 0;
	ExtractCoord(mask, x, y);
	return SetOpenMask(x, y, isOpen);
}

unsigned int MapAStarCompact::SetOpenMask(int x, int y, bool isOpen)
{
	unsigned int tmp = _cellmasks[x][y];
	tmp &= ~OPENED_MASK;
	if (isOpen)
	{
		tmp |= OPENED_MASK;
	}
	_cellmasks[x][y] = tmp;
	return tmp;
}

unsigned int MapAStarCompact::SetPredecessor(int x, int y, int p, bool adjacent)
{
	if (!adjacent)
	{
		int a = 0;
	}
	unsigned int tmp = _cellmasks[x][y];
	tmp &= ~PREDECESSOR_MASK;
	tmp |= (static_cast<unsigned int>(p) << 28);
	if (adjacent)
	{
		tmp &= ~PREDECESSOR_TYPE_MASK;
	}
	else
	{
		tmp |= PREDECESSOR_TYPE_MASK;
	}
	_cellmasks[x][y] = tmp;

	return tmp;
}

unsigned int MapAStarCompact::SetPredecessor(unsigned int mask, int p, bool adjacent)
{
	int x = 0, y = 0;
	ExtractCoord(mask, x, y);
	return SetPredecessor(x, y, p, adjacent);
}

int MapAStarCompact::GetPredecessor(unsigned int mask, bool &adjacent)
{
	adjacent = 0 == (mask & PREDECESSOR_TYPE_MASK);
	return static_cast<int>((mask & PREDECESSOR_MASK) >> 28);
}

int MapAStarCompact::GetPredecessor(int x, int y, bool &adjacent)
{
	return GetPredecessor(GetCellMask(x, y), adjacent);
}

void MapAStarCompact::InitializeInstanceFields()
{
	_footprints = std::unordered_map<unsigned int, float>();
}
