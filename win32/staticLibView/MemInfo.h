// MemInfo.h: interface for the CMemInfo class.
//
// Author: T.YogaRamanan

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMINFO_H__F50C909E_EEA2_4FC1_AFC9_1AC67CDC2436__INCLUDED_)
#define AFX_MEMINFO_H__F50C909E_EEA2_4FC1_AFC9_1AC67CDC2436__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemInfo  
{
public:
	int DeleteAll();

	int Get(DWORD dwIndex, char *&szDecorated, char *&szUndecorated);
	int Add(char *szDecorated, char *szUndecorated);

	struct ST_INFO
	{
		int nSeq;
		char *szDecorated;
		char *szUndecorated;

		ST_INFO()
		{
			nSeq = -1;
			szDecorated = NULL;
			szUndecorated = NULL;
		}

		~ST_INFO()
		{
			nSeq = -1;
			if(szDecorated)
				delete szDecorated;
			szDecorated = NULL;

			if(szUndecorated)
				szUndecorated = NULL;
			szUndecorated = NULL;
		}

	} **m_ppstInfo;

	DWORD m_dwInfoCount;

	CMemInfo();
	virtual ~CMemInfo();

};

#endif // !defined(AFX_MEMINFO_H__F50C909E_EEA2_4FC1_AFC9_1AC67CDC2436__INCLUDED_)
