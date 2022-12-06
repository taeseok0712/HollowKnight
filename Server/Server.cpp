#include "Maingame.h"
#include "Server.h"

#define SERVERPORT 9000
#define BUFSIZE    512

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// 소켓 통신 스레드 함수
DWORD WINAPI ServerMain(LPVOID arg);
DWORD WINAPI ProcessClient(LPVOID arg);

HINSTANCE hInst; // 인스턴스 핸들
HWND g_hWND;


HWND hProgress;
SOCKET g_clientSock[MAXPLAYERNUM]{};
int numOfPlayer = 2;
bool g_gameStart = false;
Client g_clients[2];
PlayerData g_Player;
PlayerData g_Player2;

std::vector<MonsterData*> v_Monster;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	// 소켓 통신 스레드 생성
	CreateThread(NULL, 0, ServerMain, NULL, 0, NULL);

	// 윈도우 클래스 등록
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_HOLLOW));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = _T("MyWndClass");
	if (!RegisterClass(&wndclass)) return 1;

	// 윈도우 생성
	HWND hWnd = CreateWindow(_T("MyWndClass"), _T("Hollow Knight"),
		WS_OVERLAPPEDWINDOW, 0, 0, 1600, 900,
		NULL, NULL, hInstance, NULL);
	g_hWND = hWnd;
	if (hWnd == NULL) return 1;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);



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
		cout << "p1: fX: " << g_Player.info.fX << endl;
		cout << "p2: fX: " << g_Player2.info.fX << endl;
	}
	WSACleanup();

	return (int)msg.wParam;
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_CREATE:
		break;
		return 0;
	case WM_SIZE:
		return 0;
	case WM_SETFOCUS:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}



// TCP 서버 시작 부분
DWORD WINAPI ServerMain(LPVOID arg)
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// 소켓 생성
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// 데이터 통신에 사용할 변수
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread[MAXPLAYERNUM];
	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_quit("accept()");
			break;
		}

		// 접속한 클라이언트 정보 출력
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d\n",
			addr, ntohs(clientaddr.sin_port));

		g_clients[numOfPlayer - 1].sock = client_sock;
		
		// 스레드 생성
		hThread[numOfPlayer - 1] = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)g_clients[numOfPlayer - 1].sock, 0, NULL);
		if (numOfPlayer == MAXPLAYERNUM || g_gameStart) { // 게임이 시작했거나 플레이어 수가 MAX에 도달했을 경우 더 이상 클라이언트를 추가하지 않음
			closesocket(client_sock); 
		}
		else {
			numOfPlayer++;
			CloseHandle(hThread[numOfPlayer - 1]); }
	}

	// 소켓 닫기
	closesocket(listen_sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

// 클라이언트와 데이터 통신
DWORD WINAPI ProcessClient(LPVOID arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE];

	int clientNum = -1;

	// 클라이언트 정보 얻기
	addrlen = sizeof(clientaddr);
	getpeername(client_sock, (struct sockaddr *)&clientaddr, &addrlen);
	inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
	for (int i = 0; i < MAXPLAYERNUM; ++i)
	{
		if (client_sock == g_clients[i].sock) {
			clientNum = i;
			break;
		}
	}
	while (1) {
		// 데이터 받기 -> 여기서 플레이어 정보를 받아온다
		PlayerData recvPlayerData;
		retval = recv(client_sock, (char*)&recvPlayerData, sizeof(recvPlayerData), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			printf("PlayerData recv failed\n");
			break;
		}

		// 플레이어 정보를 받고 scene을 업데이트를 해준다.
		// main->update();
		// 데이터 보내기 -> 여기서 업데이트 된 몬스터 정보와 다른 클라이언트 정보를 클라이언트에게 준다.
		PlayerData otherPlayerdata;
		if (clientNum == 0)			// otherPlayerdata에 m_pPlayer2의 데이터 넣기
			otherPlayerdata = g_Player2;
		else                        // otherPlayerdata에 m_pPlayer의 데이터 넣기
			otherPlayerdata = g_Player;
		//
		for (int i = 0; i < MAXPLAYERNUM; ++i) {
			if (i != clientNum) {				// 다른 클라이언트의 플레이어 정보를 보낸다.
				retval = send(g_clients[i].sock, (char*)&otherPlayerdata, sizeof(otherPlayerdata), 0);
				if (retval == SOCKET_ERROR) {
					printf("다른 플레이어 정보 보내는 도중 오류 발생\n");
					err_quit("send()");
					break;
				}
			}
			// 몬스터 정보를 씬에서 꺼내서 넣어야 함
			retval = send(g_clients[i].sock, (char*)sizeof(v_Monster), sizeof(int), 0);
			retval = send(g_clients[i].sock, (char*)&v_Monster, sizeof(v_Monster), 0);
			if (retval == SOCKET_ERROR) {
				printf("몬스터 정보 보내는 도중 오류 발생\n");
				err_quit("send()");
				break;
			}
		}

	}
	// 소켓 닫기
	closesocket(client_sock);
	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\r\n",
		addr, ntohs(clientaddr.sin_port));
	return 0;
}