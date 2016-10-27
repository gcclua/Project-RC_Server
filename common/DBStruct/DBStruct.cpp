
#include "DBStruct.h"
#include "Base.h"

VOID	DB_QUERY::Parse(const char* pTemplate,...)
{
	va_list argptr;
	va_start(argptr, pTemplate);
	int nchars  = tvsnprintf((char*)m_SqlStr, MAX_SQL_LENGTH, pTemplate, argptr );
	va_end(argptr);

	if (nchars == -1 || nchars > MAX_SQL_LENGTH )
	{
		AssertEx(false,"");
		return;
	}

}

VOID	LONG_DB_QUERY::Parse(const char* pTemplate,...)
{
	va_list argptr;
	va_start(argptr, pTemplate);
	int nchars  = tvsnprintf((char*)m_SqlStr, MAX_LONG_SQL_LENGTH, pTemplate, argptr );
	va_end(argptr);
	if (nchars == -1 || nchars > MAX_LONG_SQL_LENGTH )
	{
		AssertEx(false,"");
		return;
	}

}

char		Value2Ascii(char in)
{
		switch(in) 
		{
			case 0:
				return '0';
				break;
			case 1:
				return '1';
			case 2:
				return '2';
				break;
			case 3:
				return '3';
				break;
			case 4:
				return '4';
				break;
			case 5:
				return '5';
				break;
			case 6:
				return '6';
				break;
			case 7:
				return '7';
				break;
			case 8:
				return '8';
				break;
			case 9:
				return '9';
				break;
			case 10:
				return 'A';
				break;
			case 11:
				return 'B';
				break;
			case 12:
				return 'C';
				break;
			case 13:
				return 'D';
				break;
			case 14:
				return 'E';
				break;
			case 15:
				return 'F';
				break;
			default:
				AssertEx(false,"");
				return '?';
				break;
		}


		return '?';
}

char Ascii2Value(char in)
{
		switch(in) 
	{
		case '0':
			return 0;
			break;
		case '1':
			return 1;
		case '2':
			return 2;
			break;
		case '3':
			return 3;
			break;
		case '4':
			return 4;
			break;
		case '5':
			return 5;
			break;
		case '6':
			return 6;
			break;
		case '7':
			return 7;
			break;
		case '8':
			return 8;
			break;
		case '9':
			return 9;
			break;
		case 'A':
			return 10;
			break;
		case 'B':
			return 11;
			break;
		case 'C':
			return 12;
			break;
		case 'D':
			return 13;
			break;
		case 'E':
			return 14;
			break;
		case 'F':
			return 15;
			break;
		default:
			AssertEx(false,"");
			return '?';
			break;
	}

		return '?';
}


bool	Binary2String(const char* pIn,tuint32 InLength,char* pOut)
{

		if(InLength==0)
		{
			return false;
		}
		tuint32 iOut = 0;

		
		for(tuint32 i = 0 ;i<InLength;i++)
		{
			
			pOut[iOut] = Value2Ascii(((unsigned char)pIn[i]&0xF0)>>4);
			iOut++;
			pOut[iOut] = Value2Ascii(pIn[i]&0x0F);
			iOut++;
		

		}
		return true;

}

bool DBStr2Binary(const char* pIn,tuint32 InLength,char* pOut,tuint32 OutLimit,tuint32& OutLength)
{

		if(InLength==0)
		{
			return false;
		}

		tuint32 iOut = 0;
		tuint32 i;
		for( i = 0 ;i<InLength-1;)
		{
			if(pIn[i]=='\0'||pIn[i+1]=='\0')
			{
				break;
			}
			
			pOut[iOut]	=	(Ascii2Value(pIn[i])<<4) + Ascii2Value(pIn[i+1]);
			iOut++;
			i+=2;
			if(iOut>=OutLimit)
				break;
		}
		OutLength = iOut;
		return true;
}


bool String2Binary(const char* pIn,tuint32 InLength,char* pOut,tuint32 OutLimit,tuint32& OutLength)
{

		if(InLength==0)
		{
			return false;
		}

		tuint32 iOut = 0;
		tuint32 i;
		for( i = 0 ;i<InLength-1;)
		{
			if((pIn[i]=='\\') && (pIn[i+1]=='0'))
			{
				pOut[iOut]	=	'\0';
				iOut++;
				i+=2;
				continue;
			}
			else if((pIn[i]=='\'') && (pIn[i+1]=='\''))
			{
			pOut[iOut]	=	'\'';
			iOut++;
			i+=2;
			continue;
			}
			else if((pIn[i]=='\\') && (pIn[i+1]=='\"'))
			{
				pOut[iOut]	=	'\"';
				iOut++;
				i+=2;
				continue;
			}
			else if((pIn[i]=='\\') && (pIn[i+1]=='\\'))
			{
				pOut[iOut]	=	'\\';
				iOut++;
				i+=2;
				continue;
			}
			else if(pIn[i]=='\0')
			{
				break;
			}

			pOut[iOut] = pIn[i];
			iOut++;
			i++;

			if(iOut>=OutLimit)
				break;
		}
		OutLength = iOut;
		return true;
}

