#include "Lobby.h"
#include "SceneMgr.h"

#include "Button.h"
#include "AbstractFactory.h"

CLobby::CLobby()
{
}


CLobby::~CLobby()
{

	Release();
}

void CLobby::Initialize()
{
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Start1.bmp", L"Start1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Start.bmp", L"Start");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Menu/menuBackground.bmp", L"menuBackground");

	m_RStart.left = 1250;
	m_RStart.top = 450;
	m_RStart.right = 1550;
	m_RStart.bottom = 580;

	m_iTochange = 0;
	m_iTochange2 = 80;
}

void CLobby::Update()
{



}

void CLobby::LateUpdate()
{

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (PtInRect(&m_RStart, pt))
	{
		m_iTochange = 40;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{
			

		}

	}
	else {
		m_iTochange = 0;
	}
	if (PtInRect(&m_RExit, pt))
	{
		m_iTochange2 = 120;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{
			DestroyWindow(g_hWND);
		}

	}
	else {
		m_iTochange2 = 80;
	}

}

void CLobby::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"menuBackground");
	BitBlt(hDC, 0, 0, 1920, 1200, hMemDC, 0, 0, SRCCOPY);
	HDC hbuttonDC = CBitmapMgr::Get_Instance()->FindImage(L"Start");
	TransparentBlt(hMemDC, 1250, 450, 300, 130, hbuttonDC, 0, m_iTochange, 100, 40, RGB(255, 0, 0));

}

void CLobby::Release()
{

}
