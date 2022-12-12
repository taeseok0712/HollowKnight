#include "SubBoss.h"

#include "framework.h"


BOOL InRect(RECT player, RECT monsterSight) {

	if (player.left > monsterSight.right && player.right < monsterSight.right) {
		return TRUE;
	}
	return FALSE;


}

SubBoss::SubBoss() {
	SetRect(&wall[0], 0, 0, 118, 2160); // 1
	SetRect(&wall[1], 118, 1937, 2052, 2160); // 26
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

SubBoss::~SubBoss() {


}

void SubBoss::Initialize() {
	m_tInfo.fX = 7300.f;
	m_tInfo.fY = 1100.f;
	m_tInfo.fCX = 1024.f;
	m_tInfo.fCY = 640.f;   // 256 X 256
	moveDirect = 0;
	moveCycle = 0;
	attackDelay = 0;
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/SubBoss/standby.bmp", L"SubBoss_idle");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/SubBoss/move.bmp", L"SubBoss_move");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/SubBoss/attack.bmp", L"SubBoss_attack");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/SubBoss/attackEffect.bmp", L"effecting");
	m_eDirc = DR_RIGHT;
	m_eNextState = STATE_IDLE;
	m_pFrameKey = L"SubBoss_idle";
	m_fJumpAccel = 0.2f;
	m_fJumpPower = 20.f;
	m_fSpeed = 2.f;
	iHp = 13;
}

int SubBoss::Update() {
	RECT rcTemp;

	//if (followOn == FALSE) {
	//	if (moveCycle % 300 == 0) {
	//		if (moveDirect == 1) {
	//			moveDirect = 0;
	//		}
	//		else {
	//			moveDirect = 1;
	//		}

	//	}
	//}
	HitBox.left = m_tRect.left + 390;
	HitBox.right = m_tRect.right - 394;
	HitBox.top = m_tRect.top + 220;
	HitBox.bottom = m_tRect.bottom - 110;

	//if (effectOn == FALSE) {
	//	if (m_eDirc == DR_RIGHT) {
	//		drawEffect.left = HitBox.left + 128;
	//		drawEffect.right = HitBox.right + 128;
	//		drawEffect.top = HitBox.top;
	//		drawEffect.bottom = HitBox.bottom;
	//	}
	//	else {
	//		drawEffect.left = HitBox.left - 128;
	//		drawEffect.right = HitBox.right - 128;
	//		drawEffect.top = HitBox.top;
	//		drawEffect.bottom = HitBox.bottom;
	//	}
	//}

	//playerAttackBox = dynamic_cast<Player*>(m_pPlayer)->Attack_box;

	monsterSight.left = m_tRect.left - 300; // 몬스터 사이트 범위안에 들어오면 따라가기 시작
	monsterSight.right = m_tRect.right + 300;
	monsterSight.top = m_tRect.top;
	monsterSight.bottom = m_tRect.bottom;

	monsterAttack.left = HitBox.left - 200;  // 몬스터 어택 범위안에 들어오면 공격시작
	monsterAttack.right = HitBox.right + 200;
	monsterAttack.top = HitBox.top;
	monsterAttack.bottom = HitBox.bottom;

	//for (int i = 0; i < 22; ++i) {
	//	if (IntersectRect(&rcTemp, &HitBox, &wall[i])) {
	//		SetRect(&rcTemp, 0, 0, rcTemp.right - rcTemp.left, rcTemp.bottom - rcTemp.top);
	//		if (wall[i].top > m_tInfo.fY) {
	//			Collnum = i;
	//			IsColl = true;
	//		}
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
	//if (IntersectRect(&rcTemp, &HitBox, &wall[Collnum])) {
	//	IsColl = true;

	//}
	//else {
	//	IsColl = false;

	//}

	//if (followOn == FALSE) { // 평소 걸어다니기
	//	m_fSpeed = 2.f;
	//	if (moveDirect == 1) {
	//		m_tInfo.fX += m_fSpeed;
	//		m_pFrameKey = L"SubBoss_move";
	//		m_eDirc = DR_RIGHT;
	//		m_eNextState = STATE_WALK;
	//		++moveCycle;

	//	}
	//	else {
	//		m_tInfo.fX -= m_fSpeed;
	//		m_pFrameKey = L"SubBoss_move";
	//		m_eDirc = DR_LEFT;
	//		m_eNextState = STATE_WALK;
	//		++moveCycle;
	//	}
	//}
	//else if (hitOn) {
	//	attackOn = FALSE;
	//	effectOn = FALSE;
	//	parryingOn = FALSE;
	//	attackDelay = 0;
	//	m_fSpeed = 2.f;
	//	if (m_eDirc == DR_LEFT) {
	//		/*if (m_tFrame.iFrameStart < 1) {
	//		   m_tInfo.fX += m_fSpeed;
	//		   hitOn = FALSE;
	//		}*/
	//		if (m_tFrame.iFrameStart < 8) {
	//			m_tInfo.fX += m_fSpeed;
	//			if (time + 100 < GetTickCount()) {
	//				hitOn = FALSE;
	//				iHp -= 1;

	//			}
	//		}
	//		m_pFrameKey = L"SubBoss_idle";
	//		m_eDirc = DR_LEFT;
	//		m_eNextState = STATE_IDLE;

	//	}
	//	else {
	//		/*if (m_tFrame.iFrameStart < 1) {
	//		   m_tInfo.fX -= m_fSpeed;
	//		   hitOn = FALSE;
	//		}*/
	//		if (m_tFrame.iFrameStart < 8) {
	//			m_tInfo.fX += m_fSpeed;
	//			if (time + 100 < GetTickCount()) {
	//				hitOn = FALSE;
	//				iHp -= 1;

	//			}
	//		}
	//		m_pFrameKey = L"SubBoss_idle";
	//		m_eDirc = DR_RIGHT;
	//		m_eNextState = STATE_IDLE;
	//	}
	//}
	//else if (attackOn) { // 캐릭터 공격하기

	//	if (m_eDirc == DR_LEFT) {
	//		if (!parryingOn) {
	//			effectDir = DR_LEFT;
	//		}
	//		m_pFrameKey = L"SubBoss_attack";
	//		m_eDirc = DR_LEFT;
	//		m_eNextState = STATE_ATT;


	//		if (m_tFrame.iFrameStart == 5) {
	//			if (effectOn == FALSE) {
	//				effectOn = TRUE;
	//			}
	//		}

	//		if (parryingOn) {
	//			drawEffect.left += 20.f;
	//			drawEffect.right += 20.f;
	//		}
	//		else if (effectOn && m_tFrame.iFrameStart >= 5) {
	//			drawEffect.left -= 20.f;
	//			drawEffect.right -= 20.f;
	//		}




	//		BOOL a;
	//		a = dynamic_cast<Player*>(m_pPlayer)->Attck_ON;

	//		if (a) {
	//			if (IntersectRect(&rcTemp, &playerAttackBox, &drawEffect)) {
	//				CSoundMgr::Get_Instance()->PlaySound(L"hero_parry.wav", CSoundMgr::PARRY);
	//				effectDir = DR_RIGHT;
	//				parryingOn = TRUE;
	//				
	//			}
	//		}
	//		if (m_tFrame.iFrameStart == 10) { // 모션이 다 끝나고 공격 종료하기 
	//			attackOn = FALSE;
	//			effectOn = FALSE;
	//			parryingOn = FALSE;
	//			attackDelay = 0;
	//			if ((p.right + p.left) / 2 < (monsterAttack.right + monsterAttack.left) / 2) {
	//				m_eDirc = DR_LEFT;

	//			}
	//			else {
	//				m_eDirc = DR_RIGHT;
	//			}
	//		}
	//	}
	//	else {
	//		if (!parryingOn) {
	//			effectDir = DR_RIGHT;
	//		}

	//		m_pFrameKey = L"SubBoss_attack";
	//		m_eDirc = DR_RIGHT;
	//		m_eNextState = STATE_ATT;

	//		if (m_tFrame.iFrameStart == 5) {
	//			if (effectOn == FALSE) {
	//				effectOn = TRUE;
	//			}
	//		}

	//		if (parryingOn) {
	//			drawEffect.left -= 10.f;
	//			drawEffect.right -= 10.f;
	//		}
	//		else if (effectOn && m_tFrame.iFrameStart >= 5) {
	//			drawEffect.left += 10.f;
	//			drawEffect.right += 10.f;
	//		}


	//		BOOL a;
	//		a = dynamic_cast<Player*>(m_pPlayer)->Attck_ON;
	//		if (a) {
	//			if (IntersectRect(&rcTemp, &playerAttackBox, &drawEffect)) {
	//				effectDir = DR_LEFT;
	//				parryingOn = TRUE;
	//			}
	//		}

	//		if (m_tFrame.iFrameStart == 10) { // 모션이 다 끝나고 공격 종료하기 
	//			attackOn = FALSE;
	//			effectOn = FALSE;
	//			parryingOn = FALSE;
	//			attackDelay = 0;
	//			if ((p.right + p.left) / 2 < (monsterAttack.right + monsterAttack.left) / 2) {
	//				m_eDirc = DR_LEFT;

	//			}
	//			else {
	//				m_eDirc = DR_RIGHT;
	//			}
	//		}
	//	}
	//}
	//else if (followOn) { // 캐릭터 따라가기
	//	m_fSpeed = 2.f;
	//	if (p.right <= HitBox.left) {
	//		m_tInfo.fX -= m_fSpeed;
	//		m_pFrameKey = L"SubBoss_move";
	//		m_eDirc = DR_LEFT;
	//		m_eNextState = STATE_WALK;
	//		moveDirect = 0;

	//	}
	//	if (p.left >= HitBox.right) {
	//		m_tInfo.fX += m_fSpeed;
	//		m_pFrameKey = L"SubBoss_move";
	//		m_eDirc = DR_RIGHT;
	//		m_eNextState = STATE_WALK;
	//		moveDirect = 1;
	//	}

	//	if (!attackOn) {
	//		attackDelay++;
	//	}

	//	if (attackDelay == 60) {
	//		attackOn = TRUE;
	//	}
	//}
	return 0;
}

void SubBoss::LateUpdate() {
	CObj::FrameMove();
	//findPlayer();
	FrameChange();
	land();

	RECT rcTemp;
}
void SubBoss::Render(HDC hdc) {
	CObj::UpdateRect();
	int iScroX = CMyScrollMgr::Get_ScrollX();
	int iScroY = CMyScrollMgr::Get_ScrollY();
	HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);
	HDC hMemDC2 = CBitmapMgr::Get_Instance()->FindImage(L"effecting");
	if (iHp > 0) {
		GdiTransparentBlt(hdc,
			m_tRect.left + iScroX, m_tRect.top + iScroY,
			m_tInfo.fCX, m_tInfo.fCY,
			hMemDC,
			m_eDirc * m_tInfo.fCX, m_tFrame.iFrameStart * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
			m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
			RGB(255, 0, 0));
	}

	//HPEN hPen, oldPen;
	//hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	//oldPen = (HPEN)SelectObject(hdc, hPen);
	//SelectObject(hdc, GetStockObject(NULL_BRUSH));


	//Rectangle(hdc, HitBox.left + iScroX, HitBox.top + iScroY, HitBox.right + iScroX, HitBox.bottom + iScroY);
	//Rectangle(hdc, drawEffect.left + iScroX, drawEffect.top + iScroY, drawEffect.right + iScroX, drawEffect.bottom + iScroY);
	//Rectangle(hdc, playerAttackBox.left + iScroX, playerAttackBox.top + iScroY, playerAttackBox.right + iScroX, playerAttackBox.bottom + iScroY);
	//SelectObject(hdc, oldPen);
	//DeleteObject(hPen);



	if (effectOn) {
		GdiTransparentBlt(hdc,
			drawEffect.left + iScroX, drawEffect.top + iScroY,
			(drawEffect.right - drawEffect.left), (drawEffect.bottom - drawEffect.top),
			hMemDC2,
			effectDir * 128, (m_tFrame.iFrameStart - 6) * 256,// 출력할 그림의 시작 좌표. 
			128, 256,//그림의 전체 가로세로 크기 
			RGB(255, 0, 0));

	}
}

void SubBoss::Release() {

}

void SubBoss::FrameChange() {
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case SubBoss::STATE_ATT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 10;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case SubBoss::STATE_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 0;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case SubBoss::STATE_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
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


void SubBoss::findPlayer() {
	//RECT rcTemp;

	//p = m_pPlayer->Get_Rect();
	//p.left = p.left + 100;
	//p.right = p.right - 104;
	//p.top = p.top;
	//p.bottom = p.bottom;

	//if (IntersectRect(&rcTemp, &monsterSight, &p)) { // 몬스터 시야 와 플레이어가 충돌할시
	//	followOn = TRUE;
	//}
	//else {
	//	followOn = FALSE;
	//}
}

void SubBoss::Set_Info(CObj * player)
{
	m_pPlayer = player;
}

void SubBoss::land() {

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

void SubBoss::Set_time(DWORD Hittime)
{
	time = Hittime;
}

void SubBoss::SetData(MonsterData dt)
{
	m_tInfo = dt.info;
	m_eDirc = Direction(dt.MonsterDir);

	m_eNextState = STATE(dt.monsterState);
	m_bIsDead = dt.isDead;
	switch (m_eNextState)
	{
	case SubBoss::STATE_ATT:
		m_pFrameKey = L"SubBoss_attack";
		break;
	case SubBoss::STATE_IDLE:
		m_pFrameKey = L"SubBoss_idle";
		break;
	case SubBoss::STATE_WALK:
		m_pFrameKey = L"SubBoss_move";
		break;
	default:
		break;
	}
}
