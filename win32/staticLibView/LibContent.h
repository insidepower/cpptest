// LibContent.h: interface for the CLibContent class.
//
// Author: T.YogaRamanan
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIBCONTENT_H__667E6487_66B8_4A65_A255_DFBE034EC23A__INCLUDED_)
#define AFX_LIBCONTENT_H__667E6487_66B8_4A65_A255_DFBE034EC23A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "MemInfo.h"


class CLibContent  
{
protected:
	int ExtractCSymbol(char *szDecoratedName, DWORD dwLen);
	int ExtractCppSymbol(char *szDecoratedName, DWORD dwLen);

	CMemInfo m_cMemStore;

public:
	DWORD GetTotalCount();
	int GetFuncDetail(DWORD dwIndex, char *&szDecorated, char *&szUndecorated);
	int Browse(const char *szFilePath);
	CLibContent();
	virtual ~CLibContent();

};

#endif // !defined(AFX_LIBCONTENT_H__667E6487_66B8_4A65_A255_DFBE034EC23A__INCLUDED_)
