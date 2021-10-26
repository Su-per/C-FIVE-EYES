#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>
#include <iostream>
#include "omokai.h"
#include "draw.h"
#include "util.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"user32.lib")
#pragma warning(disable:4996)

#define BUFSIZE 512
#define BLACK 1
#define WHITE 2
#define INF 99999

void placeGo(int(*map)[15], int(*weight)[15], int go) { //가중치가 가장 높은 곳으로 착수하는 함수
	int x = 0, y = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (map[i][j] == BLACK || map[i][j] == WHITE) weight[i][j] = 0;
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (weight[i][j] >= weight[y][x]) y = i, x = j;
		}
	}
	gotoxy(53, 6);
	printf("                    ");
	gotoxy(53, 6);
	printf("착수위치: %c%d", 65 + x, 15 - y);
	map[y][x] = go;
}
int checkWin(int map[][15], int(*weight)[15], bool isMulti = false) { //게임이 끝났는지 확인하는 함수
	if (checkLine(map, weight, 5, BLACK, 0) == 1) {
		if (isMulti == false) {
			if (MessageBox(NULL, L"흑이 승리했습니다.\n한 판 더 플레이하시겠습니까?", L"알림", MB_YESNO) == IDYES)
				return 1;
			else
				return 2;
		}
		else if (isMulti == true) {
			MessageBox(NULL, L"흑이 승리했습니다.", L"알림", MB_OK);
			return 3;
		}
	}
	if (checkLine(map, weight, 5, WHITE, 0) == 1) {
		if (isMulti == false) {
			if (MessageBox(NULL, L"백이 승리했습니다.\n한 판 더 플레이하시겠습니까?", L"알림", MB_YESNO) == IDYES)
				return 1;
			else
				return 2;
		}
		else if (isMulti == true) {
			MessageBox(NULL, L"백이 승리했습니다.", L"알림", MB_OK);
			return 3;
		}
	}
	return 0;
}
void execTimer(int* time) { //1초마다 time변수를 1씩 증가시키는 함수
	while (1) {
		Sleep(1000);
		*time += 1;
	}
}
void clearBuffer(int size) { //입력 버퍼를 지우는 함수
	for (int i = 0; i < size; i++) {
		keybd_event(VK_BACK, 0, 0, 0);
		keybd_event(VK_BACK, 0, 0x0002, 0);
	}
}
void errorHandling(const char* message) { //에러를 출력하는 함수
	fputs(message, stderr);
	fputc('\n', stderr);
	system("pause > nul");
	exit(1);
}

int main() {
	int moveCount = 0;
	srand((unsigned)time(NULL));
MAIN:
	fflush(stdin);
	system("cls");
	int mode = mainMenu();
REGAME:
	system("cls");
	bool turn;
	int sectime = 0;
	int map[15][15] = {
		{3,7,7,7,7,7,7,7,7,7,7,7,7,7,4},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{10,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
		{5,9,9,9,9,9,9,9,9,9,9,9,9,9,6}
	};
	int weight[15][15] = { 0, };
	int(*mp)[15] = map;
	int(*wp)[15] = weight;
	int x = 7, y = 7;
	int game_over = 0;
	system("cls");
	fflush(stdin);
	clearBuffer(100);
	if (mode == 0) { //흑돌로 플레이
		_beginthreadex(NULL, 0, (_beginthreadex_proc_type)execTimer, (void*)&sectime, 0, NULL);
		turn = true;
		while (1) {
			printMap(map, BLACK, &sectime, &moveCount, false);
			game_over = checkWin(map, wp);
			if (game_over == 1) {
				goto REGAME;
			}
			else if (game_over == 2) {
				goto MAIN;
			}
			if (turn == true) {
				gotoxy(53, 5);
				printf("흑이 둘 차례입니다.");
				while (1) {
					for (int i = 0; i < 15; i++) {
						for (int j = 0; j < 15; j++) {
							if (map[i][j] > 10) map[i][j] -= 11;
						}
					}
					map[y][x] += 11;
					printMap(map, BLACK, &sectime, &moveCount, false);
					moveCount++;
					gotoxy(15 + x * 2, 5 + y);
					if (GetAsyncKeyState('W') & 0x0001 && y != 0) y--, moveCount = 0;
					else if (GetAsyncKeyState('A') & 0x0001 && x != 0) x--, moveCount = 0;
					else if (GetAsyncKeyState('S') & 0x0001 && y != 14) y++, moveCount = 0;
					else if (GetAsyncKeyState('D') & 0x0001 && x != 14) x++, moveCount = 0;
					else if (GetAsyncKeyState(' ') & 0x0001 && map[y][x] - 11 != 1 && map[y][x] - 11 != 2 && map[y][x] != 1 && map[y][x] != 2) {
						map[y][x] = 1;
						break;
					}
				}
				turn = false;
			}
			else {
				gotoxy(53, 5);
				printf("백이 둘 차례입니다.");
				initWeight(mp, wp, 1, 8); //가중치 초기화
				checkLine(map, wp, 2, BLACK, 250); //2줄 검색 
				checkLine(map, wp, 4, BLACK, 10000); //4줄 검색
				check11(map, wp, BLACK, 250); //11
				check3(map, wp, BLACK, 1000); //3
				check13(map, wp, BLACK, 10000); //13
				check31(map, wp, BLACK, 10000); //31
				check22(map, wp, BLACK, 10000); // 22
				check12(map, wp, BLACK, 1000); //12
				check21(map, wp, BLACK, 2100); //21
				checkLine(map, wp, 2, WHITE, 500); //2줄 검색 
				checkLine(map, wp, 4, WHITE, INF); //4줄 검색
				check11(map, wp, WHITE, 500); //11
				check3(map, wp, WHITE, 2000); //3
				check13(map, wp, WHITE, INF); //13
				check31(map, wp, WHITE, INF); //31
				check22(map, wp, WHITE, INF); // 22
				check12(map, wp, WHITE, 2000); //12
				check21(map, wp, WHITE, 2000); //21
				placeGo(mp, wp, WHITE);
				turn = true;
			}
		}
	}
	else if (mode == 2) { //백돌로 플레이
		_beginthreadex(NULL, 0, (_beginthreadex_proc_type)execTimer, (void*)&sectime, 0, NULL);
		turn = true;
		map[7][7] = BLACK;
		while (1) {
			printMap(map, WHITE, &sectime, &moveCount, false);
			game_over = checkWin(map, wp);
			if (game_over == 1) {
				goto REGAME;
			}
			else if (game_over == 2) {
				goto MAIN;
			}
			if (turn == true) {
				gotoxy(53, 5);
				printf("백이 둘 차례입니다.");
				while (1) {
					for (int i = 0; i < 15; i++) {
						for (int j = 0; j < 15; j++) {
							if (map[i][j] > 10) map[i][j] -= 11;
						}
					}
					map[y][x] += 11;
					printMap(map, WHITE, &sectime, &moveCount, false);
					moveCount++;
					gotoxy(15 + x * 2, 5 + y);
					if (GetAsyncKeyState('W') & 0x0001 && y != 0) y--, moveCount = 0;
					else if (GetAsyncKeyState('A') & 0x0001 && x != 0) x--, moveCount = 0;
					else if (GetAsyncKeyState('S') & 0x0001 && y != 14) y++, moveCount = 0;
					else if (GetAsyncKeyState('D') & 0x0001 && x != 14) x++, moveCount = 0;
					else if (GetAsyncKeyState(' ') & 0x0001 && map[y][x] - 11 != BLACK && map[y][x] - 11 != WHITE && map[y][x] != 1 && map[y][x] != 2) {
						map[y][x] = WHITE;
						break;
					}
				}
				turn = false;
			}
			else {
				gotoxy(53, 5);
				printf("흑이 둘 차례입니다.");
				initWeight(mp, wp, 8, 1); //가중치 초기화
				checkLine(map, wp, 2, WHITE, 250); //2줄 검색 
				checkLine(map, wp, 4, WHITE, 10000); //4줄 검색
				check11(map, wp, WHITE, 250); //11
				check3(map, wp, WHITE, 1000); //3
				check13(map, wp, WHITE, 10000); //13
				check31(map, wp, WHITE, 10000); //31
				check22(map, wp, WHITE, 10000); // 22
				check12(map, wp, WHITE, 1000); //12
				check21(map, wp, WHITE, 1000); //21
				checkLine(map, wp, 2, BLACK, 500); //2줄 검색 
				checkLine(map, wp, 3, BLACK, 2000); //3줄 검색
				checkLine(map, wp, 4, INF, 20000); //4줄 검색
				check11(map, wp, BLACK, 500); //11
				check3(map, wp, BLACK, 2000); //3
				check13(map, wp, BLACK, INF); //13
				check31(map, wp, BLACK, INF); //31
				check22(map, wp, BLACK, INF); // 22
				check12(map, wp, BLACK, 2000); //12
				check21(map, wp, BLACK, 2000); //21
				placeGo(mp, wp, BLACK);
				turn = true;
			}
		}
	}
	if (mode == 4) { //서버

		int dol = 0;
		int hy = 7, hx = 7;
		char temp[100];
		char* tok;
		int cnt;
		bool isStr = true;

		turn = true;

		WSADATA wsaData;
		SOCKET serv_sock, clnt_sock;
		SOCKADDR_IN serv_addr, clnt_addr;

		int strLen;
		char message[BUFSIZE] = { 0, };
		char data[BUFSIZE] = { 0, };
		int clntAdrSize;

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
			errorHandling("WSAStartup() Error!");


		serv_sock = socket(PF_INET, SOCK_STREAM, 0);

		if (serv_sock == INVALID_SOCKET)
			errorHandling("socket() error");

		memset(&serv_addr, 0, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(8080);

		if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) // 주소할당
			errorHandling("bind() error!");

		if (listen(serv_sock, 5) == SOCKET_ERROR)
			errorHandling("listen() error!");

		clntAdrSize = sizeof(clnt_addr);


		printf("\n");

		system("ipconfig | find \"IPv4\"");

		printf("\n연결을 기다리는 중입니다..\n");
		clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &clntAdrSize);

		strLen = recv(clnt_sock, message, BUFSIZE, 0);
		memset(data, 0, BUFSIZE);
		memcpy(data, message, strLen);
		if (strcmp(data, "BLACK\0") == 0) {
			printf("연결되었습니다!\n당신은 흑입니다.");
			dol = BLACK;
		}
		else if (strcmp(data, "WHITE\0") == 0) {
			printf("연결되었습니다!\n당신은 백입니다.");
			dol = WHITE;
		}
		Sleep(3000);
		_beginthreadex(NULL, 0, (_beginthreadex_proc_type)execTimer, (void*)&sectime, 0, NULL);
		system("cls");
		if (dol == BLACK) turn = true;
		else if (dol == WHITE) turn = false;
		gotoxy(53, 6);
		printf("                    ");
		gotoxy(53, 6);
		printf("착수위치: ");
		while (1) {
			printMap(map, BLACK, &sectime, &moveCount, true);
			game_over = checkWin(map, wp, true);
			if (game_over == 3) {
				closesocket(serv_sock);
				WSACleanup();
				goto MAIN;
			}
			if (turn == true) {
				gotoxy(53, 5);
				if (dol == BLACK) printf("흑이 둘 차례입니다.");
				else if (dol == WHITE) printf("백이 둘 차례입니다.");
				while (1) {
					for (int i = 0; i < 15; i++) {
						for (int j = 0; j < 15; j++) {
							if (map[i][j] > 10) map[i][j] -= 11;
						}
					}
					map[y][x] += 11;
					printMap(map, BLACK, &sectime, &moveCount, true);
					moveCount++;
					gotoxy(15 + x * 2, 5 + y);
					if (GetAsyncKeyState('W') & 0x0001 && y != 0) y--, moveCount = 0;
					else if (GetAsyncKeyState('A') & 0x0001 && x != 0) x--, moveCount = 0;
					else if (GetAsyncKeyState('S') & 0x0001 && y != 14) y++, moveCount = 0;
					else if (GetAsyncKeyState('D') & 0x0001 && x != 14) x++, moveCount = 0;
					else if (GetAsyncKeyState('T') & 0x0001) {
						clearBuffer(100);
						cnt = 0;
						memset(temp, 0, sizeof(temp));
						gotoxy(50, 20);
						printf("                                                                 ");
						gotoxy(50, 20);
						printf("나   > ");
						std::cin >> temp;
						for (unsigned int i = 0; i < strlen(temp) - 1; i++)
							if (temp[i] == ',') temp[i] = ' ';
						send(clnt_sock, temp, strlen(temp), 0);
						clearBuffer(100);
					}
					else if (GetAsyncKeyState(' ') & 0x0001 && map[y][x] - 11 != 1 && map[y][x] - 11 != 2 && map[y][x] != 1 && map[y][x] != 2) {
						map[y][x] = dol;

						memset(message, 0, sizeof(message));

						memset(temp, 0, sizeof(temp));
						_itoa(y, temp, 10);
						strcpy(message, temp);

						strcat(message, ",");

						memset(temp, 0, sizeof(temp));
						_itoa(x, temp, 10);
						strcat(message, temp);

						send(clnt_sock, message, strlen(message), 0);
						gotoxy(53, 6);
						printf("                    ");
						gotoxy(53, 6);
						printf("착수위치: %c%d", 65 + x, 15 - y);
						break;
					}
				}
				turn = false;
			}
			else {
				gotoxy(53, 5);
				if (dol == BLACK) printf("백이 둘 차례입니다.");
				else if (dol == WHITE) printf("흑이 둘 차례입니다.");

				memset(message, 0, sizeof(message));

				while (1) {

					isStr = true;
					strLen = recv(clnt_sock, message, BUFSIZE, 0);

					for (int i = 0; i < sizeof(message) - 1; i++) {
						if (message[i] == ',')
							isStr = false;
					}

					if (isStr == false) {
						tok = strtok(message, ",");
						hy = atoi(tok);

						tok = strtok(NULL, ",");
						hx = atoi(tok);

						if (dol == BLACK) map[hy][hx] = WHITE;
						else if (dol == WHITE) map[hy][hx] = BLACK;

						turn = true;
						gotoxy(53, 6);
						printf("                    ");
						gotoxy(53, 6);
						printf("착수위치: %c%d", 65 + hx, 15 - hy);
						break;
					}
					if (isStr == true) {
						gotoxy(50, 20);
						printf("                                                                 ");
						gotoxy(50, 20);
						printf("상대 > %s", message);
					}
				}
			}
		}
	}
	else if (mode == 6) { //클라이언트
		int dol;
		int hy = 7, hx = 7;
		char ip[20];
		char temp[100];
		int cnt;
		char* tok;
		bool isStr = true;

		turn = true;

		SOCKET sock;
		SOCKADDR_IN serveraddr;

		int retval;
		char buf[BUFSIZE + 1];
		int len;
		WSADATA wsa;


		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			return -1;

		sock = socket(AF_INET, SOCK_STREAM, 0);

		serveraddr.sin_family = AF_INET;
		printf("서버 IP를 입력하세요 : ");
		gets_s(ip);
		strcat(ip, "\0");
		serveraddr.sin_addr.s_addr = inet_addr(ip);
		serveraddr.sin_port = htons(8080);

		retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
		dol = rand() % 2 + 1;
		ZeroMemory(buf, sizeof(buf));
		if (dol == BLACK) {
			strcpy(buf, "WHITE\0"); //상대 돌
			printf("연결되었습니다!\n당신은 흑입니다.");
			retval = send(sock, buf, strlen(buf), 0);
		}
		if (dol == WHITE) {
			strcpy(buf, "BLACK\0");
			printf("연결되었습니다!\n당신은 백입니다.");
			retval = send(sock, buf, strlen(buf), 0);
		}
		Sleep(3000);
		system("cls");
		if (dol == BLACK) turn = true;
		else if (dol == WHITE) turn = false;
		_beginthreadex(NULL, 0, (_beginthreadex_proc_type)execTimer, (void*)&sectime, 0, NULL);
		gotoxy(53, 6);
		printf("                    ");
		gotoxy(53, 6);
		printf("착수위치: %c%d", 65 + x, 15 - y);
		while (1) {
			printMap(map, WHITE, &sectime, &moveCount, true);
			game_over = checkWin(map, wp, true);
			if (game_over == 3) {
				closesocket(sock);
				WSACleanup();
				goto MAIN;
			}
			if (turn == true) {
				gotoxy(53, 5);
				if (dol == BLACK) printf("흑이 둘 차례입니다.");
				else if (dol == WHITE) printf("백이 둘 차례입니다.");
				while (1) {
					for (int i = 0; i < 15; i++) {
						for (int j = 0; j < 15; j++) {
							if (map[i][j] > 10) map[i][j] -= 11;
						}
					}
					map[y][x] += 11;
					printMap(map, WHITE, &sectime, &moveCount, true);
					moveCount++;
					gotoxy(15 + x * 2, 5 + y);
					if (GetAsyncKeyState('W') & 0x0001 && y != 0) y--, moveCount = 0;
					else if (GetAsyncKeyState('A') & 0x0001 && x != 0) x--, moveCount = 0;
					else if (GetAsyncKeyState('S') & 0x0001 && y != 14) y++, moveCount = 0;
					else if (GetAsyncKeyState('D') & 0x0001 && x != 14) x++, moveCount = 0;
					else if (GetAsyncKeyState('T') & 0x0001) {
						clearBuffer(100);
						cnt = 0;
						memset(temp, 0, sizeof(temp));
						gotoxy(50, 20);
						printf("                                                                 ");
						gotoxy(50, 20);
						printf("나   > ");
						std::cin >> temp;
						for (unsigned int i = 0; i < strlen(temp) - 1; i++)
							if (temp[i] == ',') temp[i] = ' ';
						send(sock, temp, sizeof(temp), 0);
						clearBuffer(100);
					}
					else if (GetAsyncKeyState(' ') & 0x0001 && map[y][x] - 11 != 1 && map[y][x] - 11 != 2 && map[y][x] != 1 && map[y][x] != 2) {
						map[y][x] = dol;

						memset(buf, 0, sizeof(buf));
						memset(temp, 0, sizeof(temp));

						_itoa(y, temp, 10);
						strcpy(buf, temp);

						strcat(buf, ",");

						memset(temp, 0, sizeof(temp));
						_itoa(x, temp, 10);
						strcat(buf, temp);

						send(sock, buf, strlen(buf), 0);
						gotoxy(53, 6);
						printf("                    ");
						gotoxy(53, 6);
						printf("착수위치: %c%d", 65 + x, 15 - y);
						break;
					}
				}
				turn = false;
			}
			else {
				gotoxy(53, 5);
				if (dol == BLACK) printf("백이 둘 차례입니다.");
				else if (dol == WHITE) printf("흑이 둘 차례입니다.");

				memset(buf, 0, sizeof(buf));
				while (1) {

					isStr = true;
					len = recv(sock, buf, sizeof(buf), 0);

					for (int i = 0; i < sizeof(buf) - 1; i++) {
						if (buf[i] == ',')
							isStr = false;
					}

					if (isStr == false) {
						tok = strtok(buf, ",");
						hy = atoi(tok);

						tok = strtok(NULL, ",");
						hx = atoi(tok);

						if (dol == BLACK) map[hy][hx] = WHITE;
						else if (dol == WHITE) map[hy][hx] = BLACK;

						turn = true;
						gotoxy(53, 6);
						printf("                    ");
						gotoxy(53, 6);
						printf("착수위치: %c%d", 65 + hx, 15 - hy);
						break;
					}
					if (isStr == true) {
						gotoxy(50, 20);
						printf("                                                                 ");
						gotoxy(50, 20);
						printf("상대 > %s", buf);
					}
				}
			}
		}
	}
}