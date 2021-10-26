#pragma once
#include <Windows.h>

void gotoxy(short x, short y) { //Ŀ�� �̵� �Լ�
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void cursorView(bool visible) { //Ŀ�� Ȱ��ȭ / ��Ȱ��ȭ �Լ�
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}