#pragma once

#include "Utils.h"
#include "Coord.h"
#include <vector>


class MapLayout
{
public:
	enum class Direction
	{
		BottomLeft,
		Left,
		TopLeft,
		TopRight,
		Right,
		BottomRight,
		Count
	};

public:
	class VisibleArea
	{
	public:
		float near;
		float far;
		float nearHalfWidth;
		float farHalfWidth;

	private:
		void InitializeInstanceFields();

public:
		VisibleArea()
		{
			InitializeInstanceFields();
		}
	};

public:
	static const float Sqrt3;

private:
	float _hexEdgeLen;
	Vector3 *_hexVertices;
	Vector2 *_hexUvs;
	int *_triangles;

	float _offsetX;
	float _offsetZ;
	float _stepX;
	float _stepZ;

	/// 
	/// 3 /\ 
	/// 2 || 4
	/// 1 \/ 5
	///   0
public:
	MapLayout(float hexEdgeLen);

	static Coord NearBy(Coord coord, Direction dxt);

	static Coord Left(Coord c);
	static Coord Right(Coord c);
	static Coord TopLeft(Coord c);
	static Coord TopRight(Coord c);
	static Coord BottomLeft(Coord c);
	static Coord BottomRight(Coord c);

	static std::vector<Coord> Nearby(Coord c);

	Vector3 HexCenter(Coord coord);

	const float &getHexEdgeLen() const;

	const float &getHexTileWidth() const;

	const float &getHexTileHeight() const;

	Vector3 *getHexVertices() const;

	Vector2 *getHexUvs() const;

	int *getTriangles() const;


private:
	void InitializeInstanceFields();
};
