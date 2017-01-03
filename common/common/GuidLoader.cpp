#include "GuidLoader.h"
#include "Exception.h"
#include "ServerConfig.h"
#include "DataBase/ODBCInterface.h"
extern ServerConfig serverConfig;

enum GUIDLOAD_SEQ
{
	DB_TYPE =1,
	DB_SERIAL,
};

void LoadGUIDFromDB(GUIDInfo aInfo[], tint8 nLen )
{
	__ENTER_FUNCTION

	//��ѯ���
	const char* szLoadSql = "select type,serial from t_guid";

	//�ӿڶ���
	ODBCInterface* pFace = new ODBCInterface();
	AssertEx(pFace, "[GuidLoader]ODBC Init Fail!");

	//����Դ����
	tchar szDatabase[DATABASE_STR_LEN] = {0};
	strncpy(szDatabase, serverConfig.dbGamedName(1).c_str(), DATABASE_STR_LEN);
	szDatabase[DATABASE_STR_LEN - 1] = '\0';

	//�û�����
	tchar szUser[DB_USE_STR_LEN] = {0};
	strncpy(szUser, serverConfig.dbGamedUser(1).c_str(), DB_USE_STR_LEN);
	szUser[DB_USE_STR_LEN - 1] = '\0';

	//����
	tchar szPassword[DB_PASSWORD_STR_LEN] = {0};
	strncpy(szPassword, serverConfig.dbGamedPassword(1).c_str(), DB_PASSWORD_STR_LEN);
	szPassword[DB_PASSWORD_STR_LEN - 1] = '\0';

	CacheLog(LOGDEF_INST(DBAgent), "[GuidLoader]DB(%s),User(%s),Pwd(%s)",
		szDatabase, szUser, szPassword);

	//��ʼ����
	pFace->Connect(szDatabase, szUser, szPassword);
	AssertEx(pFace->IsConnected(), "[GuidLoader]Connect to DB Fail !");

	DB_QUERY& rQuery = pFace->GetQuery();
	rQuery.Clear();
	rQuery.Parse(szLoadSql);

	//׼����ѯ
	AssertEx(pFace->IsPrepare(), "[GuidLoader]Query Fail!");
	AssertEx(pFace->Execute(), "[GuidLoader]Execute Fail!" );

	//�����������
	tint64 nResultCount = pFace->mAffectCount;
	AssertEx(nResultCount == nLen, "[GuidLoader]ArrayCount != AffectCount");

	for (tint32 i = 0; i < nLen; ++i)
	{
		if (pFace->Fetch())
		{
			tint32 nError = 0;
			tint32 nValue1 = pFace->GetInt(DB_TYPE, nError);
			tuint32 uValue3 = pFace->GetUInt(DB_SERIAL, nError);

			AssertEx(nError == 0, "[GuidLoader]Fetch Fail!");
			AssertEx(nValue1 == i, "[GuidLoader]Wrong Type Found!");

			aInfo[i].m_Serial = uValue3;

			CacheLog(LOGDEF_INST(DBAgent), "[GuidLoader]Type(%d),Serial(%u)",
				nValue1,  uValue3);
		}
	}
	//׼���ر�
	pFace->Clear();
	AssertEx(pFace->Close(),"[GuidLoader]ODBC Close Fail!");

	if (pFace)
	{
		delete pFace;
	}
	__LEAVE_FUNCTION
}