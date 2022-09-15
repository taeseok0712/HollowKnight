#include "framework.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "Menu.h"
#include "stage1.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
	,m_eCurScene(SCENE_END)
	,m_eNextScene(SCENE_END)
{
}


CSceneMgr::~CSceneMgr()
{
	Release(); 
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}

void CSceneMgr::SceneChange(SCENEID eScene)
{


	m_eNextScene = eScene; 
	if (m_eNextScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);
		switch (m_eNextScene)
		{
		case CSceneMgr::SCENE_LOGO:
			m_pScene = new CLogo; 
			break;
		case CSceneMgr::SCENE_MENU:
			m_pScene = new CMenu;
			break;
		case CSceneMgr::SCENE_STAGE1:
			m_pScene = new CStage1;
			break;
		case CSceneMgr::SCENE_END:
			break;
		default:
			break;
		}
		m_pScene->Initialize();
		m_eCurScene = m_eNextScene;
	}
}
