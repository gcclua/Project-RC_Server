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
		bsvector<ObstacleFileItem> ofitemvec;	//��stl��
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

	CACHE_LOG("Scene","sceneclass("<<nSceneClassID<<") obstacle record begin");
	CACHE_LOG("Scene","width("<<m_nWidth<<"), height("<<m_nHeight<<"), scalewidth("<<m_nScaleWidth<<"), scaleheight("<<m_nScaleHeight<<")");

	FLString<1024> szBorderLine;
	for (int i = 0; i < (m_nScaleWidth + 2); i++)
	{
		szBorderLine += "#";
	}
	szBorderLine += "\t";
	CACHE_LOG("Scene",szBorderLine.GetCText());

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
		CACHE_LOG("Scene",szLine.GetCText());
	}

	CACHE_LOG("Scene",szBorderLine.GetCText());
	CACHE_LOG("Scene","sceneclass("<<nSceneClassID<<") obstacle record end");

	__LEAVE_FUNCTION
}

void SceneObstacle::SetObstacleValue(const ScenePos &rPos, int nValue)
{
	float fX = rPos.m_fX * OBSTACLESCALE;
	float fZ = rPos.m_fZ * OBSTACLESCALE;
	int nX = _45FLOAT2INT(fX);
	int nZ = _45FLOAT2INT(fZ);
	SetScaleObstacleValue(nX, nZ, nValue);
}

int SceneObstacle::GetObstacleValue(const ScenePos &rPos) const
{
	float fX = rPos.m_fX * OBSTACLESCALE;
	float fZ = rPos.m_fZ * OBSTACLESCALE;
	int nX = _45FLOAT2INT(fX);
	int nZ = _45FLOAT2INT(fZ);
	return GetScaleObstacleValue(nX, nZ);
}

void SceneObstacle::SetScaleObstacleValue(int nX, int nZ, int nValue)
{
	if ((nX >= 0 && nX < m_nScaleWidth) &&
		(nZ >= 0 && nZ < m_nScaleHeight))
	{
		int nIndex = m_nScaleWidth * nZ + nX;
		AssertEx(nIndex >= 0 && nIndex < static_cast<int>(m_Data.size()), "");
		m_Data[nIndex] = nValue;
	}
}

int SceneObstacle::GetScaleObstacleValue(int nX, int nZ) const
{
	if ((nX >= 0 && nX < m_nScaleWidth) &&
		(nZ >= 0 && nZ < m_nScaleHeight))
	{
		int nIndex = m_nScaleWidth * nZ + nX;
		AssertEx(nIndex >= 0 && nIndex < static_cast<int>(m_Data.size()), "");
		return m_Data[nIndex];
	}
	else
	{
		return ObstacleValue::INVALID;
	}
}