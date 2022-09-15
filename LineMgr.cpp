#include "framework.h"
#include "LineMgr.h"
#include "Line.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release(); 
}

void CLineMgr::Initialize()
{
	//SetRect(&wall[0], 0, 0, 118, 2160); // 1
	//SetRect(&wall[1], 118, 1957, 2052, 2160); // 26
	//SetRect(&wall[2], 2052, 1745, 2896, 2160);  // 22
	//SetRect(&wall[3], 2896, 1874, 3066, 2160); // 25
	//SetRect(&wall[4], 3066, 1745, 5008, 2160); // 23
	//SetRect(&wall[5], 5008, 688, 5984, 2160); // 9 
	//SetRect(&wall[6], 5984, 1838, 5984 + 2808, 2160); // 24
	//SetRect(&wall[7], 5984 + 2808, 363, 9448, 2160); // 8
	//SetRect(&wall[8], 866, 0, 6692, 363); // 3
	//SetRect(&wall[9], 896, 363, 3643, 841); // 4
	//SetRect(&wall[10], 896, 841, 3469, 1154); // 10
	//SetRect(&wall[11], 896, 1154, 3295, 1397); // 12
	//SetRect(&wall[12], 896, 1397, 3096, 1475); // 14
	//SetRect(&wall[13], 896, 1475, 1869, 1716); // 16
	//SetRect(&wall[14], 4692, 1537, 4885, 1592); // 발판
	//SetRect(&wall[15], 4347, 1333, 4468, 1474); // 발판
	//SetRect(&wall[16], 3964, 1270, 4103, 1411); // 발판//
	//SetRect(&wall[17], 3564, 1273, 3731, 1337); // 발판
	//SetRect(&wall[18], 3690, 1021, 3862, 1074); // 발판
	//SetRect(&wall[19], 3950, 762, 4115, 817); // 발판
	//SetRect(&wall[20], 4344, 631, 4473, 810); // 발판
	//SetRect(&wall[21], 4715, 695, 4883, 753); // 발판
	LINEPOS tPosArr[24] = { 
	{118.f, 1957.f}, {2052.f, 1957.f},
	{2052.f , 1745.f}, {2896.f, 1745.f},
	{3066.f, 1745.f},{5008.f,1745.f},
	{5008.f, 688.f},{5984.f,688.f},
	{5984.f, 1838.f},{5984.f + 2808.f,1838.f},
	/*{4692.f,1537.f},{4885.f,1537.f},
	{4347.f, 1333.f},{4468.f,1333.f},
	{3964.f, 1270.f},{4103.f,1270.f},
	{3564.f, 1021.f},{ 3731.f,1021.f},
	{3950.f, 762.f},{4115.f,762.f},
	{4344.f, 631.f},{4473.f,631.f},
	{4715.f, 695.f},{4883.f,695.f}*/
	};
 	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[0], tPosArr[1])));
 	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[2], tPosArr[3])));
 	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[4], tPosArr[5])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[6], tPosArr[7])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[8], tPosArr[9])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[10], tPosArr[11])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[12], tPosArr[13])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[14], tPosArr[15])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[16], tPosArr[17])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[18], tPosArr[19])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[20], tPosArr[21])));
	m_listLine.emplace_back(new CLine(LINEINFO(tPosArr[22], tPosArr[23])));

	


}

void CLineMgr::Render(HDC hDC)
{

	for (auto& pLine : m_listLine)
	{
		pLine->Render(hDC);
	}
}

void CLineMgr::Release()
{
	for (auto& pLine : m_listLine)
	{
		if (pLine)
		{
			delete pLine; 
			pLine = nullptr;
		}
	}
	m_listLine.clear();
}

bool CLineMgr::LineCollision(float fInX, float * pOutY)
{
	if(m_listLine.empty())
		return false;

	CLine* pTarget = nullptr; 

	for (auto& pLine : m_listLine)
	{
		if (fInX >= pLine->Get_Info().tLPoint.fX && fInX <= pLine->Get_Info().tRPoint.fX)
		{
			pTarget = pLine; 
		}
	}
	if (pTarget == nullptr)
		return false; 
	
	float x1 = pTarget->Get_Info().tLPoint.fX;
	float x2 = pTarget->Get_Info().tRPoint.fX; 
	float y1 = pTarget->Get_Info().tLPoint.fY; 
	float y2 = pTarget->Get_Info().tRPoint.fY;
	*pOutY = (y2 - y1 )/ (x2 - x1 )* (fInX - x1) + y1; 

	return true; 
}


