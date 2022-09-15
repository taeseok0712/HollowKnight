#pragma once
class CLine; 
class CLineMgr
{
public:
	static CLineMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineMgr; 

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
	CLineMgr();
	~CLineMgr();
public:
	void Initialize(); 
	void Render(HDC hDC);
	void Release(); 
public:
	bool LineCollision(float fInX, float* pOutY);
	
private:
	static CLineMgr* m_pInstance; 
	list<CLine*> m_listLine;
};

