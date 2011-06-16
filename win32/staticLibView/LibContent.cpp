// LibContent.cpp: implementation of the CLibContent class.
//
// Author: T.YogaRamanan
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LibContent.h"

#include "Dbghelp.h"

#define C_STYLE "__imp__"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLibContent::CLibContent()
{
}

CLibContent::~CLibContent()
{
}

int CLibContent::Browse(const char *szFilePath)
{
	HANDLE hLibFile = CreateFile(szFilePath,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,0,NULL);
	if(hLibFile == INVALID_HANDLE_VALUE)
		return GetLastError();

	char szChar[256];
	DWORD dwBytes, i;
	int nRet;
	
	char szBuff[1024];
	DWORD dwBuffPos = 0;
	bool bCollect = false;

	DWORD dwFileSize = GetFileSize(hLibFile,NULL);

	for(i=0;i<dwFileSize;i++)
	{
		SetFilePointer(hLibFile,i,0,FILE_BEGIN);

		nRet = ReadFile(hLibFile,&szChar,32,&dwBytes,NULL);
		if(!nRet)
			return GetLastError();
		
		if((szChar[0] == '?')||(bCollect))
		{// the symbol is C++ type collect it
			szBuff[dwBuffPos] = szChar[0];
			dwBuffPos++;
			bCollect = true;
		}
		else if(!memcmp(szChar,C_STYLE,7)) // check if it is C style
		{
			dwBytes = strlen(szChar);
			nRet = ExtractCSymbol(szChar,dwBytes); // if it is succ then 0 else non zeror
			if(!nRet)// if failed then pass on to next char
				i += dwBytes;// if passed skip the string
		}

		if((szChar[0] == 0)&&(bCollect))
		{ // finish and pass the buffer to decode
			szBuff[dwBuffPos] = szChar[0];
			dwBuffPos++;

			nRet = ExtractCppSymbol(szBuff, dwBuffPos);
			
			dwBuffPos = 0;
			bCollect = false;
		}
	}
	CloseHandle(hLibFile);

	return ERROR_SUCCESS;
}

int CLibContent::ExtractCppSymbol(char *szDecoratedName, DWORD dwLen)
{
	char szFunc[512];
	int nRet;

	//SymSetOptions(SYMOPT_NO_CPP|SYMOPT_DEFERRED_LOADS|SYMOPT_LOAD_LINES|SYMOPT_CASE_INSENSITIVE|SYMOPT_UNDNAME);
	
	nRet = UnDecorateSymbolName(szDecoratedName,szFunc,512,UNDNAME_COMPLETE|UNDNAME_32_BIT_DECODE);
	if(!nRet)
		return GetLastError();

	if(!memcmp(szDecoratedName,szFunc,nRet))
		return ERROR_INVALID_DATA;// since it is not decoded, this cud b some junk

	if(!memcmp("`string'",szFunc,nRet))// this cud b imported functions and constants
		return ERROR_INVALID_DATA;		//      so v don't need this

	return  m_cMemStore.Add(szDecoratedName,szFunc);	
}



int CLibContent::ExtractCSymbol(char *szDecoratedName, DWORD dwLen)
{
	char szFunc[512];
	DWORD dwBuffPos;
	int i = 0;
	dwBuffPos = 0;

	if(memcmp(szDecoratedName,C_STYLE,7))
		return  ERROR_INVALID_DATA;

	i += strlen(C_STYLE);
	
	for(;i<dwLen;i++)
	{
		szFunc[dwBuffPos] = szDecoratedName[i];
		
		if(szFunc[dwBuffPos] == '@')
		{
			szFunc[dwBuffPos] = 0;
			m_cMemStore.Add(szDecoratedName,szFunc);
			return ERROR_SUCCESS;
		}

		dwBuffPos++;
	}

	return  ERROR_INVALID_DATA;;	
}

int CLibContent::GetFuncDetail(DWORD dwIndex, char *&szDecorated, char *&szUndecorated)
{
	return m_cMemStore.Get(dwIndex, szDecorated, szUndecorated);
}

DWORD CLibContent::GetTotalCount()
{
	return m_cMemStore.m_dwInfoCount;
}

