#include "Player.h"
#include "framework.h"
#include "Husk.h"
#include "Fly.h"
#include "Bittle.h"
#include "Bug.h"
#include "HushKnight.h"
#include "SubBoss.h"
#include "AbstractFactory.h"

Player::Player() :m_pFrameKey(L"")
{
	// WaitForSingleObject(h_InitPlayerEvent, INFINITY);
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/00. idle.bmp", L"idle");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/01. move.bmp", L"move");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/02. jump_start.bmp", L"jumpstart");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/04. jump_falling.bmp", L" jump_falling");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/05. jump_landing.bmp", L" jump_landing");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/06. att_normal_1.bmp", L"attack");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/09. att_down_to_top.bmp", L"attack_up");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/08. att_top_to_down.bmp", L"attack_down");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/10. attacked.bmp", L"attacked");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/11. hero_dead.bmp", L"dead");


	////????Ʈ/////
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Att_side.bmp", L"side");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Attacked.bmp", L"attackedEff");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Att_UD.bmp", L"up");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/Player.bmp", L"Player");

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
	SetRect(&wall[13], 896, 1475, 1669, 1716); // 16
	SetRect(&wall[14], 4692, 1537, 4885, 1592); // ????
	SetRect(&wall[15], 4347, 1333, 4468, 1474); // ????
	SetRect(&wall[16], 3964, 1270, 4103, 1411); // ????
	SetRect(&wall[17], 3564, 1273, 3731, 1337); // ????
	SetRect(&wall[18], 3690, 1021, 3862, 1074); // ????
	SetRect(&wall[19], 3950, 762, 4115, 817); // ????
	SetRect(&wall[20], 4344, 631, 4473, 810); // ????
	SetRect(&wall[21], 4715, 695, 4883, 753); // ????
	ZeroMemory(&m_tPosin, sizeof(POINT));
}


Player::~Player()
{
}

void Player::Initialize()
{
	// WaitForSingleObject(h_InitPlayerEvent, INFINITY);
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/00. idle.bmp", L"idle");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/01. move.bmp", L"move");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/02. jump_start.bmp", L"jumpstart");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/04. jump_falling.bmp", L" jump_falling");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/05. jump_landing.bmp", L" jump_landing");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/06. att_normal_1.bmp", L"attack");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/09. att_down_to_top.bmp", L"attack_up");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/08. att_top_to_down.bmp", L"attack_down");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/10. attacked.bmp", L"attacked");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/motion/11. hero_dead.bmp", L"dead");


	////????Ʈ/////
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Att_side.bmp", L"side");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Attacked.bmp", L"attackedEff");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Att_UD.bmp", L"up");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/Player.bmp", L"Player");


	m_tInfo.fX = 800.f;
	m_tInfo.fY = 500.f;
	m_tInfo.fCX = 256.f;
	m_tInfo.fCY = 128.f;
	CanHit = true;
	Sound_On = false;
	Hp = 6;
	
	m_fJumpAccel = 0.2f;
	m_fJumpPower = 20.f;
	m_eDirc = DR_RIGHT;
	//m_eNextState = STATE_IDLE;
	//m_pFrameKey = L" idle";
	Attck = L"side";
	m_fSpeed = 10.f;
	Scrollspeed_X = 10.f;
	b_canChange = true;
	b_IsChange = false;
	
}


// ?߷?ó?? -> ?̵? -> ?浹 
int Player::Update()
{
	// WaitForSingleObject(h_InitPlayerEvent, INFINITY);
	RECT rcTemp;
	// cout << m_eCurState << endl;


	HitBox.left = m_tRect.left + 100;
	HitBox.right = m_tRect.right - 104;
	HitBox.top = m_tRect.top - 10;
	HitBox.bottom = m_tRect.bottom;

	if (m_eDirc == DR_RIGHT) {
		Attack_box.left = HitBox.right - 100.f;
		Attack_box.top = HitBox.top + 20.f;
		Attack_box.right = Attack_box.left + m_tInfo.fCX;
		Attack_box.bottom = Attack_box.top + m_tInfo.fCY;
	}
	else if (m_eDirc == DR_LEFT) {
		Attack_box.left = HitBox.right - 254.f;
		Attack_box.top = HitBox.top + 20.f;
		Attack_box.right = Attack_box.left + m_tInfo.fCX;
		Attack_box.bottom = Attack_box.top + m_tInfo.fCY;
	}

	for (int i = 0; i < 22; ++i) {
		if (IntersectRect(&rcTemp, &HitBox, &wall[i])) {
			SetRect(&rcTemp, 0, 0, rcTemp.right - rcTemp.left, rcTemp.bottom - rcTemp.top);
			if (wall[i].top > m_tInfo.fY) {
				Collnum = i;
				IsColl = true;
			}

			if (rcTemp.right >= rcTemp.bottom) {
				if ((HitBox.bottom + HitBox.top) / 2 < (wall[i].bottom + wall[i].top) / 2) {
					m_tInfo.fY -= rcTemp.bottom; // ?÷??̾? ?߽??? (inpos)

				}
				else {
					m_tInfo.fY += rcTemp.bottom; // ?÷??̾? ?߽???

				}
			}

			else
			{
				if ((m_tRect.right + m_tRect.left) / 2 < (wall[i].right + wall[i].left) / 2) {
					m_tInfo.fX -= rcTemp.right;

				}
				else {
					m_tInfo.fX += rcTemp.right;

				}

			}
		}
	}

	if (IntersectRect(&rcTemp, &HitBox, &wall[Collnum])) {
		IsColl = true;
	}
	else {
		IsColl = false;
	}

	//if (CKeyMgr::Get_Instance()->KeyPressing(VK_RIGHT) && m_eCurState != STATE_LAND)
	//{

	//	m_tInfo.fX += m_fSpeed;
	//	m_pFrameKey = L"move";
	//	m_eDirc = DR_RIGHT;
	//	m_eNextState = STATE_WALK;
	//}
	//if (CKeyMgr::Get_Instance()->KeyPressing(VK_LEFT) && m_eCurState != STATE_LAND)
	//{

	//	m_tInfo.fX -= m_fSpeed;
	//	m_pFrameKey = L"move";
	//	m_eDirc = DR_LEFT;
	//	m_eNextState = STATE_WALK;
	//}


	//if (CKeyMgr::Get_Instance()->KeyUp(VK_RIGHT) || CKeyMgr::Get_Instance()->KeyUp(VK_LEFT)) {
	//	m_pFrameKey = L"idle";
	//	m_eNextState = STATE_IDLE;
	//}
	///*if (CKeyMgr::Get_Instance()->KeyPressing('C') && Attacked != true && m_eCurState != STATE_FALL)
	//{
	//   m_bIsJump = true;
	//   m_pFrameKey = L"jumpstart";
	//   CSoundMgr::Get_Instance()->PlaySound(L"hero_jump.wav", CSoundMgr::JUMP);
	//   m_eNextState = STATE_JUMP;
	//}*/
	//if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && (GetAsyncKeyState('X') & 0x8000)) {
	//
	//	m_pFrameKey = L"attack_down";
	//	m_eNextState = STATE_ATT;
	//	Attck = L"up";
	//	UDS = DOWN;
	////	Attck_ON = true;
	//}
	//else if ((GetAsyncKeyState(VK_UP) & 0x8000) && (GetAsyncKeyState('X') & 0x8000)) {
	//	
	//	m_pFrameKey = L"attack_up";
	//	m_eNextState = STATE_ATT;
	//	Attck = L"up";
	//	UDS = UP;
	//	Attck_ON = true;
	//}

	//
	//else if (((GetAsyncKeyState('X') & 0x8000) || (GetAsyncKeyState('x') & 0x8000)) && Attacked != true)
	//{
	//	
	//	m_pFrameKey = L"attack";
	//	m_eNextState = STATE_ATT;
	//	Attck = L"side";
	//	UDS = SIDE;
	//	Attck_ON = true;
	//}


	if (m_eCurState == STATE_WALK) {

		
	}
	else if (m_eCurState != STATE_WALK) {

		
	}
	if (m_eCurState == STATE_FALL) {
		
	}
	else if (m_eCurState != STATE_FALL) {
		
	}



	//if (m_eCurState == STATE_ATT && m_tFrame.iFrameStart == 4) {
	//	m_pFrameKey = L"idle";
	//	m_eNextState = STATE_IDLE;

	//}
	//if (m_eCurState == STATE_ATTU && m_tFrame.iFrameStart == 4) {
	//	m_pFrameKey = L"idle";
	//	m_eNextState = STATE_IDLE;

	//}
	//if (m_eCurState == STATE_ATTD && m_tFrame.iFrameStart == 4) {
	//	m_pFrameKey = L"idle";
	//	m_eNextState = STATE_IDLE;

	//}
	//if (m_eNextState != STATE_ATT) {
	//	Attck_ON = false;
	//}

	////////////////////////////////////////////?????? ?÷??̾? ?浹///////////////////////////////////////
	if (Attacked == false) {
		if (m_wave == 0) {
			if (Check_Collision(this, pFly)) {
				if (pFly != nullptr) {
					Hp -= 1;
					Attacked = true;
				}
			}
			if (Check_Collision(this, pBug)) {
				if (pBug != nullptr) {
					Hp -= 1;
					Attacked = true;
				}
			}
			if (Check_Collision(this, pbittle)) {
				if (pbittle != nullptr) {
					Hp -= 1;
					Attacked = true;
				}
			}
			if (Check_Collision(this, pHusk)) {
				if (pHusk != nullptr) {
					Hp -= 1;
					Attacked = true;
				}
			}
			if (Check_Collision(this, pSubBoss)) {
				if (pSubBoss != nullptr) {
					Hp -= 1;
					Attacked = true;
				}
			}
			//bool t = pSubBoss->effectOn;
			/*if (t) {
				RECT rcTemp;
				RECT a = (pSubBoss)->drawEffect;

				if (IntersectRect(&rcTemp, &a, &this->HitBox)) {
					Hp -= 1;
					Attacked = true;
				}
			}*/
		}
		/////////////////////////////////1////////////////////////////////////
		if (m_wave == 3) {
			if (Check_Collision(this, pbittle2)) {
				Hp -= 1;
				Attacked = true;
			}
			if (Check_Collision(this, pbittle3)) {
				Hp -= 1;
				Attacked = true;
			}
			if (Check_Collision(this, pbittle4)) {
				Hp -= 1;
				Attacked = true;
			}
		}
		if (m_wave == 4) {
			if (Check_Collision(this, pHushK)) {
				Hp -= 1;
				Attacked = true;
			}
			bool t = pSubBoss->effectOn;
			if (t) {
				RECT rcTemp;
				RECT a = (pSubBoss)->drawEffect;

				if (IntersectRect(&rcTemp, &a, &this->HitBox)) {
					Hp -= 1;
					Attacked = true;
				}
			}
		}
		///////////////////////////////////////////////////////////
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////?????? ????Ʈ ?浹///////////////////////////////////////

	if (m_wave == 0) {
		if (CheckCollE2M(pHusk)) {
			dynamic_cast<Husk*>(pHusk)->Set_time(GetTickCount());
			dynamic_cast<Husk*>(pHusk)->hitOn = TRUE;
		
		}



		if (CheckCollE2M(pBug)) {
			dynamic_cast<Bug*>(pBug)->Set_time(GetTickCount());
			dynamic_cast<Bug*>(pBug)->hitOn = TRUE;
			
		}

		if (CheckCollE2M(pbittle)) {
			dynamic_cast<Bittle*>(pbittle)->Set_time(GetTickCount());
			dynamic_cast<Bittle*>(pbittle)->hitOn = TRUE;
			
		}



		if (CheckCollE2M(pFly)) {
			dynamic_cast<Fly*>(pFly)->Set_time(GetTickCount());
			dynamic_cast<Fly*>(pFly)->hitOn = TRUE;
			
		}

		if (CheckCollE2M(pSubBoss)) {
			dynamic_cast<SubBoss*>(pSubBoss)->Set_time(GetTickCount());
			dynamic_cast<SubBoss*>(pSubBoss)->hitOn = TRUE;
			
		}
	}
	///1???̺?///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (m_wave == 3) {
		if (CheckCollE2M(pbittle2)) {
			dynamic_cast<Bittle*>(pbittle2)->Set_time(GetTickCount());
			dynamic_cast<Bittle*>(pbittle2)->hitOn = TRUE;

		}

		if (CheckCollE2M(pbittle3)) {
			dynamic_cast<Bittle*>(pbittle3)->Set_time(GetTickCount());
			dynamic_cast<Bittle*>(pbittle3)->hitOn = TRUE;

		}

		if (CheckCollE2M(pbittle4)) {
			dynamic_cast<Bittle*>(pbittle4)->Set_time(GetTickCount());
			dynamic_cast<Bittle*>(pbittle4)->hitOn = TRUE;

		}
	}
	if (m_wave == 4) {
		if (CheckCollE2M(pHushK)) {
			dynamic_cast<HushKnight*>(pHushK)->Set_time(GetTickCount());
			dynamic_cast<HushKnight*>(pHushK)->hitOn = TRUE;
			
		}
		if (CheckCollE2M(pSubBoss)) {
			dynamic_cast<SubBoss*>(pSubBoss)->Set_time(GetTickCount());
			dynamic_cast<SubBoss*>(pSubBoss)->hitOn = TRUE;
			
		}

	}
	////////////////////////////////////////////////????/////////////////////////////////////////////////////////
	//if (Attacked == true && m_bIsDead == false) {
	//	
	//	m_pFrameKey = L"attacked";
	//	m_eNextState = STATE_HIT;
	//	if (m_eDirc == DR_RIGHT) {
	//		m_tInfo.fX -= 10;
	//	}
	//	else if (m_eDirc == DR_LEFT) {
	//		m_tInfo.fX += 10;
	//	}
	//	if (m_eCurState == STATE_HIT && m_tFrame.iFrameStart == 5) {
	//		m_pFrameKey = L"idle";
	//		m_eNextState = STATE_IDLE;
	//		Attacked = false;
	//	}
	//}


	//if (Hp <= 0) {
	//	
	//	m_pFrameKey = L"dead";
	//	m_eNextState = STATE_DEAD;
	//	Attacked = true;

	//}
	//if (Hp <= 0 && deadswitch == false) {
	//	deadswitch = true;
	//	deadtime = GetTickCount();
	//}
	//if (m_eCurState == STATE_DEAD && m_tFrame.iFrameStart == 8) {
	//	m_bIsDead = true;
	//	if (deadtime + 5000 < GetTickCount()) {
	//		Hp = -1;
	//	}
	//}


	//////////////////////////////????//////////////////////////////////////////////////

	//if (m_eCurState == STATE_LAND && m_tFrame.iFrameStart == 2) {
	//	m_pFrameKey = L"idle";
	//	m_eNextState = STATE_IDLE;
	//}
	//if (m_eCurState == STATE_LAND && m_tFrame.iFrameStart == 1) {
	//	
	//}
	////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////?÷??̾? ???ݰ???///////////////////////////////////////

	if (UDS == UP) {
		Attack_box.left = HitBox.left - 70;
		Attack_box.top = HitBox.top - 120;
		Attack_box.right = HitBox.right + 70;
		Attack_box.bottom = HitBox.top - 20;
	}


	////////////////////////??????????///////////////////////////////////////
	
	if ( m_wave == 3 &&Sound_On==true) {

		
		Sound_On = false;
	}
	
	return 0;
}

void Player::LateUpdate()
{
	CObj::FrameMove();
	IsJumping();
	IsOffset();
	FrameChange();
}

void Player::Render(HDC hdc)
{
	CObj::UpdateRect();

	if (m_bIsDead != true) {
		int iScrollX = CMyScrollMgr::Get_ScrollX();

		int iScrollY = CMyScrollMgr::Get_ScrollY();
		HDC hMemDC = CBitmapMgr::Get_Instance()->FindImage(m_pFrameKey);

		GdiTransparentBlt(hdc,
			m_tRect.left + iScrollX, HitBox.top + iScrollY,
			m_tInfo.fCX, m_tInfo.fCY,
			hMemDC,
			m_eDirc * m_tInfo.fCX, m_tFrame.iFrameStart * m_tInfo.fCY,// ?????? ?׸??? ???? ??ǥ. 
			m_tInfo.fCX, m_tInfo.fCY,//?׸??? ??ü ???μ??? ũ?? 
			RGB(255, 0, 0));


		HDC hAttDC = CBitmapMgr::Get_Instance()->FindImage(Attck);
		if (Attck_ON && Hp > 0) {
			if (UDS == SIDE) {
				if (m_eDirc == DR_RIGHT && m_eCurState == STATE_ATT) {
					GdiTransparentBlt(hdc,
						Attack_box.left + iScrollX, Attack_box.top + iScrollY,
						m_tInfo.fCX, m_tInfo.fCY,
						hAttDC,
						m_tFrame.iFrameStart * 200, 0 * 105,// ?????? ?׸??? ???? ??ǥ. 
						200, 105,//?׸??? ??ü ???μ??? ũ?? 
						RGB(255, 0, 0));
				}
				else if (m_eDirc == DR_LEFT && m_eCurState == STATE_ATT) {
					GdiTransparentBlt(hdc,
						Attack_box.left + iScrollX, Attack_box.top + iScrollY,
						m_tInfo.fCX, m_tInfo.fCY,
						hAttDC,
						m_tFrame.iFrameStart * 200, 105,// ?????? ?׸??? ???? ??ǥ. 
						200, 105,//?׸??? ??ü ???μ??? ũ?? 
						RGB(255, 0, 0));

				}
			}

			if (UDS == UP && m_eCurState == STATE_ATT) {
				GdiTransparentBlt(hdc,
					Attack_box.left + iScrollX, Attack_box.top + iScrollY,
					170, 150,
					hAttDC,
					0, (m_tFrame.iFrameStart % 2) * 200,// ?????? ?׸??? ???? ??ǥ. 
					170, 200,//?׸??? ??ü ???μ??? ũ?? 
					RGB(255, 0, 0));

			}

		}

		HDC hAttedDC = CBitmapMgr::Get_Instance()->FindImage(L"attackedEff");
		if (Attacked) {

			if (m_eDirc == DR_RIGHT) {
				GdiTransparentBlt(hdc,
					HitBox.left + iScrollX - 70, HitBox.top + iScrollY,
					m_tInfo.fCX, m_tInfo.fCY,
					hAttedDC,
					m_tFrame.iFrameStart * 800, 0,// ?????? ?׸??? ???? ??ǥ. 
					800, 300,//?׸??? ??ü ???μ??? ũ?? 
					RGB(255, 0, 0));
			}
			else if (m_eDirc == DR_LEFT) {
				GdiTransparentBlt(hdc,
					HitBox.left + iScrollX - 70, HitBox.top + iScrollY,
					m_tInfo.fCX, m_tInfo.fCY,
					hAttedDC,
					m_tFrame.iFrameStart * 800, 300,// ?????? ?׸??? ???? ??ǥ. 
					800, 300,//?׸??? ??ü ???μ??? ũ?? 
					RGB(255, 0, 0));
			}

		}
		if (UDS != SIDE) {
			//   Rectangle(hdc, Attack_box.left + iScrollX, Attack_box.top+ iScrollY, Attack_box.right + iScrollX, Attack_box.bottom + iScrollY);
		}
		//   Rectangle(hdc, wall[Collnum].left + iScrollX, wall[Collnum].top + iScrollY, wall[Collnum].right + iScrollX, wall[Collnum].bottom + iScrollY);




	}
}


void Player::Release()
{
}


void Player::IsJumping()
{
}


void Player::IsOffset()
{
	int iOffset_X = WINCX / 2;
	int iOffset_Y = WINCY / 2;

	int iScrollX = CMyScrollMgr::Get_ScrollX();
	int iScrollY = CMyScrollMgr::Get_ScrollY();


	if (IsFall == false) {
		if (iOffset_X + 400 < m_tInfo.fX + iScrollX)
		{
			CMyScrollMgr::Set_ScrollX(-Scrollspeed_X);

		}
		if (iOffset_X - 400 > m_tInfo.fX + iScrollX)
		{
			CMyScrollMgr::Set_ScrollX(Scrollspeed_X);
		}


		if (iOffset_Y - 150 < m_tInfo.fY + iScrollY && m_tInfo.fY < 1800)
		{
			CMyScrollMgr::Set_ScrollY(-Scrollspeed_Y);
		}
		if (iOffset_Y + 200 > m_tInfo.fY + iScrollY && m_tInfo.fY < 1800)
		{
			CMyScrollMgr::Set_ScrollY(+Scrollspeed_Y);
		}
	}

}




void Player::FrameChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case Player::STATE_ATT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 70;

			break;
		case Player::STATE_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case Player::STATE_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;

			break;
		case Player::STATE_HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case Player::STATE_JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case Player::STATE_FALL:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case Player::STATE_LAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 10;
			break;
		case Player::STATE_DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 50;
			break;
		case Player::STATE_ATTU:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 50;
			break;
		case Player::STATE_ATTD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 50;
			break;
		default:
			break;
		}
		m_eCurState = m_eNextState;
	}
}

bool Player::CheckCollE2M(CObj * monster)
{
	RECT Dst;
	if (Attck_ON) {
		SetRect(&Attack_box, Attack_box.left, Attack_box.top, Attack_box.right, Attack_box.bottom);
		if (monster != nullptr) {
			SetRect(&monster->HitBox, monster->HitBox.left, monster->HitBox.top, monster->HitBox.right, monster->HitBox.bottom);
			if (IntersectRect(&Dst, &Attack_box, &monster->HitBox))
			{
				return true;
			}
		}
		else {
			return false;
		}
	}
	else return false;

}

void Player::Set_InfoHusk(CObj * Monster)
{
	pHusk = Monster;
}

void Player::Set_InfoFly(CObj * Monster)
{
	pFly = Monster;
}
void Player::Set_InfoBug(CObj * Monster)
{
	pBug = Monster;
}

void Player::Set_InfoSubBoss(CObj * Monster)
{
	pSubBoss = Monster;
}
void Player::Set_Infobit(CObj * Monster)
{
	pbittle = Monster;
}
void Player::Set_Infobit2(CObj* Monster)
{
	pbittle2 = Monster;
}

void Player::Set_Infobit3(CObj* Monster)
{
	pbittle3 = Monster;
}

void Player::Set_Infobit4(CObj* Monster)
{
	pbittle4 = Monster;
}
void Player::Set_InfoHushK(CObj* Monster)
{
	pHushK = Monster;
}

int Player::GetHp()
{
	return Hp;
}

bool Player::getStage()
{
	return b_canChange;
}


void Player::SoundON()
{
	Sound_On = true;
}

PlayerData Player::Get_PlayerData()
{
	PlayerData temp;
	temp.info = this->m_tInfo;
	temp.isDead = this->m_bIsDead;
	temp.playerState = PLAYERSTATE(this->m_eNextState);
	temp.playerHp = this->Hp;
	temp.playerDir = this->m_eDirc;
	return temp;
}

void Player::Set_PlayerData(PlayerData playerdata)
{
	this->m_tInfo = playerdata.info;
	this->m_bIsDead = playerdata.isDead;
	this->m_eNextState = STATE(playerdata.playerState);
	this->Hp = playerdata.playerHp;
	this->m_eDirc = playerdata.playerDir;
	this->Attck_ON = playerdata.attakOn;

	switch (m_eNextState)
	{
	case Player::STATE_ATT:
		m_pFrameKey = L"attack";
		break;
	case Player::STATE_IDLE:
		m_pFrameKey = L"idle";
		break;
	case Player::STATE_WALK:
		m_pFrameKey = L"move";
		break;
	case Player::STATE_HIT:
		m_pFrameKey = L"attacked";
		break;
	case Player::STATE_JUMP:
		m_pFrameKey = L"jumpstart";
		break;
	case Player::STATE_FALL:
		m_pFrameKey = L" jump_falling";
		break;
	case Player::STATE_LAND:
		m_pFrameKey = L" jump_landing";
		break;
	case Player::STATE_DEAD:
		m_pFrameKey = L"dead";
		break;
	case Player::STATE_ATTD:
		m_pFrameKey = L"idle";
		break;
	case Player::STATE_ATTU:
		m_pFrameKey = L"idle";
		break;
	default:
		break;
	}
}