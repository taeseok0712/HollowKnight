#include "framework.h"
#include "BitmapMgr.h"
#include "MyBitmap.h"

CBitmapMgr* CBitmapMgr::m_pInstance = nullptr;

CBitmapMgr::CBitmapMgr()
{
}


CBitmapMgr::~CBitmapMgr()
{
	Release(); 
}

HDC CBitmapMgr::FindImage(const TCHAR * pImgKey)
{

	auto &iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), CStrCmp(pImgKey));
	if (m_mapBmp.end() == iter)
	{
		MessageBox(g_hWND, L"그림 없어여!", pImgKey, MB_OK);
		return nullptr;
	}
	return iter->second->Get_MemDC();
}

void CBitmapMgr::InsertBmp(const TCHAR * pFilePath, const TCHAR * pImgKey)
{
	auto &iter = find_if(m_mapBmp.begin(), m_mapBmp.end(), [&](auto& rPair) 
	{
		return !lstrcmp(pImgKey, rPair.first);
	});

	if (iter == m_mapBmp.end())
	{
		CMyBitmap* pBitmap = new CMyBitmap;
		pBitmap->LoadBmp(pFilePath);
		m_mapBmp.emplace(pImgKey, pBitmap);
	}
}

void CBitmapMgr::Release()
{
	for (auto& iter : m_mapBmp)
	{
		if (iter.second)
		{
			delete iter.second; 
			iter.second = nullptr;
		}
	}
	m_mapBmp.clear();
}
