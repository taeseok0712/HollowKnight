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
	// ���� ��ü ��ũ�� ������ ���콺 Ŀ���� ��ǥ�� ������ �Լ�. 
	GetCursorPos(&pt);
	//��ũ�� ��ǥ -> Ŭ���̾�Ʈ ��ǥ�� ��ȯ. 
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
