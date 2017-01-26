#include "GameStruct_Obstacle.h"

STATIC_ASSERT(sizeof(ObstacleFileHeader) == 8);
STATIC_ASSERT(sizeof(ObstacleFileItem) == 12);

SceneObstacle::SceneObstacle(void)
{
	
}

SceneObstacle::~SceneObstacle(void)
{

}

void SceneObstacle::Init(int nWidth, int nHeight)
{
	__ENTER_FUNCTION

	m_nWidth = nWidth;
	AssertEx(m_nWidth > 0 && m_nWidth < 1000, "");
	m_nHeight = nHeight;
	AssertEx(m_nHeight > 0 && m_nHeight < 1000, "");

	m_nScaleWidth = m_nWidth * OBSTACLESCALE + 1;
	m_nScaleHeight = m_nHeight * OBSTACLESCALE + 1;

	m_Data.resize(m_nScaleWidth * m_nScaleHeight, ObstacleValue::WALKABLE);

	__LEAVE_FUNCTION
}

void SceneObstacle::Load(const char *szObstacleFileName)
{
	__ENTER_PROTECT
		return;
	AssertEx(szObstacleFileName != null_ptr, "");
	int nObstacleFileNameLength = static_cast<int>(strlen(szObstacleFileName));
	if (nObstacleFileNameLength > 0)
	{
		//////////////////////////////////////////////////////////////////////////
		AssertEx(IsFileExists(szObstacleFileName), szObstacleFileName);

		FILE *fp = fopen(szObstacleFileName, "rb");
		AssertEx(fp != null_ptr, szObstacleFileName);

		//////////////////////////////////////////////////////////////////////////
		int nForecastFileLength = sizeof(ObstacleFileHeader) +
			sizeof(ObstacleFileItem) * (m_nScaleWidth * m_nScaleHeight);

		fseek(fp, 0, SEEK_END);
		int nFileLength = ftell(fp);

		AssertEx(nForecastFileLength == nFileLength, szObstacleFileName);

		//////////////////////////////////////////////////////////////////////////
		fseek(fp, 0, SEEK_SET);

		ObstacleFileHeader ofheader;
		fread(&ofheader, sizeof(ObstacleFileHeader), 1, fp);

		AssertEx(m_nWidth == ofheader.m_nWidth, szObstacleFileName);
		AssertEx(m_nHeight == ofheader.m_nHeight, szObstacleFileName);

		//////////////////////////////////////////////////////////////////////////
		bsvector<ObstacleFileItem> ofitemvec;	//¡¾stl¡¿
		ofitemvec.resize(m_nScaleWidth * m_nScaleHeight);
		fread(&(ofitemvec[0]), sizeof(ObstacleFileItem), m_nScaleWidth * m_nScaleHeight, fp);
		for (int i = 0; i < static_cast<int>(ofitemvec.size()); i++)
		{
			SetObstacleValue(ScenePos(ofitemvec[i].m_fX, ofitemvec[i].m_fZ),
				ofitemvec[i].m_nValue == 1 ? ObstacleValue::WALKABLE : ObstacleValue::WALKDISABLE);
		}

		//////////////////////////////////////////////////////////////////////////
		fclose(fp);
	}
	
	__LEAVE_PROTECT
}

void SceneObstacle::Record(int nSceneClassID)
{
	__ENTER_FUNCTION

	CacheLog(LOGDEF_INST(Scene), "sceneclass(%d) obstacle record begin", nSceneClassID);

	CacheLog(LOGDEF_INST(Scene), "width(%d), height(%d), scalewidth(%d), scaleheight(%d)",
		m_nWidth, m_nHeight, m_nScaleWidth, m_nScaleHeight);

	FLString<1024> szBorderLine;
	for (int i = 0; i < (m_nScaleWidth + 2); i++)
	{
		szBorderLine += "#";
	}
	szBorderLine += "\t";
	
	CacheLog(LOGDEF_INST(Scene), "%s", szBorderLine.GetCText());

	for (int i = (m_nScaleHeight - 1); i >= 0; i--)
	{
		FLString<1024> szLine;
		szLine += "#";

		for (int j = 0; j < m_nScaleWidth; j++)
		{
			int nValue = GetScaleObstacleValue(j, i);
			szLine += (nValue == ObstacleValue::WALKABLE ? " " : "&");
		}

		szLine += "#";
		szLine += "\t";
		
		CacheLog(LOGDEF_INST(Scene), "%s", szLine.GetCText());
	}

	CacheLog(LOGDEF_INST(Scene), "%s", szBorderLine.GetCText());

	CacheLog(LOGDEF_INST(Scene), "sceneclass(%d) obstacle record end", nSceneClassID);

	__LEAVE_FUNCTION
}

void SceneObstacle::SetObstacleValue(const ScenePos &rPos, tint32 nValue)
{
	tfloat32 fX = rPos.m_fX * OBSTACLESCALE;
	tfloat32 fZ = rPos.m_fZ * OBSTACLESCALE;
	tint32 nX = _45FLOAT2INT(fX);
	tint32 nZ = _45FLOAT2INT(fZ);
	SetScaleObstacleValue(nX, nZ, nValue);
}

tint32 SceneObstacle::GetObstacleValue(const ScenePos &rPos) const
{
	tfloat32 fX = rPos.m_fX * OBSTACLESCALE;
	tfloat32 fZ = rPos.m_fZ * OBSTACLESCALE;
	tint32 nX = _45FLOAT2INT(fX);
	tint32 nZ = _45FLOAT2INT(fZ);
	return GetScaleObstacleValue(nX, nZ);
}

void SceneObstacle::SetScaleObstacleValue(tint32 nX, tint32 nZ, tint32 nValue)
{
	if ((nX >= 0 && nX < m_nScaleWidth) &&
		(nZ >= 0 && nZ < m_nScaleHeight))
	{
		tint32 nIndex = m_nScaleWidth * nZ + nX;
		AssertEx(nIndex >= 0 && nIndex < static_cast<tint32>(m_Data.size()), "");
		m_Data[nIndex] = nValue;
	}
}

tint32 SceneObstacle::GetScaleObstacleValue(tint32 nX, tint32 nZ) const
{
	if ((nX >= 0 && nX < m_nScaleWidth) &&
		(nZ >= 0 && nZ < m_nScaleHeight))
	{
		tint32 nIndex = m_nScaleWidth * nZ + nX;
		AssertEx(nIndex >= 0 && nIndex < static_cast<tint32>(m_Data.size()), "");
		return m_Data[nIndex];
	}
	else
	{
		return ObstacleValue::INVALID;
	}
}