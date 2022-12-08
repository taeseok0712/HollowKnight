#include "HushKnight.h"
#include "framework.h"


HushKnight::HushKnight()
{
	SetRect(&wall[0], 0, 0, 118, 2160); // 1
	SetRect(&wall[1], 118, 1957, 2052, 2160); // 26
	SetRect(&wall[2], 2052, 1745, 2896, 2160);  // 22
	SetRect(&wall[3], 2896, 1874, 3066, 2160); // 25
	SetRect(&wall[4], 3066, 1745, 5008, 2160); // 23
	SetRect(&wall[5], 5008, 688, 5984, 2160); // 9 
	SetRect(&wall[6], 5984, 1838, 5984 + 2808, 2160); // 24
	SetRect(&wall[7], 5984 + 2808, 363, 9448, 2160); // 8
	SetRect(&wall[8], 866, 0, 6692, 363); // 3
	SetRect(&wall[9], 896, 363, 3643, 841); // 4
	SetRect(&wall[10], 896, 841, 3469, 1154); // 10
	SetRect(&wall[11], 896, 1154, 3295, 1397); // 12
	SetRect(&wall[12], 896, 1397, 3096, 1475); // 14
	SetRect(&wall[13], 896, 1475, 1869, 1716); // 16
	SetRect(&wall[14], 4692, 1537, 4885, 1592); // 발판
	SetRect(&wall[15], 4347, 1333, 4468, 1474); // 발판
	SetRect(&wall[16], 3964, 1270, 4103, 1411); // 발판
	SetRect(&wall[17], 3564, 1273, 3731, 1337); // 발판
	SetRect(&wall[18], 3690, 1021, 3862, 1074); // 발판
	SetRect(&wall[19], 3950, 762, 4115, 817); // 발판
	SetRect(&wall[20], 4344, 631, 4473, 810); // 발판
	SetRect(&wall[21], 4715, 695, 4883, 753); // 발판
	ZeroMemory(&m_tPosin, sizeof(POINT));
}


HushKnight::HushKnight(float x, float y) {
	//m_tInfo.fX = x;
	//m_tInfo.fY = y;
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HushKnightWarrior/walk.bmp", L"HushKnight_walk");
	//CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HushKnightWarrior/attack_HushKnight.bmp", L"HushKnight_attack");
	//m_tInfo.fCX = 260.f;
	//m_tInfo.fCY = 200.f;   // 256 X 256
	//moveDirect = 0;
	//moveCycle = 0;
	//attackDelay = 0;
	//m_eDirc = DR_RIGHT;
	//m_eNextState = STATE_IDLE;
	//m_pFrameKey = L"HushKnight_walk";
	//m_fJumpAccel = 0.2f;
	//m_fJumpPower = 20.f;
	//m_fSpeed = 2.f;
	//iHp = 15;
	//SetRect(&wall[0], 0, 0, 118, 2160); // 1
	//SetRect(&wall[1], 118, 1957, 2052, 2160); // 26
	//SetRect(&wall[2], 2052, 1745, 2896, 2160);  // 22
	//SetRect(&wall[3], 2896, 1874, 3066, 2160); // 25
	//SetRect(&wall[4], 3066, 1745, 5008, 2160); // 23
	//SetRect(&wall[5], 5008, 688, 5984, 2160); // 9 
	//SetRect(&wall[6], 5984, 1838, 5984 + 2808, 2160); // 24
	//SetRect(&wall[7], 5984 + 2808, 363, 9448, 2160); // 8
	//SetRect(&wall[8], 866, 0, 6692, 363); // 3
	//SetRect(&wall[9], 896, 363, 3643, 841); // 4
	//SetRect(&wall[10], 896, 841, 3469, 1154); // 10
	//SetRect(&wall[11], 896, 1154, 3295, 1397); // 12
	//SetRect(&wall[12], 896, 1397, 3096, 1475); // 14
	//SetRect(&wall[13], 896, 1475, 1869, 1716); // 16
	//SetRect(&wall[14], 4692, 1537, 4885, 1592); // 발판
	//SetRect(&wall[15], 4347, 1333, 4468, 1474); // 발판
	//SetRect(&wall[16], 3964, 1270, 4103, 1411); // 발판
	//SetRect(&wall[17], 3564, 1273, 3731, 1337); // 발판
	//SetRect(&wall[18], 3690, 1021, 3862, 1074); // 발판
	//SetRect(&wall[19], 3950, 762, 4115, 817); // 발판
	//SetRect(&wall[20], 4344, 631, 4473, 810); // 발판
	//SetRect(&wall[21], 4715, 695, 4883, 753); // 발판
}
HushKnight::~HushKnight() {


}

void HushKnight::Initialize()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 10;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 50;
	/*m_tInfo.fX = x;
	m_tInfo.fY = y;*/
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HushKnightWarrior/walk.bmp", L"HushKnight_walk");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/HushKnightWarrior/attack_HushKnight.bmp", L"HushKnight_attack");
	//m_tInfo.fCX = 260.f;
	//m_tInfo.fCY = 200.f;   // 256 X 256
	moveDirect = 0;
	moveCycle = 0;
	attackDelay = 0;
	m_eDirc = DR_RIGHT;
	m_eNextState = STATE_IDLE;
	m_pFrameKey = L"HushKnight_walk";
	m_fJumpAccel = 0.2f;
	m_fJumpPower = 20.f;
	m_fSpeed = 2.f;
	iHp = 15;

	//m_tInfo.fX;
}

int HushKnight::Update() {

	HitBox.left = m_tRect.left + 80;
	HitBox.right = m_tRect.right - 75;
	HitBox.top = m_tRect.top + 60;
	HitBox.bottom = m_tRect.bottom - 20;

	
	return 0;
}

void HushKnight::LateUpdate() {
	CObj::FrameMove();
	//findPlayer();
	FrameChange();

}
void HushKnight::Render(HDC hdc) {

	CObj::UpdateRect();
	int iScrollX = CMyScrollMgr::Get_ScrollX();
	int iScrollY = CMyScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	if (!m_bIsDead) {
		GdiTransparentBlt(hdc,
			m_tRect.left + iScrollX, m_tRect.top + iScrollY,
			m_tInfo.fCX, m_tInfo.fCY,
			hMemDC,
			m_eDirc * m_tInfo.fCX, m_tFrame.iFrameStart * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
			m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
			RGB(255, 0, 0));
	}

	
}

void HushKnight::Release() {

}

void HushKnight::FrameChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case HushKnight::STATE_ATT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 50;
			break;

		case HushKnight::STATE_WALK|| HushKnight::STATE_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}

void HushKnight::findPlayer() {

}

void HushKnight::Set_Info(CObj * player)
{
	m_pPlayer = player;
}

void HushKnight::land() {

	
}
void HushKnight::SetData(MonsterData dt)
{
	m_tInfo = dt.info;
	m_eDirc = Direction(dt.MonsterDir);
	FrameChange();
	m_eNextState = STATE(dt.monsterState);
	m_bIsDead = dt.isDead;
	switch (m_eNextState)
	{
	case HushKnight::STATE_ATT:
		m_pFrameKey = L"HushKnight_attack";
		break;
	case HushKnight::STATE_IDLE:
		m_pFrameKey = L"HushKnight_walk";
		break;
	case HushKnight::STATE_WALK:
		m_pFrameKey = L"HushKnight_walk";
		break;
	default:
		break;
	}

}
void HushKnight::Set_time(DWORD Hittime)
{
	time = Hittime;
}