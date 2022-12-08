#include "Menu.h"
#include "SceneMgr.h"

#include "Button.h"
#include "AbstractFactory.h"

CMenu::CMenu()
{
}


CMenu::~CMenu()
{

	Release();
}

void CMenu::Initialize()
{
	
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Start1.bmp", L"Start1");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Button/Start.bmp", L"Start");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Menu/menuBackground.bmp", L"menuBackground");

	m_RStart.left = 1250;
	m_RStart.top = 450;
	m_RStart.right = 1550;
	m_RStart.bottom = 580;

	m_RExit.left = 1250;
	m_RExit.top = 630;
	m_RExit.right = 1550;
	m_RExit.bottom = 760;
	m_iTochange = 0;
	m_iTochange2 = 80;
}

void CMenu::Update()
{
	


}

void CMenu::LateUpdate()
{
	
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (PtInRect(&m_RStart, pt))
	{
		m_iTochange = 40;
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{	
			
		    CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE1);
			
		}
		
	}
	else {
		m_iTochange =0;
	}


}

void CMenu::Render(HDC hDC)
{
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"menuBackground");
	BitBlt(hDC, 0, 0, 50, 1200, hMemDC, 0, 0, SRCCOPY);
	HDC hbuttonDC = CBitmapMgr::Get_Instance()->FindImage(L"Start");
	TransparentBlt(hMemDC, 1250, 450, 300, 130, hbuttonDC, 0, m_iTochange, 100, 40, RGB(255, 0, 0));
	TransparentBlt(hMemDC, 1250, 630, 300, 130, hbuttonDC, 0, m_iTochange2, 100, 40, RGB(255, 0, 0));
}

void CMenu::Release()
{
	
}
