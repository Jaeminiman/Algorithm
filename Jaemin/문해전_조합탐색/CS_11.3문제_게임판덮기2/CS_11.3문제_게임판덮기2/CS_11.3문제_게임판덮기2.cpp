#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int T, H, W, R, C;
int board[10][10];
int block[4][10][10];
int best;

void set_block(int y, int x) {
	int size = max(R, C);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			
		}
	}
}
void cover(int y, int x) {

	// base case : 보드판 벗어남
	if (y > H - R || y < 0 || x < 0 || x > W - C) return;

	int nextY, nextX;
	for (int i = y; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if ((i == y) && j < x) continue;

		}
	}
	for (int rot = 0; rot < 4; rot++) {

	}
}
void rotate() {
	for (int i = 1; i < 4; i++) {
		for (int y = 0; y < R; y++) {
			int newX = R - y;
			for (int x = 0; x < C; x++) {
				int newY = x;
				block[i][newY][newX] = block[i-1][y][x];
			}
		}
	}
}
void start() {
	cin >> H >> W;
	cin >> R >> C;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			block[0][i][j] = 0;
			board[i][j] = 0;
		}
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			cin >> board[i][j];
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int x;
			cin >> x;
			if (x != '.') {
				block[0][i][j] = 1;
			}
		}
	}
}
int main() {
	cin >> T;
	for (int epoch = 0; epoch < T; epoch++) {
		start();
		rotate();

	}
}