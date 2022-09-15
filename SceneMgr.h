#pragma once
#include <Windows.h>
class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)

public:
	enum SCENEID {
		SCENE_LOGO, SCENE_MENU, SCENE_HELP, SCENE_STAGE1
		, SCENE_STAGE2, SCENE_CLEAR, SCENE_END
	};
private:
	CSceneMgr();
	~CSceneMgr();
public:
	SCENEID& Get_SceneID() { return m_eCurScene; }
public:
	void Update(); 
	void LateUpdate();
	void Render(HDC hDC);
	void Release(); 
public:
	void SceneChange(SCENEID eScene);

private:
	CScene* m_pScene; 

	SCENEID m_eCurScene; // ÇöÀç ¾À
	SCENEID m_eNextScene; // ³»°¡ ¹Þ¾Æ¿Ã ¾À 
};

