#include "Maingame.h"
#include "framework.h"
#include "SceneMgr.h"

CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWND);

	//잔상 제거용 
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Back.bmp", L"Back");

//	 더블버퍼링용 dc
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/BackBuffer.bmp", L"BackBuffer");

	CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE1);

}
void CMainGame::LateUpdate()
{
	CSceneMgr::Get_Instance()->LateUpdate();
	CKeyMgr::Get_Instance()->KeyUpdate();
	CMyScrollMgr::ScrollLock();
}
void CMainGame::Release()
{
	ReleaseDC(g_hWND, m_hDC);
	CSceneMgr::Destroy_Instance();
	CBitmapMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
}
void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}
void CMainGame::Render()
{
	if (CSceneMgr::SCENE_LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
	{
		return;
	}
	int iScrollX = CMyScrollMgr::Get_ScrollX();
	int iScrollY = CMyScrollMgr::Get_ScrollY();
	HDC hBack = CBitmapMgr::Get_Instance()->FindImage(L"BackBuffer");
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(L"Back");
	BitBlt(hBack, 0, 0, WINCX, WINCY, hMemDC, 0, 0, NOTSRCCOPY);


	CSceneMgr::Get_Instance()->Render(hBack);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBack, 0, 0, SRCCOPY);
}
