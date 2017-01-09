#include "Coord.h"
#include "MapConst.h"
#include <allocators>


Coord::Coord()
{
	x = 0;
	y = 0;
}

Coord::Coord(int ax, int ay)
{
	x = ax;
	y = ay;
}

Coord::Coord(const std::string &coordText)
{
	std::vector<std::string> value = Utils::Split(coordText, ',');

	try
	{
		if (value.size() != 2)
		{
			throw;
		}

		x = std::stoi(value[0]);
		y = std::stoi(value[1]);
	}
	catch (std::exception e)
	{
		std::stringstream errMsg;
		errMsg << "Error Coord Input : " << coordText;
		throw std::exception(errMsg.str().c_str());
	}
}

bool Coord::operator < (Coord rhs)
{
	if (this->x != rhs.x)
	{
		return (this->x < rhs.x);
	}
	else
	{
		return (this->y < rhs.y);
	}
}

bool Coord::operator > (Coord rhs)
{
	if (*this != rhs)
	{
		return !(*this < rhs);
	}
	return false;
}

bool Coord::operator == (Coord rhs)
{
	return this->x == rhs.x && this->y == rhs.y;
}

bool Coord::operator != (Coord rhs)
{
	return (this->x != rhs.x || this->y != rhs.y);
}

std::string Coord::ToString()
{
	return std::string(std::to_string(x) + ", " + std::to_string(y));
}

int Coord::GetHashCode()
{
	//return this.x.GetHashCode () ^ this.y.GetHashCode () << 2 ^ this.z.GetHashCode () >> 2;
	return (x << 16 + y);
}

bool Coord::Near(Coord other, int measure)
{
	return (abs(x - other.x) + abs(y - other.y) < measure);
}

Coord Coord::RandomMapCoord()
{
	Coord re = Coord();
	re.x = rand() % MapConst::MAP_WIDTH;
	re.y = rand() % MapConst::MAP_HEIGHT;
	return re;
}

Coord Coord::GetSubmapCoord()
{
	Coord submapCoord = Coord();
	submapCoord.x = static_cast<int>(floor(static_cast<float>(x / MapConst::MAP_TILES_PER_SUB)));
	submapCoord.y = static_cast<int>(floor(static_cast<float>(y / MapConst::MAP_TILES_PER_SUB)));
	return submapCoord;
}
