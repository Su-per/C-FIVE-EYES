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
	printf("雜熱嬪纂: ");
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
			if (map[i][j] == 0) printf("托 ");
			else if (map[i][j] == BLACK)
				printf("≒");  //?瘚?
			else if (map[i][j] == WHITE) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (6 << 4));
				printf("≒");  //寥給
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (6 << 4));
			}
			else if (map[i][j] == 3) printf("忙式");
			else if (map[i][j] == 4) printf("忖");
			else if (map[i][j] == 5) printf("戌式");
			else if (map[i][j] == 6) printf("戎");
			else if (map[i][j] == 7 and map[i][j + 1] == BLACK) printf("成 ");
			else if (map[i][j] == 7 and map[i][j + 1] != 1) printf("成式");
			else if (map[i][j] == 8) printf("扣");
			else if (map[i][j] == 9 and map[i][j + 1] == BLACK) printf("扛 ");
			else if (map[i][j] == 9 and map[i][j + 1] != BLACK) printf("扛式");
			else if (map[i][j] == 10) printf("戍式");
			else if (map[i][j] > 10) printf("﹤");
		}
		printf(" \n");
	}
	if (dol == BLACK) {
		gotoxy(2, 5);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (6 << 4));
		if (isMulti == false)
			printf("≒COMPUTER ");
		else
			printf("≒OPPONENT ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 | (6 << 4));
		gotoxy(2, 6);
		printf("≒");  //寥給
		if (isMulti == false)
			printf("PLAYER   ");
		else
			printf("YOU      ");
	}
	else if (dol == WHITE) {
		gotoxy(2, 5);
		if (isMulti == false)
			printf("≒COMPUTER ");
		else
			printf("≒OPPONENT ");
		gotoxy(2, 6);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7 | (6 << 4));
		printf("≒");  //寥給
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

int mainMenu() { //詭檣詭景 轎溘 л熱
	char ment[300] = " *褻濛酈*\n W A S D蒂 鱔п 雜熱 嬪纂蒂 摹鷗м棲棻.\n Space蒂 鱔п 雜熱м棲棻.\n T蒂 揚楝 鼻渠寞婁 瓣たй 熱 氈蝗棲棻.\n\n  *詩じ Ы溯檜*\n 憮幗縑 菟橫陞 陽朝 憮幗 儅撩濠曖 嬴檜Я 輿模蒂 殮溘п 蕾樓м棲棻.\n 諼睡 啻お錶觼縑憮 蕾樓 衛 8080んお曖 んおん錶註檜 в蹂й 熱 氈蝗棲棻.";
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
	printf("?瘚僩? Ы溯檜ж晦");
	gotoxy(50, 17);
	printf("寥給煎 Ы溯檜ж晦");
	gotoxy(53, 19);
	printf("詩じ Ы溯檜");
	gotoxy(54, 21);
	printf(" ぅ饜葬橡");
	gotoxy(54, 23);
	printf("啪歜 謙猿");
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
				printf("\n嬴鼠 酈釭 揚楝 詭景煎 檜翕м棲棻.");
				system("pause > nul");
				goto MAINMENU;
			}
			if (y != 4) return y;
			system("cls");
			printTitle();
			gotoxy(53, 15);
			printf("憮幗 虜菟晦");
			gotoxy(54, 17);
			printf("憮幗 翱唸");
			gotoxy(54, 19);
			printf("菴煎 陛晦");
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