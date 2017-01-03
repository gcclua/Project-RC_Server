#include "GuidDefine.h"
#include "GuidLoader.h"

//添加新的Guid生成器，需要修改数据库
STATIC_ASSERT(GuidType::MAX == 6);

GUIDDEF_IMPL(Char);
GUIDDEF_IMPL(City);
GUIDDEF_IMPL(Building);
GUIDDEF_IMPL(Hero);
GUIDDEF_IMPL(March);
GUIDDEF_IMPL(Troop);

void InitGuidModule(  )
{
	__ENTER_FUNCTION

	GUIDInfo guidinfo[GuidType::MAX];
	for (tint32 i = 0; i < GuidType::MAX; i++)
	{
		guidinfo[i].m_Serial = 0xffffffff;
	}
	LoadGUIDFromDB(guidinfo, GuidType::MAX);
	for (tint32 i = 0; i < GuidType::MAX; i++)
	{
		AssertEx(guidinfo[i].m_Serial != 0xffffffff, "");
	}

	GUIDDEF_INIT(Char,	    GuidType::CHAR,			guidinfo[GuidType::CHAR].m_Serial);
	GUIDDEF_INIT(City,	    GuidType::CITY,		    guidinfo[GuidType::CITY].m_Serial);
	GUIDDEF_INIT(Building,	GuidType::BUILDING,		guidinfo[GuidType::BUILDING].m_Serial);
	GUIDDEF_INIT(Hero,	    GuidType::HERO,		    guidinfo[GuidType::HERO].m_Serial);
	GUIDDEF_INIT(March,	    GuidType::MARCH,		guidinfo[GuidType::MARCH].m_Serial);
	GUIDDEF_INIT(Troop,	    GuidType::TROOP,		guidinfo[GuidType::TROOP].m_Serial);

	__LEAVE_FUNCTION
}
