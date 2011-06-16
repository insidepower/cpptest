// MemInfo.cpp: implementation of the CMemInfo class.
//
// Author: T.YogaRamanan

//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemInfo::CMemInfo()
{
	m_ppstInfo = NULL;
	m_dwInfoCount = 0;
}

CMemInfo::~CMemInfo()
{
	DeleteAll();
}

int CMemInfo::Add(char *szDecorated, char *szUndecorated)
{
	if(!m_dwInfoCount)
	{
		m_ppstInfo = new ST_INFO*[1];
		m_ppstInfo[0] = new ST_INFO;
		m_dwInfoCount++;
	}
	else
	{
		ST_INFO **ppTempInfo = new ST_INFO* [m_dwInfoCount+1];
		int n =0;
		for (n=0;n<m_dwInfoCount;n++)
		{
			ppTempInfo[n] = m_ppstInfo[n];
		}

		ppTempInfo[n] = new ST_INFO();
		delete[] m_ppstInfo;
		m_ppstInfo = ppTempInfo;
		m_dwInfoCount++;
	}

	m_ppstInfo[m_dwInfoCount-1]->szDecorated = new char[strlen(szDecorated)+1];
	strcpy(m_ppstInfo[m_dwInfoCount-1]->szDecorated,szDecorated);

	m_ppstInfo[m_dwInfoCount-1]->szUndecorated = new char[strlen(szUndecorated)+1];
	strcpy(m_ppstInfo[m_dwInfoCount-1]->szUndecorated,szUndecorated);

	return 0;
}

int CMemInfo::DeleteAll()
{
	for(int i=0;i<m_dwInfoCount;i++)
	{
		delete m_ppstInfo[i];
	}
	if(m_ppstInfo)
		delete[] m_ppstInfo;
	m_ppstInfo=0;
	m_dwInfoCount=0;
	return 0;
}

int CMemInfo::Get(DWORD dwIndex, char *&szDecorated, char *&szUndecorated)
{
	if(!m_ppstInfo)
		return ERROR_BUFFER_OVERFLOW;
	
	if(dwIndex >= m_dwInfoCount)
		return ERROR_BUFFER_OVERFLOW;

	szDecorated = new char[strlen(m_ppstInfo[dwIndex]->szDecorated)+1];
	strcpy(szDecorated,m_ppstInfo[dwIndex]->szDecorated);

	szUndecorated = new char[strlen(m_ppstInfo[dwIndex]->szUndecorated)+1];
	strcpy(szUndecorated,m_ppstInfo[dwIndex]->szUndecorated);

	return 0;
}
