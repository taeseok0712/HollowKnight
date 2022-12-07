#include "Bittle.h"
#include "framework.h"

Bittle::Bittle() {
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/Bittle/Bittle.bmp", L"Bittle_move");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Monster/Bittle/Bittle_attack.bmp", L"Bittle_attack");
	
	m_pFrameKey = L"Bittle_move";
	moveDirect = 0;
	moveCycle = 0;
	attackDelay = 0;
	m_fJumpAccel = 0.2f;
	m_fJumpPower = 20.f;
	m_fSpeed = 3.f;

	iHp = 1;
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 80;
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

Bittle::Bittle(MonsterData dt) {

	
	
}

Bittle::~Bittle() {


}

void Bittle::Initialize() {

	moveDirect = 0;
	moveCycle = 0;
	attackDelay = 0;
	
	m_eCurState == STATE_IDLE;
	m_eNextState == STATE_IDLE;
	
	m_fJumpAccel = 0.2f;
	m_fJumpPower = 20.f;
	m_fSpeed = 2.f;
	iHp = 1;

}

int Bittle::Update() {
	RECT rcTemp;
	land();

	HitBox.left = m_tRect.left + 73;
	HitBox.right = m_tRect.right - 55;
	HitBox.top = m_tRect.top;
	HitBox.bottom = m_tRect.bottom;

	monsterSight.left = m_tRect.left - 400; // 몬스터 사이트 범위안에 들어오면 따라가기 시작
	monsterSight.right = m_tRect.right + 400;
	monsterSight.top = m_tRect.top;
	monsterSight.bottom = m_tRect.bottom;

	//for (int i = 0; i < 22; ++i) {
	//	if (IntersectRect(&rcTemp, &HitBox, &wall[i])) {
	//		SetRect(&rcTemp, 0, 0, rcTemp.right - rcTemp.left, rcTemp.bottom - rcTemp.top);
	//	}
	//	if (rcTemp.right > rcTemp.bottom) {
	//		if ((HitBox.bottom + HitBox.top) / 2 < (wall[i].bottom + wall[i].top) / 2) {
	//			m_tInfo.fY -= rcTemp.bottom; // 플레이어 중심점 (inpos)

	//		}
	//		else {
	//			m_tInfo.fY += rcTemp.bottom; // 플레이어 중심점

	//		}
	//	}
	//	//오른쪽 왼쪽 충돌
	//	else
	//	{
	//		if ((HitBox.right + HitBox.left) / 2 < (wall[i].right + wall[i].left) / 2) {
	//			m_tInfo.fX -= rcTemp.right;

	//		}
	//		else {
	//			m_tInfo.fX += rcTemp.right;

	//		}

	//	}
	//}


	//if (followOn == FALSE && attackOn == FALSE) { // 평소 걸어다니기
	//	m_fSpeed = 5.f;
	//	if (moveDirect == 1) {
	//		m_tInfo.fX += m_fSpeed;
	//		m_pFrameKey = L"Bittle_move";
	//		m_eDirc = DR_RIGHT;
	//		m_eNextState = STATE_WALK;
	//		++moveCycle;

	//	}
	//	else {
	//		m_tInfo.fX -= m_fSpeed;
	//		m_pFrameKey = L"Bittle_move";
	//		m_eDirc = DR_LEFT;
	//		m_eNextState = STATE_WALK;
	//		++moveCycle;
	//	}

	//}

	//else if (hitOn) {
	//	attackOn = FALSE;
	//	m_fSpeed = 5.f;
	//	if (m_eDirc == DR_LEFT) {
	//		if (m_tFrame.iFrameStart < 8) {
	//			m_tInfo.fX += m_fSpeed;
	//			if (time + 100 < GetTickCount()) {
	//				hitOn = false;
	//				iHp -= 1;
	//			}
	//		}


	//		m_pFrameKey = L"Bittle_move";
	//		m_eDirc = DR_LEFT;
	//		m_eNextState = STATE_WALK;

	//	}
	//	else {
	//		if (m_tFrame.iFrameStart < 8) {
	//			m_tInfo.fX -= m_fSpeed;
	//			if (time + 100 < GetTickCount()) {
	//				hitOn = false;
	//				iHp -= 1;
	//			}

	//		}

	//		m_pFrameKey = L"Bittle_move";
	//		m_eDirc = DR_RIGHT;
	//		m_eNextState = STATE_WALK;
	//	}
	//}
	//else if (attackOn) { // 캐릭터 공격하기
	//	m_fSpeed = 20.f;
	//	if (m_eDirc == DR_LEFT) {
	//		if (m_tFrame.iFrameStart < 3) {
	//			m_tInfo.fX -= m_fSpeed;
	//		}
	//		m_pFrameKey = L"Bittle_attack";
	//		m_eDirc = DR_LEFT;
	//		m_eNextState = STATE_ATT;

	//	}
	//	else {
	//		if (m_tFrame.iFrameStart < 3) {
	//			m_tInfo.fX += m_fSpeed;
	//		}
	//		m_pFrameKey = L"Bittle_attack";
	//		m_eDirc = DR_RIGHT;
	//		m_eNextState = STATE_ATT;
	//	}
	//	if (m_tFrame.iFrameStart == 3) { // 모션이 다 끝나고 공격 종료하기 

	//		attackOn = FALSE;
	//		attackDelay = 0;

	//		if ((p.right + p.left) / 2 < (monsterSight.right + monsterSight.left) / 2) {
	//			m_eDirc = DR_LEFT;

	//		}
	//		else {
	//			m_eDirc = DR_RIGHT;

	//		}
	//	}
	//}
	//else if (followOn) { // 캐릭터 따라가기
	//	m_fSpeed = 2.f;
	//	if (p.right <= HitBox.left) {
	//		m_tInfo.fX -= m_fSpeed;
	//		m_pFrameKey = L"Bittle_move";
	//		m_eDirc = DR_LEFT;
	//		m_eNextState = STATE_WALK;
	//		moveDirect = 0;


	//	}
	//	if (p.left >= HitBox.right) {
	//		m_tInfo.fX += m_fSpeed;
	//		m_pFrameKey = L"Bittle_move";
	//		m_eDirc = DR_RIGHT;
	//		m_eNextState = STATE_WALK;
	//		moveDirect = 1;
	//	}

	//	if (attackOn == FALSE) {
	//		++attackDelay;
	//	}

	//	if (attackDelay == 108) {
	//		attackOn = TRUE;
	//	}
	//}
	return 0;
}

void Bittle::LateUpdate() {
	CObj::FrameMove();
	findPlayer();
	FrameChange();

}
void Bittle::Render(HDC hdc) {

	CObj::UpdateRect();
	int iScrollX = CMyScrollMgr::Get_ScrollX();
	int iScrollY = CMyScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	if (iHp != 0) {
		GdiTransparentBlt(hdc,
			m_tRect.left + iScrollX, m_tRect.top + iScrollY,
			m_tInfo.fCX, m_tInfo.fCY,
			hMemDC,
			m_eDirc * m_tInfo.fCX, m_tFrame.iFrameStart * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
			m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
			RGB(255, 0, 0));
	}

}

void Bittle::Release() {

}

void Bittle::FrameChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case Bittle::STATE_ATT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 3;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 80;
			break;
		case Bittle::STATE_WALK || Bittle::STATE_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
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

void Bittle::findPlayer() {
	RECT rcTemp;
	RECT rcTemp2;
	//p = m_pPlayer->Get_Rect();
	p.left = p.left + 100;
	p.right = p.right - 104;
	p.top = p.top;
	p.bottom = p.bottom;

	if (IntersectRect(&rcTemp, &monsterSight, &p)) { // 몬스터 시야 와 플레이어가 충돌할시

		followOn = TRUE;
	}
	else {
		followOn = FALSE;
	}
}

void Bittle::Set_Info(CObj * player)
{
	m_pPlayer = player;
}
void Bittle::land() {

	float fy = 0.f;
	int i = 0;

	m_fJumpPower = 0;
	if (m_fJumpPower * m_fJumpAccel >= GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f) {
		m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f;
		m_fJumpAccel += 0.20f;
	}
	if (m_fJumpPower * m_fJumpAccel <= GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f) {
		m_tInfo.fY += 10;
	}
}

void Bittle::Set_time(DWORD Hittime)
{
	time = Hittime;
}

void Bittle::SetData(MonsterData dt)
{
	m_tInfo = dt.info;
	m_eDirc = Direction(dt.MonsterDir);
	
	m_eNextState = STATE(dt.monsterState);
	m_bIsDead = dt.isDead;
	switch (m_eNextState)
	{
	case Bittle::STATE_ATT:
		m_pFrameKey = L"Bittle_attack";
		break;
	case Bittle::STATE_IDLE:
		m_pFrameKey = L"Bittle_move";
		break;
	case Bittle::STATE_WALK:
		m_pFrameKey = L"Bittle_move";
		break;
	default:
		break;
	}
	
}
