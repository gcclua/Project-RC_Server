#ifndef _SQL_TEMPLATE_H_
#define _SQL_TEMPLATE_H_
#include "Base.h"


#define CHAR_TABLE		"t_char"
#define TILE_TABLE      "t_tile"

extern const char* LoadCharFullData;
extern const char* UpdateCharFullData;

extern const char*  LoadTileData;
extern const char*  UpdateTileData;
extern const tchar*	CreateChar;
extern const tchar*	SaveGuidData;
extern const tchar*	LoadCharList;
extern const tchar* LoadRandomName;

extern const tchar* CreateCity;
extern const tchar* LoadCity;
extern const tchar* UpdateCity;

extern const tchar* LoadBuilding;
extern const tchar* UpdateBuilding;

extern const tchar* LoadMarch;
extern const tchar* UpdateMarch;
extern const tchar* LoadMapMarch;

extern const tchar* LoadHero;
extern const tchar* UpdateHero;

extern const tchar* UpdateTroop;
extern const tchar* LoadMarchTroop;

extern const tchar* LoadTroopTrain;
extern const tchar* UpdateTroopTrain;

#endif