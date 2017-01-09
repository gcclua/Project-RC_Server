#include "MapProxy.h"
#include <fstream>
#include "AStarHelper.h"

void AStarHelper::TestLoadMapData()
{
	std::ifstream tileFile("C:/Users/liangxiao/Desktop/mapuint16.bytes");
	std::string str;
	std::string tileStr;
	while (std::getline(tileFile, str))
	{
		tileStr += str;
		tileStr.push_back('\n');
	}
	tileFile.close();

	unsigned char *tileChars = new unsigned char[tileStr.size()];
	memcpy(tileChars, tileStr.c_str(), tileStr.size());

	std::ifstream tileSprFile("C:/Users/liangxiao/Desktop/mapsprdata.bytes");
	std::string str2;
	std::string tileSprStr;
	while (std::getline(tileSprFile, str2))
	{
		tileSprStr += str2;
		tileSprStr.push_back('\n');
	}
	tileSprFile.close();

	unsigned char* tileSprChars = new unsigned char[tileSprStr.size()];
	memcpy(tileSprChars, tileSprStr.c_str(), tileSprStr.size());

	MapProxy::GetInstance()->OnInit(tileChars, tileSprChars);
}

void AStarHelper::TestCalcPath()
{
	std::vector<Coord> result = MapAStarCompact::GetInstance()->CalcPathImp(Coord(1, 1), Coord(2, 2));

	for (auto item : result)
	{
		std::cout << item.ToString() << std::endl;
	}
}

