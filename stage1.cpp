#include "stage1.h"
#include "framework.h"
#include "Fly.h"
#include "Husk.h"
#include "Bug.h"
#include "Bittle.h"
#include "SubBoss.h"
#include "LineMgr.h"
#include "SceneMgr.h"
#include "HushKnight.h"
#include "AbstractFactory.h"

CStage1::CStage1()
{
	wave = 1;

	if (m_pPlayer == nullptr) {
		m_pPlayer = new Player;
		m_pPlayer->Initialize();

	}


	if (m_pHush == nullptr) {
		m_pHush = new Husk;
		m_pHush->Initialize();
		dynamic_cast<Husk*>(m_pHush)->Set_Info(m_pPlayer);
		dynamic_cast<Player*>(m_pPlayer)->Set_InfoHusk(m_pHush);
	}

	if (m_pFly == nullptr) {
		m_pFly = new Fly;
		m_pFly->Initialize();
		dynamic_cast<Fly*>(m_pFly)->Set_Info(m_pPlayer);
		dynamic_cast<Player*>(m_pPlayer)->Set_InfoFly(m_pFly);
	}

	if (m_pBug == nullptr) {
		m_pBug = new Bug;
		m_pBug->Initialize();
		dynamic_cast<Bug*>(m_pBug)->Set_Info(m_pPlayer);
		dynamic_cast<Player*>(m_pPlayer)->Set_InfoBug(m_pBug);
	}
	if (m_pbittle == nullptr) {
		m_pbittle = new Bittle;
		m_pbittle->Initialize();
		dynamic_cast<Bittle*>(m_pbittle)->Set_Info(m_pPlayer);
		dynamic_cast<Player*>(m_pPlayer)->Set_Infobit(m_pbittle);
	}
	if (m_pSub == nullptr) {
		m_pSub = new SubBoss;
		m_pSub->Initialize();
		dynamic_cast<SubBoss*>(m_pSub)->Set_Info(m_pPlayer);
		dynamic_cast<Player*>(m_pPlayer)->Set_InfoSubBoss(m_pSub);
	}

	/////////////////////////웨이브//////////////////////////////

	
	/////////////////////////////////////////////////////////////

}


CStage1::~CStage1()
{
}

void CStage1::Initialize()
{

	

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/HPbar_1.bmp", L"HPbar");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/HPicon_1.bmp", L"HPicon");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/UI/PowerGage2.bmp", L"PowerGage");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Field/Tutorial/tutorial_mainlayer.bmp", L"mapRoad");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Field/Tutorial/tutorial_backlayer1.bmp", L"mapBack");
}

void CStage1::Update() {
	m_pPlayer->Update();
	
	
	if (m_pHush != nullptr) {
		m_pHush->Update();
		if (m_pHush->iHp <= 0) {
			Safe_Delete(m_pHush);
		}
	}
	if (m_pFly != nullptr) {
		m_pFly->Update();
		if (m_pFly->iHp <= 0) {
			Safe_Delete(m_pFly);
		}
	}
	if (m_pBug != nullptr) {
		m_pBug->Update();
		if (m_pBug->iHp <= 0) {
			Safe_Delete(m_pBug);
		}
	}
	
	if (m_pSub != nullptr) {
		m_pSub->Update();
		if (m_pSub->iHp <= 0) {
			Safe_Delete(m_pSub);
			wave++;
		}
	}
	if (m_pbittle != nullptr) {
		m_pbittle->Update();
		if (m_pbittle->iHp <= 0) {
			Safe_Delete(m_pbittle);
		}
	}
	/////////////////////////////////////////////////////1/////////////////////////
	if (wave == 2 && dynamic_cast<Player*>(m_pPlayer)->getStage() == false) {
		dynamic_cast<Player*>(m_pPlayer)->Set_Wave(wave);
		if (m_pbittle2 == nullptr) {
			m_pbittle2 = new Bittle(8000.f, 1600.f);
			//m_pbittle->Initialize();
			dynamic_cast<Bittle*>(m_pbittle2)->Set_Info(m_pPlayer);
			dynamic_cast<Player*>(m_pPlayer)->Set_Infobit2(m_pbittle2);
		}
		if (m_pbittle3 == nullptr) {
			m_pbittle3 = new Bittle(7400.f, 1500.f);
			//m_pbittle->Initialize();
			dynamic_cast<Bittle*>(m_pbittle3)->Set_Info(m_pPlayer);
			dynamic_cast<Player*>(m_pPlayer)->Set_Infobit3(m_pbittle3);
		}

		if (m_pbittle4 == nullptr) {
			m_pbittle4 = new Bittle(6200.f, 1300.f);
			//m_pbittle->Initialize();
			dynamic_cast<Bittle*>(m_pbittle4)->Set_Info(m_pPlayer);
			dynamic_cast<Player*>(m_pPlayer)->Set_Infobit4(m_pbittle4);
		}
		wave += 1;
	}

	if (m_pbittle2 != nullptr) {
		m_pbittle2->Update();
		if (m_pbittle2->iHp <= 0) {
			Safe_Delete(m_pbittle2);
		}
	}
	if (m_pbittle3 != nullptr) {
		m_pbittle3->Update();
		if (m_pbittle3->iHp <= 0) {
			Safe_Delete(m_pbittle3);
		}
	}
	if (m_pbittle4 != nullptr) {
		m_pbittle4->Update();
		if (m_pbittle4->iHp <= 0) {
			Safe_Delete(m_pbittle4);
		}
	}
	if (m_pHushKni != nullptr) {
		m_pHushKni->Update();
		if (m_pHushKni->iHp <= 0) {
			Safe_Delete(m_pHushKni);
		}
	}

	if (wave == 3 && Wave2clear==true) {
		
		dynamic_cast<Player*>(m_pPlayer)->Set_Wave(wave);
		dynamic_cast<Player*>(m_pPlayer)->SoundON();
		if (m_pSub == nullptr) {
			m_pSub = new SubBoss;
			m_pSub->Initialize();
			dynamic_cast<SubBoss*>(m_pSub)->Set_Info(m_pPlayer);
			dynamic_cast<Player*>(m_pPlayer)->Set_InfoSubBoss(m_pSub);

			if (m_pHushKni == nullptr) {
				m_pHushKni = new HushKnight(8000.f,1100.f);
				m_pHushKni->Initialize();
				dynamic_cast<HushKnight*>(m_pHushKni)->Set_Info(m_pPlayer);
				dynamic_cast<Player*>(m_pPlayer)->Set_InfoHushK(m_pHushKni);
			}
		}
		
		wave += 1;
		
	}
	
	///////////////////////////////////////////////////////////

	PlayerHp = dynamic_cast<Player*>(m_pPlayer)->GetHp();

	
	if (PlayerHp < 0) {
		CSoundMgr::Get_Instance()->StopAll();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
	}
}

void CStage1::LateUpdate()
{

	m_pPlayer->LateUpdate();
	if (m_pHush != nullptr) {
		m_pHush->LateUpdate();
	}
	if (m_pFly != nullptr) {
		m_pFly->LateUpdate();
	}
	if (m_pBug != nullptr) {
		m_pBug->LateUpdate();
	}
	if (m_pSub != nullptr) {
		m_pSub->LateUpdate();
	}
	if (m_pbittle != nullptr) {
		m_pbittle->LateUpdate();
	}
	if (m_pbittle2 != nullptr) {
		m_pbittle2->LateUpdate();
	}
	if (m_pbittle3 != nullptr) {
		m_pbittle3->LateUpdate();
	}
	if (m_pbittle4 != nullptr) {
		m_pbittle4->LateUpdate();
	}
	if (m_pHushKni != nullptr) {
		m_pHushKni->LateUpdate();
	}

	if (m_pbittle4 == nullptr && m_pbittle3 == nullptr && m_pbittle2 == nullptr&& wave == 3) {
		Wave2clear = true;
	}
	if (wave == 5 && m_pHushKni == nullptr && m_pSub == nullptr) {
		CSoundMgr::Get_Instance()->StopAll();
		CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_MENU);
	}

}

void CStage1::Render(HDC hDC)
{
	m_pPlayer->UpdateRect();
	if (m_pHush != nullptr) {
		m_pHush->UpdateRect();
	}
	if (m_pFly != nullptr) {
		m_pFly->UpdateRect();
	}
	if (m_pBug != nullptr) {
		m_pBug->UpdateRect();
	}
	if (m_pSub != nullptr) {
		m_pSub->UpdateRect();
	}
	if (m_pbittle != nullptr) {
		m_pbittle->UpdateRect();
	}
	if (m_pbittle2 != nullptr) {
		m_pbittle2->UpdateRect();
	}
	if (m_pbittle3 != nullptr) {
		m_pbittle3->UpdateRect();
	}
	if (m_pbittle4 != nullptr) {
		m_pbittle4->UpdateRect();
	}
	if (m_pHushKni != nullptr) {
		m_pHushKni->UpdateRect();
	}
	int iScrollX = CMyScrollMgr::Get_ScrollX();
	int iScrollY = CMyScrollMgr::Get_ScrollY();
	HDC mMemDC2 = CBitmapMgr::Get_Instance()->FindImage(L"mapBack");
	
	BitBlt(hDC, 0, 0, WINCX, WINCY, mMemDC2, 0, 0, SRCCOPY);

	if (m_pHush != nullptr) {
		m_pHush->Render(hDC);
	}
	if (m_pFly != nullptr) {
		m_pFly->Render(hDC);
	}
	if (m_pBug != nullptr) {
		m_pBug->Render(hDC);
	}
	if (m_pSub != nullptr) {
		m_pSub->Render(hDC);
	}
	if (m_pbittle != nullptr) {
		m_pbittle->Render(hDC);
	}
	if (m_pbittle2 != nullptr) {
		m_pbittle2->Render(hDC);
	}
	if (m_pbittle3 != nullptr) {
		m_pbittle3->Render(hDC);
	}
	if (m_pbittle4 != nullptr) {
		m_pbittle4->Render(hDC);
	}
	if (m_pHushKni != nullptr) {
		m_pHushKni->Render(hDC);
	}
	m_pPlayer->Render(hDC);
	HDC mMemDC = CBitmapMgr::Get_Instance()->FindImage(L"mapRoad");
	HDC hHpDC = CBitmapMgr::Get_Instance()->FindImage(L"HPbar");
	HDC hHPiconDC = CBitmapMgr::Get_Instance()->FindImage(L"HPicon");
	HDC PowerGage = CBitmapMgr::Get_Instance()->FindImage(L"PowerGage");
	TransparentBlt(hDC,
		0, 0,
		1600, 900,
		mMemDC,
		-iScrollX, -iScrollY,// 출력할 그림의 시작 좌표. 
		1600, 900,//그림의 전체 가로세로 크기 
		RGB(255, 0, 0));
	GdiTransparentBlt(hDC,
		10, 10,
		500, 200,
		hHpDC,
		0, 0,// 출력할 그림의 시작 좌표. 
		500, 200,//그림의 전체 가로세로 크기 
		RGB(255, 0, 0));
	for (int i = 0; i < PlayerHp; ++i) {
		GdiTransparentBlt(hDC,
			175+(50*i), 100,
			75,75,
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

void CStage1::Release()
{
	
}