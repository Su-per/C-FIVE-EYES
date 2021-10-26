#pragma once
#include <stdio.h>
#include <conio.h>
#include "util.h"
#define BLACK 1
#define WHITE 2
void printMap(int map[][15], int dol, int* time, int* moveCount, bool isMulti) {
	int hh = *time / 3600;
	int mm = (*time % 3600) / 60;
	int ss = *time %= 60;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (map[i][j] > 10 && ss % 3 == 0 && *moveCount > 2) map[i][j] -= 11;
		}
	}
	gotoxy(53, 6);
	printf("착수위치: ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (6 << 4));
	gotoxy(0, 0);
	for (int i = 0; i < 16; i++) {
		if (i != 15)
			gotoxy(15, 5 + i);
		if (i == 15) {
			gotoxy(13, 5 + i);
			printf("  ");
		}
		for (int j = 0; j < 15; j++) {
			if (i == 15) {
				if (j < 14) printf("%c ", 65 + j);
				if (j == 14) printf("%c", 65 + j);
				continue;
			}
			if (map[i][j] == 0) printf("┼ ");
			else if (map[i][j] == BLACK)
				printf("●");  //흑돌
			else if (map[i][j] == WHITE) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (6 << 4));
				printf("●");  //백돌
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (6 << 4));
			}
			else if (map[i][j] == 3) printf("┌─");
			else if (map[i][j] == 4) printf("┐");
			else if (map[i][j] == 5) printf("└─");
			else if (map[i][j] == 6) printf("┘");
			else if (map[i][j] == 7 and map[i][j + 1] == BLACK) printf("┬ ");
			else if (map[i][j] == 7 and map[i][j + 1] != 1) printf("┬─");
			else if (map[i][j] == 8) printf("┤");
			else if (map[i][j] == 9 and map[i][j + 1] == BLACK) printf("┴ ");
			else if (map[i][j] == 9 and map[i][j + 1] != BLACK) printf("┴─");
			else if (map[i][j] == 10) printf("├─");
			else if (map[i][j] > 10) printf("□");
		}
		printf(" \n");
	}
	if (dol == BLACK) {
		gotoxy(2, 5);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (6 << 4));
		if (isMulti == false)
			printf("●COMPUTER ");
		else
			printf("●OPPONENT ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (6 << 4));
		gotoxy(2, 6);
		printf("●");  //백돌
		if (isMulti == false)
			printf("PLAYER   ");
		else
			printf("YOU      ");
	}
	else if (dol == WHITE) {
		gotoxy(2, 5);
		if (isMulti == false)
			printf("●COMPUTER ");
		else
			printf("●OPPONENT ");
		gotoxy(2, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (6 << 4));
		printf("●");  //백돌
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (6 << 4));
		if (isMulti == false)
			printf("PLAYER   ");
		else
			printf("YOU      ");
	}
	for (int i = 0; i < 15; i++) {
		gotoxy(13, 5 + i);
		if (i > 5)
			printf(" %d", 15 - i);
		else
			printf("%d", 15 - i);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11 | (0 << 4));
	gotoxy(22, 57);
	printf("\n\n             %02d : %02d : %02d", hh, mm, ss);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (0 << 4));
}

void printTitle() {
	gotoxy(30, 3);
	printf("______  _____  _   _  _____          _____ __   __ _____  _____ \n");
	gotoxy(30, 4);
	printf("|  ___||_   _|| | | ||  ___|        |  ___|\\ \\ / /|  ___|/  ___|\n");
	gotoxy(30, 5);
	printf("| |_     | |  | | | || |__          | |__   \\ V / | |__  \\ `--. \n");
	gotoxy(30, 6);
	printf("|  _|    | |  | | | ||  __|         |  __|   \\ /  |  __|  `--. \\n");
	gotoxy(30, 7);
	printf("| |     _| |_ \\ \\_/ /| |___         | |___   | |  | |___ /\\__/ /\n");
	gotoxy(30, 8);
	printf("\\_|     \\___/  \\___/ \\____/         \\____/   \\_/  \\____/ \\____/ \n");
}

int mainMenu() { //메인메뉴 출력 함수
	char ment[300] = " *조작키*\n W A S D를 통해 착수 위치를 선택합니다.\n Space를 통해 착수합니다.\n T를 눌러 상대방과 채팅할 수 있습니다.\n\n  *멀티 플레이*\n 서버에 들어갈 때는 서버 생성자의 아이피 주소를 입력해 접속합니다.\n 외부 네트워크에서 접속 시 8080포트의 포트포워딩이 필요할 수 있습니다.";
	short y = 0;
	char in;
	bool showSlowly;
	cursorView(false);
	system("title FIVE EYES");
	system("mode con cols=120 lines=30");
MAINMENU:
	system("cls");
	printTitle();
	gotoxy(50, 15);
	printf("흑돌로 플레이하기");
	gotoxy(50, 17);
	printf("백돌로 플레이하기");
	gotoxy(53, 19);
	printf("멀티 플레이");
	gotoxy(54, 21);
	printf(" 튜토리얼");
	gotoxy(54, 23);
	printf("게임 종료");
	while (1) {
		gotoxy(46, y + 15);
		printf(">");
		in = _getch();
		gotoxy(46, y + 15);
		printf("  ");
		if (in == 'w' && y != 0)
			y -= 2;
		else if (in == 's' && y != 8)
			y += 2;
		else if (in == 13) {
			if (y == 6) {
				showSlowly = true;
				system("cls");
				for (int i = 0; ment[i] != NULL; i += 2) {
					printf("%c%c", ment[i], ment[i + 1]);
					if (_kbhit())
						showSlowly = false;
					if (showSlowly == true) Sleep(20);
				}
				printf("\n아무 키나 눌러 메뉴로 이동합니다.");
				system("pause > nul");
				goto MAINMENU;
			}
			if (y != 4) return y;
			system("cls");
			printTitle();
			gotoxy(53, 15);
			printf("서버 만들기");
			gotoxy(54, 17);
			printf("서버 연결");
			gotoxy(54, 19);
			printf("뒤로 가기");
			while (1) {
				gotoxy(46, y + 15);
				printf(">");
				in = _getch();
				gotoxy(46, y + 15);
				printf("  ");
				if (in == 'w' && y != 0)
					y -= 2;
				else if (in == 's' && y != 4)
					y += 2;
				else if (in == 13) {
					if (y == 0) return 4;
					else if (y == 2) return 6;
					else if (y == 4) goto MAINMENU;
				}
			}
		}
	}
}