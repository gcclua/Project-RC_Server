
//********************************************
//	Ini ��غ���
//********************************************


#include "Ini.h"
#include <iostream>
#include <malloc.h>
#include <string.h>
////////////////////////////////////////////////
// ͨ�ýӿ�
////////////////////////////////////////////////

//��ʼ��
Ini::Ini()
{
	//__ENTER_FUNCTION

	m_lDataLen = 0;
	m_strData = NULL;
	IndexNum = 0;
	IndexList = NULL;

	//__LEAVE_FUNCTION
}

//��ʼ��
Ini::Ini( const char *filename )
{
	//__ENTER_FUNCTION

	m_lDataLen=0;
	m_strData=NULL;
	IndexNum=0;
	IndexList=NULL;
	memset( m_strFileName, 0, MAX_PATH1 ) ;
	memset( m_szValue, 0, MAX_INI_VALUE ) ;
	memset( m_szRet, 0, MAX_INI_VALUE) ;

	Open(filename);

	//__LEAVE_FUNCTION
}

//�����ͷ�
Ini::~Ini()
{
	//__ENTER_FUNCTION

	if( m_lDataLen != 0 )
	{
		SAFE_FREE( m_strData );
		m_lDataLen = 0;
	}

	if( IndexNum != 0 )
	{
		SAFE_DELETE_ARRAY( IndexList );
		IndexNum = 0;
	}

	//__LEAVE_FUNCTION
}

//�����ļ�
bool Ini::Open( const char *filename )
{
	//__ENTER_FUNCTION

	strncpy(m_strFileName, filename, MAX_PATH1-1);

	SAFE_FREE( m_strData );

	//��ȡ�ļ�����
	FILE* fp;
	fp = fopen(filename,"rb");
	if(fp == 0)
	{
		m_lDataLen = -1;
	}
	else
	{
		fseek( fp, 0L, SEEK_END );
		m_lDataLen	= ftell( fp );
		fclose(fp);
	}
	
	
	//�ļ�����
	if( m_lDataLen > 0 )
	{
		m_strData = (char*)malloc( (size_t)m_lDataLen ) ;
		//m_strData = new char[m_lDataLen];
		memset( m_strData, 0, m_lDataLen ) ;

		FILE *fp;
		fp=fopen(filename, "rb");
		//AssertEx( fp!=NULL, filename );
		fread(m_strData, m_lDataLen, 1, fp);		//������
		fclose(fp);

		//��ʼ������
		InitIndex();
		return true;
	}
	else	// �ļ�������
	{
		// �Ҳ����ļ�
		m_lDataLen=1;
		m_strData = (char*)malloc( (size_t)m_lDataLen ) ;
		//m_strData = new char[m_lDataLen];
		memset(m_strData, 0, 1);
		InitIndex();
	}

	return false;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//�ر��ļ�
void Ini::Close()
{
	//__ENTER_FUNCTION

	if( m_lDataLen != 0 )
	{
		SAFE_FREE( m_strData );
		m_lDataLen = 0;
	}

	if( IndexNum != 0 )
	{
		SAFE_DELETE_ARRAY( IndexList );
		IndexNum = 0;
	}

	//__LEAVE_FUNCTION
}

//д���ļ�
bool Ini::Save(char *filename)
{
	//__ENTER_FUNCTION

	if( filename==NULL )
	{
		filename=m_strFileName;
	}

	FILE *fp;
	fp=fopen(filename, "wb");
	//AssertEx( fp!=NULL, filename );

	fwrite(m_strData, m_lDataLen, 1, fp);
	fclose(fp);

	return true;

	//__LEAVE_FUNCTION

//	return false ;
}

//�����ļ�����
char *Ini::GetData()
{
	//__ENTER_FUNCTION

	return m_strData;

	//__LEAVE_FUNCTION
}

//����ļ�������
int Ini::GetLines(int cur)
{
	//__ENTER_FUNCTION

	int n=1;
	for(int i=0; i<cur; i++)
	{
		if( m_strData[i]=='\n' )
			n++;
	}
	return n;

	//__LEAVE_FUNCTION
}

//����ļ�������
int Ini::GetLines()
{
	//__ENTER_FUNCTION

	int		n = 0;
	int		i;
	for(i=0; i<m_lDataLen; i++)
	{
		if( m_strData[i]=='\n' )
			n++;
	}
	if(i>=m_lDataLen)
		return n+1;
	return n;

	//__LEAVE_FUNCTION
}

////////////////////////////////////////////////
// �ڲ�����
////////////////////////////////////////////////

//��������е�����λ��
void Ini::InitIndex()
{
	//__ENTER_FUNCTION

	IndexNum=0;

	for(int i=0; i<m_lDataLen; i++)
	{
		//�ҵ�
		if( m_strData[i]=='[' && ( m_strData[i-1]=='\n' || i==0 ) )
		{
			IndexNum++;
		}
	}

	//�����ڴ�
	SAFE_DELETE_ARRAY( IndexList );
	if( IndexNum>0 )
		IndexList=new int[IndexNum];
	int n=0;

	for(int i=0; i<m_lDataLen; i++)
	{
		if( m_strData[i]=='[' && ( m_strData[i-1]=='\n' || i==0 ) )
		{
			IndexList[n]=i+1;
			n++;
		}
	}

	//__LEAVE_FUNCTION
}

//����ָ������λ��
int Ini::FindIndex(char *string)
{
	//__ENTER_FUNCTION

	for(int i=0; i<IndexNum; i++)
	{
		char *str=ReadText( IndexList[i] );
		if( strcmp(string, str) == 0 )
		{
//			SAFE_FREE( str );
			return IndexList[i];
		}
//		SAFE_FREE( str );
	}
	return -1;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//����ָ�����ݵ�λ��
int Ini::FindData(int index, char *string)
{
	//__ENTER_FUNCTION

	int p=index;	//ָ��

	while(1)
	{
		p=GotoNextLine(p);
		char *name=ReadDataName(p);
		if( strcmp(string, name)==0 )
		{
			SAFE_DELETE_ARRAY( name );
			return p;
		}

		if ( name[0] == '[' )
		{
			SAFE_DELETE_ARRAY( name );
			return -1;
		}

		SAFE_DELETE_ARRAY( name );
		if( p>=m_lDataLen ) return -1;
	}
	return -1;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//����
int Ini::GotoNextLine(int p)
{
	//__ENTER_FUNCTION

	int i;
	for(i=p; i<m_lDataLen; i++)
	{
		if( m_strData[i]=='\n' )
			return i+1;
	}
	return i;

	//__LEAVE_FUNCTION
}

//��ָ��λ�ö�һ��������
char *Ini::ReadDataName(int &p)
{
	//__ENTER_FUNCTION

	char chr;
	char *Ret;
	int m=0;

	Ret=new char[256];
	memset(Ret, 0, 256);

	for(int i=p; i<m_lDataLen; i++)
	{
		chr = m_strData[i];

		//����
		if( chr == '\r' )
		{
			p=i+1;
			return Ret;
		}
		
		//����
		if( chr == '=' || chr == ';' )
		{
			p=i+1;
			return Ret;
		}
		
		Ret[m]=chr;
		m++;
	}
	return Ret;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//��ָ��λ�ö�һ�ַ���
char *Ini::ReadText(int p)
{
	//__ENTER_FUNCTION

	char chr;
	char *Ret;
	int n=p, m=0;

	int LineNum = GotoNextLine(p) - p + 1;
	Ret=(char*)m_szValue;//new char[LineNum];
	memset(Ret, 0, LineNum);

	for(int i=0; i<m_lDataLen-p; i++)
	{
		chr = m_strData[n];

		//����
		if( chr == ';' || chr == '\r' || chr == '\t' || chr == ']' )
		{
			//ShowMessage(Ret);
			return Ret;
		}
		
		Ret[m]=chr;
		m++;
		n++;
	}

	return Ret;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//����һ������
bool Ini::AddIndex(char *index)
{
	//__ENTER_FUNCTION

	char str[256];
	memset(str, 0, 256);
	int n=FindIndex(index);

	if( n == -1 )	//�½�����
	{
		sprintf(str,"\r\n[%s]\r\n",index);
		m_strData = (char *)realloc(m_strData, m_lDataLen+strlen(str));	//���·����ڴ�
		sprintf(&m_strData[m_lDataLen], "%s", str);
		m_lDataLen+=(long)(strlen(str));

		InitIndex();
		return true;
	}
	
	return false;	//�Ѿ�����

	//__LEAVE_FUNCTION

//	return 0 ;
}

//�ڵ�ǰλ�ü���һ������
bool Ini::AddData(int p, char *name, char *string)
{
	//__ENTER_FUNCTION

	char *str;
	int len=(int)(strlen(string));
	str=new char[len+256];
	memset(str, 0, len+256);
	sprintf(str,"%s=%s\r\n",name,string);
	len=(int)(strlen(str));

	p=GotoNextLine(p);	//����
	m_strData = (char *)realloc(m_strData, m_lDataLen+len);	//���·����ڴ�

	char *temp=new char[m_lDataLen-p];
	memcpy(temp, &m_strData[p], m_lDataLen-p);
	memcpy(&m_strData[p+len], temp, m_lDataLen-p);	//�Ѻ���İᵽĩβ
	memcpy(&m_strData[p], str, len);
	m_lDataLen+=len;

	SAFE_DELETE_ARRAY( temp );
	SAFE_DELETE_ARRAY( str );
	return true;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//�ڵ�ǰλ���޸�һ�����ݵ�ֵ
bool Ini::ModityData(int p, char *name, char *string)
{
	//__ENTER_FUNCTION

	int n=FindData(p, name);

	char *t=ReadText(n);
	p=n+(int)(strlen(t));
//	if( strlen(t)>0 ) free(t);

	int newlen=(int)(strlen(string));
	int oldlen=p-n;

	m_strData = (char *)realloc(m_strData, m_lDataLen+newlen-oldlen);	//���·����ڴ�

	char *temp=new char[m_lDataLen-p];
	memcpy(temp, &m_strData[p], m_lDataLen-p);
	memcpy(&m_strData[n+newlen], temp, m_lDataLen-p);			//�Ѻ���İᵽĩβ
	memcpy(&m_strData[n], string, newlen);
	m_lDataLen+=newlen-oldlen;

	SAFE_DELETE_ARRAY( temp );
	return true;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//��ָ���ƶ�����INDEX�����һ��
int Ini::GotoLastLine(char *index)
{
	//__ENTER_FUNCTION

	int n=FindIndex(index);
	n=GotoNextLine(n);
	while(1)
	{
		if( m_strData[n] == '\r' || m_strData[n] == EOF || m_strData[n] == -3 || m_strData[n] == ' ' || m_strData[n] == '/' || m_strData[n] == '\t' || m_strData[n] == '\n' )
		{
			return n;
		}
		else
		{
			n=GotoNextLine(n);
			if( n >= m_lDataLen ) return n;
		}
	}

	//__LEAVE_FUNCTION

//	return 0 ;
}

/////////////////////////////////////////////////////////////////////
// ����ӿ�
/////////////////////////////////////////////////////////////////////

//����ͨ��ʽ��һ�ַ�������
char *Ini::ReadText(char *index, char *name, char* str, int size)
{
	//__ENTER_FUNCTION

	char szTmp[512] ;
	memset( szTmp, 0, 512 ) ;
	sprintf( szTmp, "[%s][%s][%s]", m_strFileName, index, name ) ;

	int n=FindIndex(index);
	//AssertEx( n != -1, szTmp );

	if ( n == -1 )
		return NULL;

	int m=FindData(n, name);
	//AssertEx( m != -1, szTmp );
	if ( m == -1 )
		return NULL;

	char* ret = ReadText(m);
	strncpy( str, ret, size ) ;
	return ret ;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//����������ȡ
bool Ini::ReadTextIfExist(char *index, char *name, char* str, int size)
{
//__ENTER_FUNCTION

	int n = FindIndex(index);
	
	if( n == -1 )
		return false;

	int m = FindData(n, name);
	
	if( m == -1 )
		return false;

	char* ret = ReadText(m);
	strncpy( str, ret, size );
	return true;

//__LEAVE_FUNCTION

//	return false ;
}
	
//��ָ�����ж�һ�ַ���
char *Ini::ReadText(char *index, int lines, char* str, int size)
{
	//__ENTER_FUNCTION

	char szTmp[512] ;
	memset( szTmp, 0, 512 ) ;
	sprintf( szTmp, "[%s][%s][%d]", m_strFileName, index, lines ) ;


	int n=FindIndex(index);
	//AssertEx( n != -1, szTmp );

	//����ָ������
	n=GotoNextLine(n);
	for(int i=0; i<lines; i++)
	{
		if( n<m_lDataLen )
			n=GotoNextLine(n);
	}

	//������
	while( n<=m_lDataLen )
	{
		if( m_strData[n] == '=' )
		{
			n++;
			char* ret = ReadText(n);
			strncpy( str, ret, size ) ;
			return ret ;
		}
		if( m_strData[n] == '\r' )
		{
			return NULL;
		}
		n++;
	}

	return NULL;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//����ͨ��ʽ��һ����
int Ini::Readint(char *index, char *name)
{
	//__ENTER_FUNCTION

	char szTmp[512] ;
	memset( szTmp, 0, 512 ) ;
	sprintf( szTmp, "[%s][%s][%s]", m_strFileName, index, name ) ;

	int n=FindIndex(index);
	//AssertEx( n != -1, szTmp );

	int m=FindData(n, name);
	//AssertEx( m != -1, szTmp );

	char *str=ReadText(m);
	int ret=atoi(str);
//	free(str);
	return ret;

	//__LEAVE_FUNCTION

//	return 0 ;
}

bool Ini::ReadintIfExist(char *section, char *key, int& nResult)
{
//__ENTER_FUNCTION

	int n=FindIndex(section);

	if( n == -1 )
		return false;

	int m=FindData(n, key);

	if( m == -1 )
		return false;

	char *str=ReadText(m);
	nResult=atoi(str);
	return true;

//__LEAVE_FUNCTION

//	return false;
}

//��ָ�����ж�һ����
int Ini::Readint(char *index, int lines)
{
	//__ENTER_FUNCTION

	char szTmp[512] ;
	memset( szTmp, 0, 512 ) ;
	sprintf( szTmp, "[%s][%s][%d]", m_strFileName, index, lines ) ;

	int n=FindIndex(index);
	//AssertEx( n != -1, szTmp );

	//����ָ������
	n=GotoNextLine(n);
	for(int i=0; i<lines; i++)
	{
		if( n<m_lDataLen )
			n=GotoNextLine(n);
	}

	//������
	while( n<m_lDataLen )
	{
		if( m_strData[n] == '=' )
		{
			n++;
			char *str=ReadText(n);
			int ret=atoi(str);
//			free(str);
			return ret;
		}
		if( m_strData[n] == '\r' )
		{
			return ERROR_DATA;
		}
		n++;
	}

	return ERROR_DATA;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//��ָ�����ж�һ��������
char *Ini::ReadCaption(char *index, int lines, char* str, int size)
{
	//__ENTER_FUNCTION

	char szTmp[512] ;
	memset( szTmp, 0, 512 ) ;
	sprintf( szTmp, "[%s][%s][%d]", m_strFileName, index, lines ) ;

	int n=FindIndex(index);
	//AssertEx( n != -1, szTmp );

	//����ָ������
	n=GotoNextLine(n);
	for(int i=0; i<lines; i++)
	{
		if( n<m_lDataLen )
			n=GotoNextLine(n);
	}

	char* ret = ReadDataName(n);
	strncpy( str, ret, size ) ;
	return ret ;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//����ͨ��ʽдһ�ַ�������
bool Ini::Write(char *index, char *name, char *string)
{
	//__ENTER_FUNCTION

	int n=FindIndex(index);
	if( n == -1 )	//�½�����
	{
		AddIndex(index);
		n=FindIndex(index);
		n=GotoLastLine(index);
		AddData(n, name, string);	//�ڵ�ǰλ��n��һ������
		return true;
	}

	//��������
	int m=FindData(n, name);
	if( m==-1 )		//�½�����
	{
		n=GotoLastLine(index);
		AddData(n, name, string);	//�ڵ�ǰλ��n��һ������
		return true;
	}

	//��������
	ModityData(n, name, string);	//�޸�һ������

	return true;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//����ͨ��ʽдһ����
bool Ini::Write(char *index, char *name, int num)
{
	//__ENTER_FUNCTION

	char string[32];
	sprintf(string, "%d", num);

	int n=FindIndex(index);
	if( n == -1 )	//�½�����
	{
		AddIndex(index);
		n=FindIndex(index);
		n=GotoLastLine(index);
		AddData(n, name, string);	//�ڵ�ǰλ��n��һ������
		return true;
	}

	//��������
	int m=FindData(n, name);
	if( m==-1 )		//�½�����
	{
		n=GotoLastLine(index);
		AddData(n, name, string);	//�ڵ�ǰλ��n��һ������
		return true;
	}

	//��������
	ModityData(n, name, string);	//�޸�һ������

	return true;

	//__LEAVE_FUNCTION

//	return 0 ;
}

//��������������
int Ini::GetContinueDataNum(char *index)
{
	//__ENTER_FUNCTION

	int num=0;
	int n=FindIndex(index);
	n=GotoNextLine(n);
	while(1)
	{
		if( m_strData[n] == '\r' || m_strData[n] == EOF || m_strData[n] == -3 || m_strData[n] == ' ' || m_strData[n] == '/' || m_strData[n] == '\t' || m_strData[n] == '\n' )
		{
			return num;
		}
		else
		{
			num++;
			n=GotoNextLine(n);
			if( n >= m_lDataLen ) return num;
		}
	}

	//__LEAVE_FUNCTION

//	return 0 ;
}
//��ָ���ж�һ�ַ���
char* Ini::ReadOneLine(int p)
{
//__ENTER_FUNCTION

	int start = FindOneLine(p);
	memset(m_szRet,0,sizeof(m_szRet));
	

	for(int i=start; i<m_lDataLen; i++)
	{
		if( m_strData[i]=='\n' || m_strData[i]=='\0')
		{
			memset(m_szRet,0,sizeof(m_szRet));
			strncpy(m_szRet,&m_strData[start],i-start);
			m_szRet[i-start] = '\0';
			return m_szRet;
		}

	}

//__LEAVE_FUNCTION

	return m_szRet;
}
int Ini::FindOneLine(int p)
{
	char*	Ret = NULL;
	int		n = 0;
	int     m = 0;
	if(p==0)	return -1;
	if(p==1)	return 0;
	for(int i=0; i<m_lDataLen; i++)
	{
		if ( m_strData[i]=='\n' )
			n++;
		if ( n==p-1 )				//�ҵ�Ҫ��Ҫ�ҵĵ���
			return i+1;
	}

	return -1; //û���ҵ�
}
int Ini::ReturnLineNum(char* string)
{
	int p = FindIndex(string);
	char*	Ret = NULL;
	int		n = 0;
	int     m = 0;
	if(p==0)	return -1;
	if(p==1)	return 0;
	for(int i=0; i<p; i++)
	{
		if ( m_strData[i]=='\n' )
			n++;
	}
	return n;

	//return -1; //û���ҵ�
}

