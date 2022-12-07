#pragma once
class CMyScrollMgr
{
public:
	CMyScrollMgr();
	~CMyScrollMgr();

public:
	static int Get_ScrollX(){return m_iScrollX;	}
	static int Get_ScrollY() { return m_iScrollY; }
	static void Set_ScrollX(int iScrX) { m_iScrollX += iScrX; }
	static void Set_ScrollY(int iScrY) { m_iScrollY += iScrY; }

public:
	static void ScrollLock();
private:
	static int m_iScrollX;
	static int m_iScrollY;
};

