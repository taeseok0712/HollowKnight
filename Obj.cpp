#include "Obj.h"
#include "framework.h"

CObj::CObj()
	:m_fSpeed(0.f)
	, m_bIsDead(false)
	, m_bIsInit(false)

{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}


CObj::~CObj()
{
}


void CObj::setData(MonsterData dt)
{
	
	//m_tInfo.fX = dt.info.fX;
	//m_tInfo.fY = dt.info.fY;
	//m_eDirc = Direction(dt.MonsterDir);
	//m_eNextState = STATE(dt.monsterState);

}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	m_tRect.top = LONG(m_tInfo.fY - (LONG(m_tInfo.fCY) >> 1));
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5f);
}
void CObj::FrameMove()
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();
	}

	if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;
	}
}
bool CObj::Check_Collision(CObj* Player, CObj* monster)
{
	RECT Dst;
	SetRect(&Player->HitBox, Player->HitBox.left, Player->HitBox.top
		, Player->HitBox.right, Player->HitBox.bottom);
	if (monster != nullptr) {
		SetRect(&monster->HitBox, monster->HitBox.left, monster->HitBox.top
			, monster->HitBox.right, monster->HitBox.bottom);

		if (IntersectRect(&Dst, &Player->HitBox, &monster->HitBox))
		{
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void CObj::setDead(bool in)
{
	this->m_bIsDead = in;
}

bool CObj::getIsDead()
{
	return this->m_bIsDead;
}


