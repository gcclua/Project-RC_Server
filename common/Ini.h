
//********************************************
//	Ini ��غ���
//********************************************

#ifndef __INI_H__
#define __INI_H__


#include <stdlib.h>

#define ERROR_DATA (-99999999)
#define MAX_INI_VALUE (1024)
#define MAX_PATH1 (260)
//����ָ��ֵɾ���ڴ�
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
//����ָ��ֵɾ�����������ڴ�
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif
//����ָ�����free�ӿ�
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif
//����ָ�����Release�ӿ�
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif
 
#ifndef _MAX_PATH
#define _MAX_PATH (4096)
#endif
//�����ļ���
class Ini
{
////////////////////////////////////////////////
// �ڲ�����
////////////////////////////////////////////////
private:
	char			m_strFileName[MAX_PATH1];	//�ļ���
	long			m_lDataLen;					//�ļ�����
	char*			m_strData;					//�ļ�����

	int				IndexNum;					//������Ŀ��[]����Ŀ��
	int*			IndexList;					//������λ���б�
	int				Point;						//��ǰָ��
	int				Line, Word;					//��ǰ����

	char			m_szValue[MAX_INI_VALUE] ;
	char			m_szRet[MAX_INI_VALUE];

////////////////////////////////////////////////
// ͨ�ýӿ�
////////////////////////////////////////////////
public:
	Ini();
	Ini(const char* filename);								//��ʼ���������ļ�
	virtual ~Ini();									//�ͷ��ڴ�
	char			*GetData();							//�����ļ�����
	int				GetLines(int);						//�����ļ�������
	int				GetLines();						//�����ļ�������

	bool			Open(const char* filename);				//�������ļ�
	void			Close();							//�ر������ļ�
	bool			Save(char *filename=NULL);			//���������ļ�
	int				FindIndex(char *);					//���ر���λ��

////////////////////////////////////////////////
// �ڲ�����
////////////////////////////////////////////////
private:
	void		InitIndex();						//��ʼ������
	int			FindData(int, char *);				//��������λ��
	int			GotoNextLine(int); 					//����
	char*		ReadDataName(int &);				//��ָ��λ�ö�һ��������
	char*		ReadText(int);						//��ָ��λ�ö��ַ���

	bool		AddIndex(char *);					//����һ������
	bool		AddData(int, char *, char *);		//�ڵ�ǰλ�ü���һ������
	bool		ModityData(int, char *, char *);	//�ڵ�ǰλ���޸�һ�����ݵ�ֵ
	int			GotoLastLine(char *section);			//��ָ���ƶ�����INDEX�����һ��

////////////////////////////////////////////////
// ���ýӿ�
////////////////////////////////////////////////
public:
	//��һ������
	int				Readint(char *section, char *key);
	//������ڣ����һ������
	bool			ReadintIfExist(char *section, char *key, int& nResult);
	//��ָ�����ж�һ����
	int				Readint(char *section, int lines);	
	//��һ���ַ���
	char*			ReadText(char *section, char *key, char* str, int size);
	//����������ȡ
	bool			ReadTextIfExist(char *section, char *key, char* str, int size);
	//��ָ�����ж�һ�ַ���
	char*			ReadText(char *section, int lines, char* str, int size);	
	//��ָ���ж�һ�ַ�����
	char*			ReadCaption(char *section, int lines, char* str, int size);
	//дһ������
	bool			Write(char *section, char *key, int num);			
	//дһ���ַ���
	bool			Write(char *section, char *key, char *string);		
	//������������������INDEX����һ�����У�
	int				GetContinueDataNum(char *section);	
	//��ָ��λ�ö��ַ���
	char*			ReadOneLine(int);
	int				FindOneLine(int);
	//����ָ���ַ����ڵ�����
	int				ReturnLineNum(char*);
};



#endif



