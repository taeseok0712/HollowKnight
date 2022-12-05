#include "Stage2.h"
#include "framework.h"
#include "Fly.h"
#include "Husk.h"
#include "Bug.h"
#include "Bittle.h"
#include "SubBoss.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "AbstractFactory.h"

CStage2::CStage2()
{
	
}


CStage2::~CStage2()
{
}

void CStage2::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"S19 Crossroads Main.wav");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/HPbar_1.bmp", L"HPbar");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/HPicon_1.bmp", L"HPicon");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/PowerGage2.bmp", L"PowerGage");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Field/Tutorial/tutorial_mainlayer.bmp", L"mapRoad");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Field/Tutorial/tutorial_backlayer1.bmp", L"mapBack");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Field/Colosseum/Colosseum_mainlayer.bmp", L"mapRoad2");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Field/Colosseum/Colosseum_backlayer1.bmp", L"mapBack2");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Field/Colosseum/Colosseum_backlayer2.bmp", L"mapBack3");
}

void CStage2::Update()
{
	m_pPlayer->Update();

	PlayerHp = dynamic_cast<Player*>(m_pPlayer)->GetHp();
	if (PlayerHp < 0) {
		CSoundMgr::Get_Instance()->StopAll();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
	}
}

void CStage2::LateUpdate()
{
	m_pPlayer->LateUpdate();
}

void CStage2::Render(HDC hDC)
{
	m_pPlayer->UpdateRect();
	int iScrollX = CMyScrollMgr::Get_ScrollX();
	int iScrollY = CMyScrollMgr::Get_ScrollY();

	

	HDC mMemDC = CBitmapMgr::Get_Instance()->FindImage(L"mapRoad2");
	HDC hHpDC = CBitmapMgr::Get_Instance()->FindImage(L"HPbar");
	HDC hHPiconDC = CBitmapMgr::Get_Instance()->FindImage(L"HPicon");
	HDC PowerGage = CBitmapMgr::Get_Instance()->FindImage(L"PowerGage");

	//TransparentBlt(hDC,
	//	0, 0,
	//	1600, 900,
	//	mMemDC,
	//	-iScrollX, -iScrollY,// 출력할 그림의 시작 좌표. 
	//	1600, 900,//그림의 전체 가로세로 크기 
	//	RGB(255, 0, 0));



	m_pPlayer->Render(hDC);
	GdiTransparentBlt(hDC,
		10, 10,
		500, 200,
		hHpDC,
		0, 0,// 출력할 그림의 시작 좌표. 
		500, 200,//그림의 전체 가로세로 크기 
		RGB(255, 0, 0));
	for (int i = 0; i < PlayerHp; ++i) {
		GdiTransparentBlt(hDC,
			175 + (50 * i), 100,
			75, 75,
			hHPiconDC,
			0, 0,// 출력할 그림의 시작 좌표. 
			100, 100,//그림의 전체 가로세로 크기 
			RGB(255, 0, 0));
	}
	GdiTransparentBlt(hDC,
		60, 70,
		125, 110,
		PowerGage,
		0, 115,// 출력할 그림의 시작 좌표. 
		55, 45,//그림의 전체 가로세로 크기 
		RGB(255, 0, 0));
}


void CStage2::Release()
{
}
