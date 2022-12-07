#include "framework.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
}

void CMyBitmap::LoadBmp(const TCHAR * pFilePath)
{
	// �ϴ� ȭ�鿡 ����� ȭ�� DC�� ���´�. 
	HDC hDC = GetDC(g_hWND);

	
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWND, hDC);
				  
	m_hBitmap = (HBITMAP)LoadImage(NULL, pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
	
}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);

	DeleteDC(m_hMemDC);
}
