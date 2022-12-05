#include "framework.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize()
{
	m_tInfo.fCY = 20.f;
	m_tInfo.fCX = 20.f;
}

int CMouse::Update()
{
	CObj::UpdateRect();
	POINT pt = {};
	// 현재 전체 스크린 영역의 마우스 커서의 좌표를 얻어오는 함수. 
	GetCursorPos(&pt);
	//스크린 좌표 -> 클라이언트 좌표로 변환. 
	ScreenToClient(g_hWND, &pt);
	m_tInfo.fX = float(pt.x);
	m_tInfo.fY = float(pt.y);
	ShowCursor(FALSE);
	return 0;
}

void CMouse::LateUpdate()
{
}

void CMouse::Render(HDC hDC)
{
	CObj::UpdateRect();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
}
