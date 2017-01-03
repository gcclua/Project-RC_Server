#ifndef _GAMESTRUCT_OBSTACLE_H_
#define _GAMESTRUCT_OBSTACLE_H_

#include "Base.h"
#include "GameDefine_Obstacle.h"
#include "Scene/GameStruct_Scene.h"

struct ObstacleFileHeader
{
	int	m_nWidth;
	int	m_nHeight;
};

struct ObstacleFileItem
{
	int	m_nX;
	int	m_nZ;
	int		m_nValue;
};

class SceneObstacle
{
public:
	SceneObstacle(void);
	~SceneObstacle(void);
private:
	SceneObstacle(const SceneObstacle &);
	SceneObstacle& operator=(const SceneObstacle &);

public:
	void Init(int nWidth, int nHeight);
	void Load(const char *szObstacleFileName);
	void Record(int nSceneClassID);

public:
	void SetObstacleValue(const ScenePos &rPos, int nValue);
	int GetObstacleValue(const ScenePos &rPos) const;
public:
	void SetScaleObstacleValue(int nX, int nZ, int nValue);
	int GetScaleObstacleValue(int nX, int nZ) const;

public:
	int GetWidth(void) const { return m_nWidth; }
	int GetHeight(void) const { return m_nHeight; }
private:
	int m_nWidth;
	int m_nHeight;
public:
	int GetScaleWidth(void) const { return m_nScaleWidth; }
	int GetScaleHeight(void) const { return m_nScaleHeight; }
private:
	int m_nScaleWidth;
	int m_nScaleHeight;
private:
	typedef bsvector<char> ObstacleData;
	ObstacleData m_Data;	//¡¾stl¡¿
};

#endif
