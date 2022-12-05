#pragma once
class CLine
{
public:
	CLine();
	CLine(LINEINFO& rInfo);
	~CLine();
public:
	const LINEINFO& Get_Info()const { return m_tInfo; }
public:
	void Render(HDC hDC); 
private:
	LINEINFO m_tInfo; 

};

