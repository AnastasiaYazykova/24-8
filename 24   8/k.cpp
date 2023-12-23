#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "k.h"
#include <tchar.h>
#include <stdio.h>



#define N 10
#define M 15

#define WIDTH 30
#define HEIGHT 20


int steps = 0;
int gold = 0;







// Коды ячеек:
// 0 - свободна
// 1 - игрок
// 2 - препятствие
// 3 - золото
int map[N][M] = {
	{0, 0, 0, 0, 0,   0, 0, 0, 0, 0,   0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0,   0, 0, 0, 0, 3,   0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,   0, 0, 0, 0, 3,   0, 0, 0, 0, 0},
	{0, 0, 0, 3, 3,   3, 3, 0, 0, 0,   3, 3, 0, 0, 0},
	{0, 0, 0, 0, 0,   0, 3, 0, 0, 0,   3, 3, 0, 0, 0},

	{0, 0, 0, 0, 0,   0, 3, 3, 3, 0,   0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0,   0, 0, 0, 3, 0,   2, 0, 0, 2, 0},
	{0, 0, 0, 0, 0,   0, 0, 2, 0, 0,   2, 0, 0, 2, 0},
	{0, 0, 0, 0, 0,   0, 2, 2, 2, 2,   2, 2, 2, 2, 0},
	{0, 0, 0, 0, 0,   0, 0, 0, 0, 0,   0, 0, 0, 0, 0}
};

void drawMap(HDC hdc) {
	// кисть для пустого поля
	HBRUSH hBrushEmptyCell = CreateSolidBrush(RGB(200, 200, 200)); // серый
	// кисть для поля с золотом
	HBRUSH hBrushGold = CreateSolidBrush(RGB(255, 255, 0)); // желтый
	// кисть для стены
	HBRUSH hBrushWall = CreateSolidBrush(RGB(0, 0, 0)); // черный
	// кисть для игрока
	HBRUSH hBrushMan = CreateSolidBrush(RGB(0, 0, 255)); // синий

	// Коды ячеек:
	// 0 - свободна
	// 1 - игрок
	// 2 - препятствие
	// 3 - золото
	HBRUSH brush[4] = { hBrushEmptyCell, hBrushMan, hBrushWall, hBrushGold };

	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {

			int x1 = j * WIDTH;
			int x2 = (j + 1) * WIDTH;
			int y1 = i * HEIGHT;
			int y2 = (i + 1) * HEIGHT;

			RECT r = { x1, y1, x2, y2 };
			FillRect(hdc, &r, brush[map[i][j]]);
		}
	}


	// Все кисти удаляем!!!
	for (i = 0; i < 4; i++)
		DeleteObject(brush[i]);


	char strC[80];
	sprintf(strC, "steps=%d  gold=%d", steps, gold);

	TCHAR  strWin[80];
	OemToChar(strC, strWin);

	HFONT hFont = CreateFont(HEIGHT, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0, 0, L"Courier New");

	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 128));

	TextOut(hdc, 10, HEIGHT * N, (LPCWSTR)strWin, _tcslen(strWin));

	DeleteObject(hFont);
}












void Left() {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 1; j < M; j++) {
			if (map[i][j] == 1) { // если в map[i][j]  игрок
				if (map[i][j - 1] == 0) { // если слева от игрока - пустая клетка
					map[i][j - 1] = 1;
					map[i][j] = 0;
					steps++;
				}
				else if (map[i][j - 1] == 3) {// если слева от игрока - золото
					map[i][j - 1] = 1;
					map[i][j] = 0;
					steps++;
					gold++;
				}
			}
		}
	}
}

void Right() {
	int i, j;

	for (i = 0; i < N; i++) {

		for (j = M - 2; j >= 0; j--) {

			if (map[i][j] == 1) { // если в map[i][j]  игрок
				if (map[i][j + 1] == 0) {
					map[i][j + 1] = 1;
					map[i][j] = 0;
					steps++;
				}
				else if (map[i][j + 1] == 3) {
					map[i][j + 1] = 1;
					map[i][j] = 0;
					steps++;
					gold++;
				}
			}
		}
	}
}


void Up() {
	int i, j;

	for (i = 1; i < N; i++) {

		for (j = 0; j < M; j++) {

			if (map[i][j] == 1) { // если в map[i][j]  игрок
				if (map[i - 1][j] == 0) {
					map[i - 1][j] = 1;
					map[i][j] = 0;
					steps++;
				}
				else if (map[i - 1][j] == 3) {
					map[i - 1][j] = 1;
					map[i][j] = 0;
					steps++;
					gold++;
				}
			}
		}
	}
}

void Down() {
	int i, j;

	for (i = N - 2; i >= 0; i--) {

		for (j = 0; j < M; j++) {

			if (map[i][j] == 1) { // если в map[i][j]  игрок
				if (map[i + 1][j] == 0) {
					map[i + 1][j] = 1;
					map[i][j] = 0;
					steps++;
				}
				else if (map[i + 1][j] == 3) {
					map[i + 1][j] = 1;
					map[i][j] = 0;
					steps++;
					gold++;
				}
			}
		}
	}
}



void wall() {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 1; j < M; j++) {
			if (map[i][j] == 1) { // если в map[i][j]  игрок
				if (map[i][j - 1] == 0) { // если слева от игрока - пустая клетка
					map[i][j - 1] = 2;
					map[i][j] = 1;
					steps++;
				}
				else if (map[i][j - 1] == 3) {// если слева от игрока - золото
					map[i][j - 1] = 1;
					map[i][j] = 0;
					steps++;
					gold++;
				}
			}
		}
	}
}


void zoloto() {
	int i, j;

	for (i = 0; i < N; i++) {

		for (j = M - 2; j >= 0; j--) {

			if (map[i][j] == 1) { // если в map[i][j]  игрок
				if (map[i][j + 1] == 0) {
					map[i][j + 1] = 3;
					map[i][j] = 1;
					steps++;
				}
				else if (map[i][j + 1] == 3) {
					map[i][j + 1] = 1;
					map[i][j] = 0;
					steps++;
					gold++;
				}
			}
		}
	}
}




void Up12() {
	int i, j;

	for (i = 1; i < N; i++) {

		for (j = 0; j < M; j++) {

			if (map[i][j] == 1) { // если в map[i][j]  игрок
				if (map[i - 1][j] == 2) {
					map[i - 1][j] = 0;
					map[i][j] = 1;
					steps++;
				}
				else if (map[i - 1][j] == 3) {
					map[i - 1][j] = 1;
					map[i][j] = 0;
					steps++;
					gold++;
				}
			}
		}
	}
}

void Down12() {
	int i, j;

	for (i = N - 2; i >= 0; i--) {

		for (j = 0; j < M; j++) {

			if (map[i][j] == 1) { // если в map[i][j]  игрок
				if (map[i + 1][j] == 2) {
					map[i + 1][j] = 3;
					map[i][j] = 1;
					steps++;
				}
				else if (map[i + 1][j] == 3) {
					map[i + 1][j] = 1;
					map[i][j] = 0;
					steps++;
					gold++;
				}
			}
		}
	}
}

void domidas(int i, int j) {
	if (map[i][j] == 2) {
		map[i][j] = 3;
		if (i > 0) domidas(i - 1, j);
		if (i < N - 1) domidas(i + 1, j);
		if (j > 0) domidas(i, j - 1);
		if (j < M - 1) domidas(i, j + 1);
	}
}

void midas() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M - 1; ++j) {
			if (map[i][j] == 1 && map[i][j+1] == 2) {
				domidas(i, j + 1);
			}
		}
	}
}
