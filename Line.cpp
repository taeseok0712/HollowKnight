#include "framework.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(LINEINFO & rInfo)
	:m_tInfo(rInfo)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int iScroX = CMyScrollMgr::Get_ScrollX();
	int iScroY= CMyScrollMgr::Get_ScrollY();
	MoveToEx(hDC, m_tInfo.tLPoint.fX+ iScroX, m_tInfo.tLPoint.fY+iScroY, nullptr);
	LineTo(hDC, m_tInfo.tRPoint.fX + iScroX, m_tInfo.tRPoint.fY+ iScroY);
}
