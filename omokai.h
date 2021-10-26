#pragma once
#define BLACK 1
#define WHITE 2

void check13(int(*map)[15], int(*weight)[15], int go, int score) {

	for (int i = 0; i < 11; i++) { //세로
		for (int j = 0; j < 15; j++) {
			if (map[i][j] == go && map[i + 2][j] == go && map[i + 3][j] == go && map[i + 4][j] == go)
				weight[i + 1][j] += score;
		}
	}
	for (int i = 0; i < 15; i++) { //가로
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i][j + 2] == go && map[i][j + 3] == go && map[i][j + 4] == go)
				weight[i][j + 1] += score;
		}
	}
	for (int i = 0; i < 11; i++) { //대각선
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i + 2][j + 2] == go && map[i + 3][j + 3] == go && map[i + 4][j + 4] == go)
				weight[i + 1][j + 1] += score;
		}
	}
	for (int i = 4; i < 15; i++) { //대각선
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i - 2][j + 2] == go && map[i - 3][j + 3] == go && map[i - 4][j + 4] == go)
				weight[i - 1][j + 1] += score;
		}
	}
}

void check31(int(*map)[15], int(*weight)[15], int go, int score) {
	for (int i = 0; i < 11; i++) { //세로
		for (int j = 0; j < 15; j++) {
			if (map[i][j] == go && map[i + 1][j] == go && map[i + 2][j] == go && map[i + 4][j] == go)
				weight[i + 3][j] += score;
		}
	}
	for (int i = 0; i < 15; i++) { //가로
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i][j + 1] == go && map[i][j + 2] == go && map[i][j + 4] == go)
				weight[i][j + 3] += score;
		}
	}
	for (int i = 0; i < 11; i++) { //대각선
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i + 1][j + 1] == go && map[i + 2][j + 2] == go && map[i + 4][j + 4] == go)
				weight[i + 3][j + 3] += score;
		}
	}
	for (int i = 4; i < 15; i++) { //대각선
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i - 1][j + 1] == go && map[i - 2][j + 2] == go && map[i - 4][j + 4] == go)
				weight[i - 3][j + 3] += score;
		}
	}

}

void check22(int(*map)[15], int(*weight)[15], int go, int score) {
	for (int i = 0; i < 11; i++) { //세로
		for (int j = 0; j < 15; j++) {
			if (map[i][j] == go && map[i + 1][j] == go && map[i + 3][j] == go && map[i + 4][j] == go)
				weight[i + 2][j] += score;
		}
	}
	for (int i = 0; i < 15; i++) { //세로
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i][j + 1] == go && map[i][j + 3] == go && map[i][j + 4] == go)
				weight[i][j + 2] += score;
		}
	}
	for (int i = 0; i < 11; i++) { //대각선
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i + 1][j + 1] == go && map[i + 3][j + 3] == go && map[i + 4][j + 4] == go)
				weight[i + 2][j + 2] += score;
		}
	}
	for (int i = 4; i < 15; i++) { //대각선
		for (int j = 0; j < 11; j++) {
			if (map[i][j] == go && map[i - 1][j + 1] == go && map[i - 3][j + 3] == go && map[i - 4][j + 4] == go)
				weight[i - 2][j + 2] += score;
		}
	}
}

void check12(int(*map)[15], int(*weight)[15], int go, int score) {
	for (int i = 1; i < 11; i++) { //세로
		for (int j = 0; j < 15; j++) {
			if (map[i][j] == go && map[i + 1][j] != BLACK && map[i + 1][j] != WHITE && map[i + 2][j] == go && map[i + 3][j] == go) {
				if (map[i - 1][j] != BLACK && map[i - 1][j] != WHITE && map[i + 4][j] != BLACK && map[i + 4][j] != WHITE)
					weight[i + 1][j] += score;
			}
		}
	}
	for (int i = 0; i < 15; i++) { //가로
		for (int j = 1; j < 12; j++) {
			if (map[i][j] == go && map[i][j + 1] != BLACK && map[i][j + 1] != WHITE && map[i][j + 2] == go && map[i][j + 3] == go) {
				if (map[i][j - 1] != BLACK && map[i][j - 1] != WHITE && map[i][j + 4] != BLACK && map[i][j + 4] != WHITE)
					weight[i][j + 1] += score;
			}
		}
	}
	for (int i = 1; i < 12; i++) { //대각선
		for (int j = 1; j < 12; j++) {
			if (map[i][j] == go && map[i + 1][j + 1] != BLACK && map[i + 1][j + 1] != WHITE && map[i + 2][j + 2] == go && map[i + 3][j + 3] == go) {
				if (map[i - 1][j - 1] != BLACK && map[i - 1][j - 1] != WHITE && map[i + 4][j + 4] != BLACK && map[i + 4][j + 4] != WHITE)
					weight[i + 1][j + 1] += score;
			}
		}
	}
	for (int i = 1; i < 12; i++) { //대각선
		for (int j = 4; j < 11; j++) {
			if (map[i][j] == go && map[i + 1][j - 1] != BLACK && map[i + 1][j - 1] != WHITE && map[i + 2][j - 2] == go && map[i + 3][j - 3] == go) {
				if (map[i - 1][j + 1] != BLACK && map[i - 1][j + 1] != WHITE && map[i + 4][j - 4] != BLACK && map[i + 4][j - 4] != WHITE)
					weight[i + 1][j - 1] += score;
			}
		}
	}
}

void check21(int(*map)[15], int(*weight)[15], int go, int score) {
	for (int i = 1; i < 12; i++) { //세로
		for (int j = 0; j < 15; j++) {
			if (map[i][j] == go && map[i + 1][j] == go && map[i + 2][j] != BLACK && map[i + 2][j] != WHITE && map[i + 3][j] == go) {
				if (map[i - 1][j] != BLACK && map[i - 1][j] != WHITE && map[i + 4][j] != BLACK && map[i + 4][j] != WHITE)
					weight[i + 2][j] += score;
			}
		}
	}
	for (int i = 0; i < 15; i++) { //가로
		for (int j = 1; j < 12; j++) {
			if (map[i][j] == go && map[i][j + 1] == go && map[i][j + 2] != BLACK && map[i][j + 2] != WHITE && map[i][j + 3] == go) {
				if (map[i][j - 1] != BLACK && map[i][j - 1] != WHITE && map[i][j + 4] != BLACK && map[i][j + 4] != WHITE)
					weight[i][j + 2] += score;
			}
		}
	}
	for (int i = 0; i < 12; i++) { //대각선
		for (int j = 0; j < 12; j++) {
			if (map[i][j] == go && map[i + 1][j + 1] == go && map[i + 2][j + 2] != BLACK && map[i + 2][j + 2] != WHITE && map[i + 3][j + 3] == go) {
				if (map[i - 1][j - 1] != BLACK && map[i - 1][j - 1] != WHITE && map[i + 4][j + 4] != BLACK && map[i + 4][j + 4] != WHITE)
					weight[i + 2][j + 2] += score;
			}
		}
	}
	for (int i = 1; i < 12; i++) { //대각선
		for (int j = 4; j < 11; j++) {
			if (map[i][j] == go && map[i + 1][j - 1] == go && map[i + 2][j - 2] != BLACK && map[i + 2][j + 2] != WHITE && map[i + 3][j - 3] == go) {
				if (map[i - 1][j + 1] != BLACK && map[i - 1][j + 1] != WHITE && map[i + 4][j - 4] != BLACK && map[i + 4][j - 4] != WHITE)
					weight[i + 2][j - 2] += score;
			}
		}
	}
}
void check11(int(*map)[15], int(*weight)[15], int go, int score) {
	for (int i = 0; i < 10; i++) { //세로
		for (int j = 0; j < 15; j++) {
			if (map[i + 1][j] == go && map[i + 2][j] != BLACK && map[i + 2][j] != WHITE && map[i + 3][j] == go) {
				if (map[i][j] != BLACK && map[i][j] != WHITE) {
					weight[i][j] += score;
				}
				if (map[i + 4][j] != BLACK && map[i + 4][j] != WHITE) {
					weight[i + 4][j] += score;
				}
			}
		}
	}
	for (int i = 0; i < 15; i++) { //가로
		for (int j = 0; j < 10; j++) {
			if (map[i][j + 1] == go && map[i][j + 2] != BLACK && map[i][j + 2] != WHITE && map[i][j + 3] == go) { //1 0 1
				if (map[i][j] != BLACK && map[i][j] != WHITE) {// 0 1 0 1 0
					weight[i][j] += score;
				}
				if (map[i][j + 4] != BLACK && map[i][j + 4] != WHITE) {
					weight[i][j + 4] += score;
				}
			}
		}
	}
	for (int i = 0; i < 11; i++) { //대각선
		for (int j = 0; j < 11; j++) {
			if (map[i + 1][j + 1] == go && map[i + 2][j + 2] != BLACK && map[i + 2][j + 2] != WHITE && map[i + 3][j + 3] == go) { //1 0 1
				if (map[i][j] != BLACK && map[i][j] != WHITE) {// 0 1 0 1 0
					weight[i][j] += score;
				}
				if (map[i + 4][j + 4] != BLACK && map[i + 4][j + 4] != WHITE) {
					weight[i + 4][j + 4] += score;
				}
			}
		}
	}
	for (int i = 4; i < 15; i++) { //대각선
		for (int j = 0; j < 10; j++) {
			if (map[i - 1][j + 1] == go && map[i - 2][j + 2] != BLACK && map[i - 2][j + 2] != WHITE && map[i - 3][j + 3] == go) {
				if (map[i][j] != BLACK && map[i][j] != WHITE) {
					weight[i][j] += score;
				}
				if (map[i - 4][j + 4] != BLACK && map[i - 4][j + 4] != WHITE)
					weight[i - 4][j + 4] += score;
			}
		}
	}
}

void check3(int(*map)[15], int(*weight)[15], int go, int score) {
	for (int i = 1; i < 14; i++) { //세로
		for (int j = 0; j < 15; j++) {
			if (map[i][j] == go && map[i + 1][j] == go && map[i + 2][j] == go) {
				if (map[i - 1][j] != BLACK && map[i - 1][j] != WHITE && map[i + 3][j] != BLACK && map[i + 3][j] != WHITE) {
					weight[i - 1][j] += score;
					weight[i + 3][j] += score;
				}
				else if (map[i - 1][j] != BLACK && map[i - 1][j] != WHITE) {
					weight[i - 1][j] += score/2;
				}
				else if (map[i + 3][j] != BLACK && map[i + 3][j] != WHITE) {
					weight[i + 3][j] += score/2;
				}
			}
		}
	}
	for (int i = 0; i < 15; i++) { //가로
		for (int j = 1; j < 14; j++) {
			if (map[i][j] == go && map[i][j + 1] == go && map[i][j + 2] == go) {
				if (map[i][j - 1] != BLACK && map[i][j - 1] != WHITE && map[i][j + 3] != BLACK && map[i][j + 3] != WHITE) {
					weight[i][j - 1] += score;
					weight[i][j + 3] += score;
				}
				if (map[i][j - 1] != BLACK && map[i][j - 1] != WHITE) {
					weight[i][j - 1] += score / 2;
				}
				if (map[i][j + 3] != BLACK && map[i][j + 3] != WHITE) {
					weight[i][j + 3] += score / 2;
				}
			}
		}
	}
	for (int i = 1; i < 14; i++) { //대각선
		for (int j = 1; j < 14; j++) {
			if (map[i][j] == go && map[i + 1][j + 1] == go && map[i + 2][j + 2] == go) {
				if (map[i - 1][j - 1] != BLACK && map[i - 1][j - 1] != WHITE && map[i + 3][j + 3] != BLACK && map[i + 3][j + 3] != WHITE) {
					weight[i - 1][j - 1] += score;
					weight[i + 3][j + 3] += score;
				}
				if (map[i - 1][j - 1] != BLACK && map[i - 1][j - 1] != WHITE) {
					weight[i - 1][j - 1] += score / 2;
				}
				if (map[i + 3][j + 3] != BLACK && map[i + 3][j + 3] != WHITE) {
					weight[i + 3][j + 3] += score / 2;
				}
			}
		}
	}
	for (int i = 3; i < 14; i++) { //대각선
		for (int j = 1; j < 14; j++) {
			if (map[i][j] == go && map[i - 1][j + 1] == go && map[i - 2][j + 2] == go) {
				if (map[i + 1][j - 1] != BLACK && map[i + 1][j - 1] != WHITE && map[i - 3][j + 3] != BLACK && map[i - 3][j + 3] != WHITE) {
					weight[i][j - 1] += score;
					weight[i - 3][j + 3] += score;
				}
				if (map[i + 1][j - 1] != BLACK && map[i + 1][j - 1] != WHITE) {
					weight[i][j - 1] += score / 2;
				}
				if (map[i - 3][j + 3] != BLACK && map[i - 3][j + 3] != WHITE) {
					weight[i - 3][j + 3] += score / 2;
				}
			}
		}
	}
}

int checkLine(int map[][15], int(*weight)[15], int line, int ele, int score) {
	bool find;
	for (int i = 1; i < 15 - line; i++) { //세로 찾기
		for (int j = 0; j < 15; j++) {
			find = true;
			for (int k = 0; k < line; k++) {
				if (map[i + k][j] != ele) find = false;
			}
			if (find == true) {
				if (line == 5) return true;
				weight[i - 1][j] += score;
				weight[i + line][j] += score;
			}
		}
	}
	for (int i = 0; i < 15; i++) { //가로 찾기
		for (int j = 1; j < 15 - line; j++) {
			find = true;
			for (int k = 0; k < line; k++) {
				if (map[i][j + k] != ele) find = false;
			}
			if (find == true) {
				if (line == 5) return true;
				weight[i][j - 1] += score;
				weight[i][j + line] += score;
			}
		}
	}
	for (int i = 1; i < 15 - line; i++) { //대각선 찾기
		for (int j = 1; j < 15 - line; j++) {
			find = true;
			for (int k = 0; k < line; k++) {
				if (map[i + k][j + k] != ele) find = false;
			}
			if (find == true) {
				if (line == 5) return true;
				weight[i - 1][j - 1] += score;
				weight[i + line][j + line] += score;
			}
		}
	}
	for (int i = line; i < 15; i++) { //대각선 찾기
		for (int j = 1; j < 15 - line; j++) {
			find = true;
			for (int k = 0; k < line; k++) {
				if (map[i - k][j + k] != ele) find = false;
			}
			if (find == true) {
				if (line == 5) return true;
				weight[i + 1][j - 1] += score;
				weight[i - line][j + line] += score;
			}
		}
	}
	return 0;
}

void initWeight(int(*map)[15], int(*weight)[15], int score1, int score2) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			weight[i][j] = 0;
		}
	}
	for (int i = 1; i < 14; i++) {
		for (int j = 1; j < 14; j++) {
			if (map[i][j] == BLACK) {
				weight[i - 1][j] += score1;
				weight[i - 1][j - 1] += score1;
				weight[i][j - 1] += score1;
				weight[i + 1][j - 1] += score1;
				weight[i + 1][j] += score1;
				weight[i + 1][j + 1] += score1;
				weight[i][j + 1] += score1;
				weight[i - 1][j + 1] += score1;
			}
			else if (map[i][j] == WHITE) {
				weight[i - 1][j] += score2;
				weight[i - 1][j - 1] += score2;
				weight[i][j - 1] += score2;
				weight[i + 1][j - 1] += score2;
				weight[i + 1][j] += score2;
				weight[i + 1][j + 1] += score2;
				weight[i][j + 1] += score2;
				weight[i - 1][j + 1] += score2;
			}
		}
	}
}