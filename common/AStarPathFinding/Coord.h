#pragma once

#include <string>
#include <cmath>
#include <stdexcept>
#include "Utils.h"


class Coord
{
public:
	int x;
	int y;

	Coord();
	Coord(int ax, int ay);

	/// <summary>
	/// 用字符串创建坐标
	/// </summary>
	/// <param name="coordText">0,0</param>
	Coord(const std::string &coordText);

	bool operator < (Coord rhs);

	bool operator > (Coord rhs);

	bool operator == (Coord rhs);

	bool operator != (Coord rhs);

	std::string ToString();

	int GetHashCode();

	bool Near(Coord other, int measure);

	static Coord RandomMapCoord();

	Coord GetSubmapCoord();
};
