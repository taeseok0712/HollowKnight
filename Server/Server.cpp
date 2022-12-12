#include "Maingame.h"
#include "Server.h"

#define SERVERPORT 9000
#define BUFSIZE    512

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// ���� ��� ������ �Լ�
DWORD WINAPI ServerMain(LPVOID arg);
DWORD WINAPI ProcessClient(LPVOID arg);

HINSTANCE hInst; // �ν��Ͻ� �ڵ�
HWND g_hWND;


HWND hProgress;
SOCKET g_clientSock[MAXPLAYERNUM]{};
int numOfPlayer = 0;
bool g_gameStart = false;
Client g_clients[2];
PlayerData g_Player;
PlayerData g_Player2;
int waveNum = 1;


// HANDLE h_InitPlayerEvent;

vector<MonsterData> v_Monster;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;

	// ���� ��� ������ ����
	CreateThread(NULL, 0, ServerMain, NULL, 0, NULL);
	// h_InitPlayerEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	// ������ Ŭ���� ���
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

	// ������ ����
	HWND hWnd = CreateWindow(_T("MyWndClass"), _T("����"),
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
			if (dwOldTime + 10 < GetTickCount() && g_gameStart)
			{

				MainGame.Update();
				MainGame.LateUpdate();
				MainGame.Render();
				dwOldTime = GetTickCount();
			}
		}
	}
	WSACleanup();

	return (int)msg.wParam;
}

// ������ ���ν���
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



// TCP ���� ���� �κ�
DWORD WINAPI ServerMain(LPVOID arg)
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// ���� ����
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

	// ������ ��ſ� ����� ����
	SOCKET client_sock;
	struct sockaddr_in clientaddr;
	int addrlen;
	HANDLE hThread;
	while (1) {
		// accept()
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_quit("accept()");
			break;
		}

		// ������ Ŭ���̾�Ʈ ���� ���
		char addr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientaddr.sin_addr, addr, sizeof(addr));
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			addr, ntohs(clientaddr.sin_port));

		g_clients[numOfPlayer].sock = client_sock;
		
		// ������ ����
		hThread = CreateThread(NULL, 0, ProcessClient,
			(LPVOID)g_clients[numOfPlayer].sock, 0, NULL);
		if (numOfPlayer == MAXPLAYERNUM || g_gameStart) { // ������ �����߰ų� �÷��̾� ���� MAX�� �������� ��� �� �̻� Ŭ���̾�Ʈ�� �߰����� ����
			closesocket(client_sock); 
		}
		else {
			CloseHandle(hThread);
			numOfPlayer++;
			if (numOfPlayer == 2)
				g_gameStart = true;
		}
	}

	// ���� �ݱ�
	closesocket(listen_sock);

	// ���� ����
	WSACleanup();
	return 0;
}

// Ŭ���̾�Ʈ�� ������ ���
DWORD WINAPI ProcessClient(LPVOID arg)
{
	int retval;
	SOCKET client_sock = (SOCKET)arg;
	struct sockaddr_in clientaddr;
	char addr[INET_ADDRSTRLEN];
	int addrlen;
	char buf[BUFSIZE];

	int clientNum = -1; 

	// Ŭ���̾�Ʈ ���� ���
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
	PlayerData recvPlayerData;
	while (1) {
		// ������ �ޱ� -> ���⼭ �÷��̾� ������ �޾ƿ´�

		retval = recv(client_sock, (char*)&recvPlayerData, sizeof(recvPlayerData), MSG_WAITALL);
		if (retval == SOCKET_ERROR) {
			printf("PlayerData recv failed\n");
			break;
		}
		//�÷��̾� �ʱ�ȭ �Ϸ�˸�//
		if (clientNum == 0) {
			g_Player = recvPlayerData;
			cout << "client1.hp: " << g_Player.playerHp << endl;
			// SetEvent(h_InitPlayerEvent);
		}
		else {
			g_Player2 = recvPlayerData;
			cout << "client2.hp: " << g_Player2.playerHp << endl;
			// SetEvent(h_InitPlayerEvent);
		}

		
		//////

		// �÷��̾� ������ �ް� scene�� ������Ʈ�� ���ش�.
		// main->update();
		// ������ ������ -> ���⼭ ������Ʈ �� ���� ������ �ٸ� Ŭ���̾�Ʈ ������ Ŭ���̾�Ʈ���� �ش�.
		////////////////////////////////////////////////////////////////////////////////////////////
		if (clientNum == 0) {
			retval = send(g_clients[clientNum].sock, (char*)&g_Player2, sizeof(PlayerData), 0);
			if (retval == SOCKET_ERROR) {
				printf("�ٸ� �÷��̾� ���� ������ ���� ���� �߻�\n");
				err_quit("send()");
				break;
			}
		}
		else {
			retval = send(g_clients[clientNum].sock, (char*)&g_Player, sizeof(PlayerData), 0);
			if (retval == SOCKET_ERROR) {
				printf("�ٸ� �÷��̾� ���� ������ ���� ���� �߻�\n");
				err_quit("send()");
				break;
			}
		}
		///////////////////////////////////////////////////////////////////////////////////////////
		// ���� ������ ��� �迭�� ������.
		int num = v_Monster.size();
		cout << num << endl;
		retval = send(g_clients[clientNum].sock, (char*)&num, sizeof(int), 0); //���� ���� �ѱ��
		
		for (int i = 0; i < num; ++i) {
			retval = send(g_clients[clientNum].sock, (char*)&v_Monster[i], sizeof(MonsterData), 0);
			if (retval == SOCKET_ERROR) {
				printf("���� ���� ������ ���� ���� �߻�\n");
				err_quit("send()");
				break;
			}
		}
		// wave ���� ������
		retval = send(g_clients[clientNum].sock, (char*)&waveNum, sizeof(int), 0);
		if (retval == SOCKET_ERROR) {
			printf("���̺� ���� ������ ���� ���� �߻�\n");
			err_quit("send()");
			break;
		}
	}
	// ���� �ݱ�
	closesocket(client_sock);
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\r\n",
		addr, ntohs(clientaddr.sin_port));
	return 0;
}