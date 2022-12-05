#include"framework.h"
#include "MyScrollMgr.h"

int CMyScrollMgr::m_iScrollX = 0;
int CMyScrollMgr::m_iScrollY = 0;
CMyScrollMgr::CMyScrollMgr()
{
}


CMyScrollMgr::~CMyScrollMgr()
{
}

void CMyScrollMgr::ScrollLock()
{
	if (m_iScrollX > 0)
		m_iScrollX = 0;
	if (m_iScrollY > 0)
		m_iScrollY = 0;

	//if (WINCX - TILECX * TILEX > m_iScrollX)
	//	m_iScrollX = WINCX - TILECX * TILEX;
	//if (WINCY - TILECY * TILEY > m_iScrollY)
	//	m_iScrollY = WINCY - TILECY * TILEY;
	
}
