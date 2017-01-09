#include "MapLayout.h"


void MapLayout::VisibleArea::InitializeInstanceFields()
{
	near = 0;
	far = 0;
	nearHalfWidth = 0;
	farHalfWidth = 0;
}

const float MapLayout::Sqrt3 = 1.7320508f;

MapLayout::MapLayout(float hexEdgeLen)
{
	InitializeInstanceFields();
	_hexEdgeLen = hexEdgeLen;
	_hexVertices = new Vector3[6]{
		Vector3(0, 0, -1.0f) * _hexEdgeLen,
		Vector3(-Sqrt3 / 2.0f, 0, -0.5f) * _hexEdgeLen,
		Vector3(-Sqrt3 / 2.0f, 0, 0.5f) * _hexEdgeLen,
		Vector3(0, 0, 1.0f) * _hexEdgeLen,
		Vector3(Sqrt3 / 2.0f, 0, 0.5f) * _hexEdgeLen,
		Vector3(Sqrt3 / 2.0f, 0, -0.5f) * _hexEdgeLen
	};

	_hexUvs = new Vector2[6]{
		Vector2(0, -1.0f),
		Vector2(-Sqrt3 / 2.0f, -0.5f),
		Vector2(-Sqrt3 / 2.0f, 0.5f),
		Vector2(0, 1.0f),
		Vector2(Sqrt3 / 2.0f, 0.5f),
		Vector2(Sqrt3 / 2.0f, -0.5f)
	};

	_triangles = new int[12]{0, 1, 5, 1, 4, 5, 1, 2, 4, 2, 3, 4};

	_offsetX = Sqrt3 / 2.0f * _hexEdgeLen;
	_offsetZ = _hexEdgeLen;
	// 以下两个值需要修改
	//_stepX = Sqrt3 * _hexEdgeLen;
	//_stepZ = 1.5f * _hexEdgeLen;
	// fixed
	_stepX = Sqrt3 * _hexEdgeLen + 0.5f;
	_stepZ = 1.5f * _hexEdgeLen + (Sqrt3 / 4);
}

Coord MapLayout::NearBy(Coord coord, Direction dxt)
{
	switch (dxt)
	{
		case Direction::BottomLeft:
			return BottomLeft(coord);

		case Direction::BottomRight:
			return BottomRight(coord);

		case Direction::Left:
			return Left(coord);

		case Direction::Right:
			return Right(coord);

		case Direction::TopLeft:
			return TopLeft(coord);

		case Direction::TopRight:
			return TopRight(coord);
	}
	return Coord();
}

Coord MapLayout::Left(Coord c)
{
	return Coord(c.x - 1, c.y);
}

Coord MapLayout::Right(Coord c)
{
	return Coord(c.x + 1, c.y);
}

Coord MapLayout::TopLeft(Coord c)
{
	return Coord((c.y & 0x1) == 0 ? c.x : c.x - 1, c.y + 1);
}

Coord MapLayout::TopRight(Coord c)
{
	return Coord((c.y & 0x1) == 0 ? c.x + 1 : c.x, c.y + 1);
}

Coord MapLayout::BottomLeft(Coord c)
{
	return Coord((c.y & 0x1) == 0 ? c.x : c.x - 1, c.y - 1);
}

Coord MapLayout::BottomRight(Coord c)
{
	return Coord((c.y & 0x1) == 0 ? c.x + 1 : c.x, c.y - 1);
}

std::vector<Coord> MapLayout::Nearby(Coord c)
{
	std::vector<Coord> re = std::vector<Coord>();
	re.push_back(Coord(c.x - 1, c.y));
	re.push_back(Coord(c.x + 1, c.y));
	re.push_back(Coord(c.x, c.y - 1));
	re.push_back(Coord(c.x, c.y + 1));

	int offset = (c.y & 0x1) == 0 ? 1 : -1;
	re.push_back(Coord(c.x + offset, c.y - 1));
	re.push_back(Coord(c.x + offset, c.y + 1));

	return re;
}

Vector3 MapLayout::HexCenter(Coord coord)
{
	Vector3 re = Vector3(coord.x * _stepX + _offsetX, 0, coord.y * _stepZ + _offsetZ);
	if ((coord.y & 0x1) == 0)
	{
		re.x += _stepX / 2.0f;
	}
	return re;
}

const float &MapLayout::getHexEdgeLen() const
{
	return _hexEdgeLen;
}

const float &MapLayout::getHexTileWidth() const
{
	return _stepX;
}

const float &MapLayout::getHexTileHeight() const
{
	return _stepZ;
}

Vector3 *MapLayout::getHexVertices() const
{
	return _hexVertices;
}

Vector2 *MapLayout::getHexUvs() const
{
	return _hexUvs;
}

int *MapLayout::getTriangles() const
{
	return _triangles;
}

void MapLayout::InitializeInstanceFields()
{
	_hexEdgeLen = 1.0f;
	_offsetX = 0;
	_offsetZ = 0;
	_stepX = 0;
	_stepZ = 0;
}
