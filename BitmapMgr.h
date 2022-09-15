#pragma once
class CMyBitmap;
class CBitmapMgr
{
public:
	static CBitmapMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBitmapMgr;

		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
private:
	CBitmapMgr();
	~CBitmapMgr();
public:
	HDC FindImage(const TCHAR* pImgKey);
	void InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void Release(); 
private:
	map<const TCHAR*, CMyBitmap*> m_mapBmp;
	static CBitmapMgr* m_pInstance; 
};

