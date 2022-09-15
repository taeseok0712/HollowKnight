#include "framework.h"
#include "Button.h"
#include "SceneMgr.h"

CMyButton::CMyButton()
	:m_pFrameKey()
	, m_iDrawID(0)
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

}

int CMyButton::Update()
{
	return OBJ_NOEVENT;
}

void CMyButton::LateUpdate()
{
	CObj::UpdateRect();
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->KeyDown(VK_LBUTTON))
		{
			if (!lstrcmp(m_pFrameKey, L"Start"))
				CSceneMgr::Get_Instance()->SceneChange(CSceneMgr::SCENE_STAGE1);

			else if (!lstrcmp(m_pFrameKey, L"Exit"))
				DestroyWindow(g_hWND);
			return;
		}
		m_iDrawID = 1;
	}
	else
		m_iDrawID = 0;
}

void CMyButton::Render(HDC hDC)
{
	CObj::UpdateRect();
	//HDC hMemDC;
	//GdiTransparentBlt(hDC,
	//	m_tRect.left, m_tRect.top,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//	hMemDC, m_iDrawID * m_tInfo.fCX, 0,
	//	(int)m_tInfo.fCX, (int)m_tInfo.fCY,
	//	RGB(255, 255, 255));
}

void CMyButton::Release()
{
}
