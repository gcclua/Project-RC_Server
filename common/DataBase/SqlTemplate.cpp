
#include "SqlTemplate.h"

/*
 *	角色基本信息
 */
const tchar*	LoadCharFullData	=  	"call load_char_info(%lld);";
const tchar*	UpdateCharFullData	=	"call update_char_info(%lld,\'%s\',\'%s\',%d,%d,%d,\'%s\',\'%s\',%d,%d,%d);";

const char*     LoadTileData = "call loadtile()";
const char*     UpdateTileData = "call ";

const tchar*	CreateChar			=	"call createchar(%lld,\'%s\',\'%s\',%d,%d)";

const tchar*    SaveGuidData		=	"call saveguid(%d,%lld)";

const tchar*	LoadCharList		=	"call loadcharlist(\'%s\')";
const tchar*	LoadRandomName		=	 "call loadrandomname()";

const tchar*    CreateCity          =  "call createcity(%lld,%lld,%d,%d,%d,%d,%lld,%lld,%lld,%lld);";
const tchar*    LoadCity            =  "call loadcity(%lld)";
const tchar*    UpdateCity          =  "call updatecity(lld,%d,%d,%d,%d,%lld,%lld,%lld,%lld)";

const tchar*    LoadBuilding        =  "call loadbuilding(%lld)";
const tchar*    UpdateBuilding      =  "call updatebuilding(%lld,%lld,%d,%d,%d);";
const tchar*    LoadMapMarch        =  "call LoadMapMarch()";

const tchar*    LoadMarch           =  "call loadcitymarch(%lld)";
const tchar*    UpdateMarch         =  "call updatemarch(%lld,%lld,%lld,%lld,%lld,%d,%d,%lld,%lld,%d);";

const tchar*    LoadHero            =  "call loadcityhero(%lld)";
const tchar*    UpdateHero          =  "call updatehero(%lld,%lld,%lld,%d,%d,%d,%d,%d,%d,%d,%d);";

const tchar*    UpdateTroop         =   "call updatetroop(%lld,%lld,%d,%d,%d,%d,%d)";
const tchar*    LoadMarchTroop      =   "call loadmarchtroop(%lld)";