// Hollow_.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include "framework.h"
#include "Hollow_.h"
#include "Maingame.h"
#include "Common.h"


#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    512
#define MAX_LOADSTRING 100


//서버-클라이언트 통신을 위한 전역변수

SOCKET sock; // 소켓
char OtherPlayerbuf[BUFSIZE + 1]; // 데이터 송수신 버퍼
char Monsterbuf[BUFSIZE + 1]; // 데이터 송수신 버퍼



DWORD WINAPI ClientMain(LPVOID arg);



// 전역 변수:
HWND g_hWND;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


PlayerData playerDataPacket;
HANDLE h_SendDataEvent;
HANDLE h_WriteDataEvent;
HANDLE h_ConnectServerEvent;

//서버 접속용
SCENEID CUR_SCENE;
SCENEID NEXT_SCENE;
string SERVER_IP = "127.0.0.1";
string NickName;
bool ENDFLAG = false;



PlayerData OtherPlayerData;
std::vector<MonsterData> v_Monster;
int waveNum;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void SendPlayerInfo(SOCKET sock)
{
    int retval;
    retval = send(sock, (char*)&playerDataPacket, sizeof(PlayerData), 0);//클라이언트 플레이어 데이터 전송

};
void RecvPlayerInfo(SOCKET sock)
{
    int retval;
    retval = recv(sock, (char*)&OtherPlayerData, sizeof(PlayerData), 0);//클라이언트 플레이어 데이터 전송

};

void SendEndFlag(SOCKET sock) 
{
    int retval;
    retval = recv(sock, (char*)&ENDFLAG, sizeof(bool), 0);//엔드 플레그 전송
}

void RecvSceneID(SOCKET sock)
{
    int retval;
    retval = recv(sock, (char*)&NEXT_SCENE, sizeof(SCENEID), 0);//Scene ID 수신

};
void RecvMonsterData(SOCKET sock, int& MonsterNum,int &temp)
{
    int retval;
    MonsterData Mdt;
    temp = MonsterNum;
    retval = recv(sock, (char*)&MonsterNum, sizeof(int), 0); //몬스터 갯수 받아오기

    for (int i = 0; i < MonsterNum; ++i)
    {

        if (temp != MonsterNum) {
            retval = recv(sock, (char*)&Mdt, sizeof(MonsterData), 0); //몬스터 데이터 받기
            if (temp <= i)
                v_Monster.push_back(Mdt); //받은 데이터를 넣어준다
            if (i == MonsterNum - 1) {//다넣으면 더이상 넣지 않는다
                temp = MonsterNum;
                // SetEvent(h_InitMonsterEvent);
            }
        }
        else {
            retval = recv(sock, (char*)&Mdt, sizeof(MonsterData), 0);
            if (i < temp)
                v_Monster[i] = Mdt; //서버로부터 몬스터 데이터를 받아와 갱신해준다.
        }
    }

    retval = recv(sock, (char*)&waveNum, sizeof(int), MSG_WAITALL);
};



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    //서버 클라이언트 통신을 위한 윈속 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return 1;

    // 이벤트 생성



    //이벤트 생성
    h_WriteDataEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
    h_SendDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    h_InitMonsterEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    h_ConnectServerEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    // 소켓 통신 스레드 생성
    CreateThread(NULL, 0, ClientMain, NULL, 0, NULL);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOLLOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
 

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOLLOW));

    MSG msg;
	msg.message = WM_NULL;
	CMainGame MainGame;
	MainGame.Initialize();
	DWORD dwOldTime = GetTickCount();


	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);

			DispatchMessage(&msg);
		}
		else
		{
			if (dwOldTime + 10 < GetTickCount())
			{

				MainGame.Update();
				MainGame.LateUpdate();
				MainGame.Render();
				dwOldTime = GetTickCount();



			}
		}
	}

    CloseHandle(h_SendDataEvent);
    CloseHandle(h_WriteDataEvent);
    CloseHandle(h_InitMonsterEvent);
    WSACleanup();

	return (int)msg.wParam;
}


//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOLLOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_HOLLOW);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
	RECT rc = { 0, 0, 1600, 900 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE); //출력 영역 크기를 조절하는 함수. 
	HWND hWnd = CreateWindowW(szWindowClass, L"Hollow Knight", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	g_hWND = hWnd;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;



}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

//	PAINTSTRUCT ps;
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}




// TCP 클라이언트 시작 부분
DWORD WINAPI ClientMain(LPVOID arg)
{
	int retval;

	// 소켓 생성

  
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

 
    cout << "서버IP 입력: ";
    cin >> SERVER_IP;
     
    SetEvent(h_ConnectServerEvent);

   // WaitForSingleObject(h_ConnectServerEvent, INFINITE); //클라이언트에 접속할 서버ip주소와 자신의 닉네임 입력 전까진 대기시키기

	// connect()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVER_IP.c_str());
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// 서버와 데이터 통신
    

    PlayerData pd = {}; //다른 플레이어 데이터용
    int GetSize = 0;
    int MonsterNum = -1;
    int temp = -1;
   
    bool b_Init = false;
    while (1) {
        WaitForSingleObject(h_SendDataEvent, INFINITE);
        SendPlayerInfo(sock);
        //타 클라 플레이어 데이터 수신
        RecvPlayerInfo(sock);
        RecvMonsterData(sock, MonsterNum, temp);
        //몬스터 정보 수신
        //temp = MonsterNum;
        //retval = recv(sock, (char*)&MonsterNum, sizeof(int), 0); //몬스터 갯수 받아오기
  /*      SendEndFlag(sock);
        if(ENDFLAG)
            RecvSceneID(sock);*/

        //for (int i = 0; i < MonsterNum; ++i)
        //{
        //    
        //    if (temp != MonsterNum) {
        //        retval = recv(sock, (char*)&Mdt, sizeof(MonsterData), 0); //몬스터 데이터 받기
        //        if (temp <= i)
        //            v_Monster.push_back(Mdt); //받은 데이터를 넣어준다
        //        if (i == MonsterNum - 1) {//다넣으면 더이상 넣지 않는다
        //            temp = MonsterNum;
        //        // SetEvent(h_InitMonsterEvent);
        //        }
        //    }
        //    else {
        //        retval = recv(sock, (char*)&Mdt, sizeof(MonsterData), 0);
        //        if (i < temp)
        //            v_Monster[i] = Mdt; //서버로부터 몬스터 데이터를 받아와 갱신해준다.
        //    }
        // }
        //
        //retval = recv(sock, (char*)&waveNum, sizeof(int), MSG_WAITALL);

        SetEvent(h_WriteDataEvent);
        if (ENDFLAG)
            break;
	}

	return 0;
}
