#include "OtherPlayer.h"
#include "framework.h"
#include "Husk.h"
#include "Fly.h"
#include "Bittle.h"
#include "Bug.h"
#include "HushKnight.h"
#include "SubBoss.h"
#include "AbstractFactory.h"

OtherPlayer::OtherPlayer() :m_pFrameKey(L"")
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
	SetRect(&wall[13], 896, 1475, 1669, 1716); // 16
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


OtherPlayer::~OtherPlayer()
{
}

void OtherPlayer::Initialize()
{
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 7;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameTime = GetTickCount();
	m_tFrame.dwFrameSpeed = 100;
	CanHit = true;
	Sound_On = false;
	Hp = 6;
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


	////이펙트/////
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Att_side.bmp", L"side");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Attacked.bmp", L"attackedEff");
	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/effect/Att_UD.bmp", L"up");

	CBitmapMgr::Get_Instance()->InsertBmp(L"../Image/Hero/Player.bmp", L"Player");
	m_fJumpAccel = 0.2f;
	m_fJumpPower = 20.f;
	/*m_eDirc = DR_RIGHT;
	m_eNextState = STATE_FALL;
	m_pFrameKey = L" jump_falling";*/
	Attck = L"side";
	m_fSpeed = 10.f;
	
	b_canChange = true;
	b_IsChange = false;
	//CSoundMgr::Get_Instance()->PlayBGM(L"S19 Crossroads Main.wav");


}


// 중력처리 -> 이동 -> 충돌 
int OtherPlayer::Update()
{
	RECT rcTemp;

	WaitForSingleObject(h_WriteDataEvent, INFINITE); // 읽기 완료 대기
	SetEvent(h_SendDataEvent);
	m_eCurState;
	SetState();
	
	if (b_IsChange == false) {
		if (b_canChange == true) {
			if (m_tInfo.fX > 8700) {

				CSoundMgr::Get_Instance()->StopAll();
				CSoundMgr::Get_Instance()->PlaySound(L"final_boss_chain_break.wave", CSoundMgr::EFFECT);
				CSoundMgr::Get_Instance()->PlayBGM(L"bossmap.wav");
				b_canChange = false;
			}
		}
	}

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

	//for (int i = 0; i < 22; ++i) {
	//	if (IntersectRect(&rcTemp, &HitBox, &wall[i])) {
	//		SetRect(&rcTemp, 0, 0, rcTemp.right - rcTemp.left, rcTemp.bottom - rcTemp.top);
	//		if (wall[i].top > m_tInfo.fY) {
	//			Collnum = i;
	//			IsColl = true;
	//		}

	//		if (rcTemp.right >= rcTemp.bottom) {
	//			if ((HitBox.bottom + HitBox.top) / 2 < (wall[i].bottom + wall[i].top) / 2) {
	//				m_tInfo.fY -= rcTemp.bottom; // 플레이어 중심점 (inpos)

	//			}
	//			else {
	//				m_tInfo.fY += rcTemp.bottom; // 플레이어 중심점

	//			}
	//		}

	//		else
	//		{
	//			if ((m_tRect.right + m_tRect.left) / 2 < (wall[i].right + wall[i].left) / 2) {
	//				m_tInfo.fX -= rcTemp.right;

	//			}
	//			else {
	//				m_tInfo.fX += rcTemp.right;

	//			}

	//		}
	//	}
	//}

	//if (IntersectRect(&rcTemp, &HitBox, &wall[Collnum])) {
	//	IsColl = true;

	//}
	//else {
	//	IsColl = false;

	//}



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

	
	//////////////////////////////////////////////////뒤짐/////////////////////////////////////////////////////////
	//if (Attacked == true && m_bIsDead == false) {
	//	CSoundMgr::Get_Instance()->PlaySound(L"hero_damage.wav", CSoundMgr::ATTED);
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
	//	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ATTED);
	//	CSoundMgr::Get_Instance()->PlaySound(L"hero_death_v2.wav", CSoundMgr::EFFECT);
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


	////////////////////////////////렌딩//////////////////////////////////////////////////

	//if (m_eCurState == STATE_LAND && m_tFrame.iFrameStart == 2) {
	//	m_pFrameKey = L"idle";
	//	m_eNextState = STATE_IDLE;
	//}
	//if (m_eCurState == STATE_LAND && m_tFrame.iFrameStart == 1) {
	//	CSoundMgr::Get_Instance()->PlaySound(L"hero_land_soft.wav", CSoundMgr::LAND);
	//}
	//////////////////////////////////////////////////////////////////////////////////////


	///////////////////////////플레이어 공격관련///////////////////////////////////////

	//if (UDS == UP) {
	//	Attack_box.left = HitBox.left - 70;
	//	Attack_box.top = HitBox.top - 120;
	//	Attack_box.right = HitBox.right + 70;
	//	Attack_box.bottom = HitBox.top - 20;
	//}


	//////////////////////////등장사운드///////////////////////////////////////

	////if (m_wave == 3 && Sound_On == true) {

	////	CSoundMgr::Get_Instance()->PlaySound(L"a.monsterEmer.wav", CSoundMgr::MONSTER);
	////	Sound_On = false;
	////}

	return 0;
}

void OtherPlayer::LateUpdate()
{
	CObj::FrameMove();
	//IsJumping();
	FrameChange();
}

void OtherPlayer::Render(HDC hdc)
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
			m_eDirc * m_tInfo.fCX, m_tFrame.iFrameStart * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
			m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
			RGB(255, 0, 0));


		HDC hAttDC = CBitmapMgr::Get_Instance()->FindImage(Attck);
		if (Attck_ON && Hp > 0) {
			if (UDS == SIDE) {
				if (m_eDirc == DR_RIGHT && m_eCurState == STATE_ATT) {
					GdiTransparentBlt(hdc,
						Attack_box.left + iScrollX, Attack_box.top + iScrollY,
						m_tInfo.fCX, m_tInfo.fCY,
						hAttDC,
						m_tFrame.iFrameStart * 200, 0 * 105,// 출력할 그림의 시작 좌표. 
						200, 105,//그림의 전체 가로세로 크기 
						RGB(255, 0, 0));
				}
				else if (m_eDirc == DR_LEFT && m_eCurState == STATE_ATT) {
					GdiTransparentBlt(hdc,
						Attack_box.left + iScrollX, Attack_box.top + iScrollY,
						m_tInfo.fCX, m_tInfo.fCY,
						hAttDC,
						m_tFrame.iFrameStart * 200, 105,// 출력할 그림의 시작 좌표. 
						200, 105,//그림의 전체 가로세로 크기 
						RGB(255, 0, 0));

				}
			}

			if (UDS == UP && m_eCurState == STATE_ATT) {
				GdiTransparentBlt(hdc,
					Attack_box.left + iScrollX, Attack_box.top + iScrollY,
					170, 150,
					hAttDC,
					0, (m_tFrame.iFrameStart % 2) * 200,// 출력할 그림의 시작 좌표. 
					170, 200,//그림의 전체 가로세로 크기 
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
					m_tFrame.iFrameStart * 800, 0,// 출력할 그림의 시작 좌표. 
					800, 300,//그림의 전체 가로세로 크기 
					RGB(255, 0, 0));
			}
			else if (m_eDirc == DR_LEFT) {
				GdiTransparentBlt(hdc,
					HitBox.left + iScrollX - 70, HitBox.top + iScrollY,
					m_tInfo.fCX, m_tInfo.fCY,
					hAttedDC,
					m_tFrame.iFrameStart * 800, 300,// 출력할 그림의 시작 좌표. 
					800, 300,//그림의 전체 가로세로 크기 
					RGB(255, 0, 0));
			}

		}
		if (UDS != SIDE) {
			//   Rectangle(hdc, Attack_box.left + iScrollX, Attack_box.top+ iScrollY, Attack_box.right + iScrollX, Attack_box.bottom + iScrollY);
		}
		//   Rectangle(hdc, wall[Collnum].left + iScrollX, wall[Collnum].top + iScrollY, wall[Collnum].right + iScrollX, wall[Collnum].bottom + iScrollY);




	}
}


void OtherPlayer::Release()
{
}


void OtherPlayer::IsJumping()
{
	//float fy = 0.f;

	//static bool drop = false;
	//static bool first_frame = true;
	//if (m_bIsJump)
	//{
	//	m_fJumpPower = 20.f;
	//	//자유낙하 공식. 
	//	FSpeed = 5;
	//	Scrollspeed_Y = FSpeed + (GRAVITY * m_fJumpAccel) * 0.5f;
	//	//  y = 파워 * 시간 - 중력 * 시간 제곱 * 0.5f 
	//	if (m_fJumpPower * m_fJumpAccel >= GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f && !drop) {
	//		m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f;
	//		//s= 1/2 a t^2 

	//		m_fJumpAccel += 0.20f;

	//		if (first_frame)
	//			first_frame = false;
	//		else if (IsColl == true)
	//			drop = true;
	//	}
	//	if ((m_fJumpPower * m_fJumpAccel <= GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f) || drop) {

	//		m_tInfo.fY += FSpeed + (GRAVITY * m_fJumpAccel) * 0.5f;
	//		m_pFrameKey = L" jump_falling";
	//		m_eNextState = STATE_FALL;

	//		if (IsColl == true)
	//		{
	//			m_tInfo.fY = wall[Collnum].top - 60;
	//			drop = false;
	//			first_frame = true;
	//		}

	//	}


	//	if (IsColl == true)
	//	{
	//		//m_tInfo.fY = wall[Collnum].top - 60;

	//		m_bIsJump = false;
	//		m_pFrameKey = L" jump_landing";
	//		m_eNextState = STATE_LAND;
	//		m_fJumpAccel = 0.f;
	//	}
	//}
	//else {
	//	m_fJumpPower = 10;

	//	if (m_fJumpPower * m_fJumpAccel >= GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f) {
	//		m_tInfo.fY -= m_fJumpPower * m_fJumpAccel - GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f;
	//		m_fJumpAccel += 0.20f;
	//	}
	//	if (m_fJumpPower * m_fJumpAccel <= GRAVITY * m_fJumpAccel * m_fJumpAccel * 0.5f) {
	//		m_tInfo.fY += FSpeed + (GRAVITY * m_fJumpAccel) * 0.5f;
	//		Scrollspeed_Y = FSpeed + (GRAVITY * m_fJumpAccel) * 0.5f;


	//	}

	//	if (IsColl == true)
	//	{
	//		m_tInfo.fY = wall[Collnum].top - 60;
	//		if (isLand == false) {
	//			if (m_eCurState == STATE_FALL && m_eNextState != STATE_LAND) {

	//				m_pFrameKey = L" jump_landing";
	//				m_eNextState = STATE_LAND;
	//				m_fJumpAccel = 0.f;
	//				isLand = true;

	//			}
	//		}

	//	}
	//}
	//if (IsColl == false) {
	//	isLand = false;
	//}


	///*if (CKeyMgr::Get_Instance()->KeyPressing('C') && Attacked != true && m_eCurState != STATE_FALL)
	//{
	//	m_bIsJump = true;
	//	m_pFrameKey = L"jumpstart";
	//	CSoundMgr::Get_Instance()->PlaySound(L"hero_jump.wav", CSoundMgr::JUMP);
	//	m_eNextState = STATE_JUMP;
	//}*/

}

//
//void OtherPlayer::IsOffset()
//{
//	int iOffset_X = WINCX / 2;
//	int iOffset_Y = WINCY / 2;
//
//	int iScrollX = CMyScrollMgr::Get_ScrollX();
//	int iScrollY = CMyScrollMgr::Get_ScrollY();
//
//
//	if (IsFall == false) {
//		if (iOffset_X + 400 < m_tInfo.fX + iScrollX)
//		{
//			CMyScrollMgr::Set_ScrollX(-Scrollspeed_X);
//
//		}
//		if (iOffset_X - 400 > m_tInfo.fX + iScrollX)
//		{
//			CMyScrollMgr::Set_ScrollX(Scrollspeed_X);
//		}
//
//
//		if (iOffset_Y - 150 < m_tInfo.fY + iScrollY && m_tInfo.fY < 1800)
//		{
//			CMyScrollMgr::Set_ScrollY(-Scrollspeed_Y);
//		}
//		if (iOffset_Y + 200 > m_tInfo.fY + iScrollY && m_tInfo.fY < 1800)
//		{
//			CMyScrollMgr::Set_ScrollY(+Scrollspeed_Y);
//		}
//	}
//
//}




void OtherPlayer::FrameChange()
{
	if (m_eCurState != m_eNextState)
	{
		switch (m_eNextState)
		{
		case OtherPlayer::STATE_ATT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 70;

			break;
		case OtherPlayer::STATE_IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case OtherPlayer::STATE_WALK:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 6;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;

			break;
		case OtherPlayer::STATE_HIT:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 5;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case OtherPlayer::STATE_JUMP:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case OtherPlayer::STATE_FALL:

			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 100;
			break;
		case OtherPlayer::STATE_LAND:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 2;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 10;
			break;
		case OtherPlayer::STATE_DEAD:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 8;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 50;
			break;
		case OtherPlayer::STATE_ATTU:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.iFrameScene = 0;
			m_tFrame.dwFrameTime = GetTickCount();
			m_tFrame.dwFrameSpeed = 50;
			break;
		case OtherPlayer::STATE_ATTD:
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
#include "Exturn.h"
void OtherPlayer::SetState()
{
	m_tInfo.fX = OtherPlayerData.info.fX;
	m_tInfo.fY = OtherPlayerData.info.fY;

	m_tInfo.fCX = OtherPlayerData.info.fCX;// 230.f;//230
	m_tInfo.fCY = OtherPlayerData.info.fCY;//200   // 256 X 256

	m_eDirc = Direction(OtherPlayerData.playerDir);
	m_eNextState = STATE(OtherPlayerData.playerState);

	switch (m_eNextState)
	{
	case OtherPlayer::STATE_ATT:
		m_pFrameKey = L"attack";
		break;
	case OtherPlayer::STATE_IDLE:
		m_pFrameKey = L"idle";
		break;
	case OtherPlayer::STATE_WALK:
		m_pFrameKey = L"move";
		break;
	case OtherPlayer::STATE_HIT:
		m_pFrameKey = L"attacked";
		break;
	case OtherPlayer::STATE_JUMP:
		m_pFrameKey = L"jumpstart";
		break;
	case OtherPlayer::STATE_FALL:
		m_pFrameKey = L"jump_falling";
		break;
	case OtherPlayer::STATE_LAND:
		m_pFrameKey = L" jump_landing";
		break;
	case OtherPlayer::STATE_DEAD:
		m_pFrameKey = L"dead";
		break;
	case OtherPlayer::STATE_ATTD:
		m_pFrameKey = L"idle";
		break;
	case OtherPlayer::STATE_ATTU:
		m_pFrameKey = L"idle";
		break;
	default:
		break;
	}
}
