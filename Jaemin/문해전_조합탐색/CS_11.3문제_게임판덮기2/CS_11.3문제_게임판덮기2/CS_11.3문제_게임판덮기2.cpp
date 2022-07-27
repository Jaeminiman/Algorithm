#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int T, H, W, R, C;
int board[10][10];
vector<pair<int,int>> block[4];
int best;

void set_block(int y, int x) {
}
void cover(int y, int x) {

	// base case : 보드판 벗어남
	if (y > H - R || y < 0 || x < 0 || x > W - C) return;

	for (int i = y; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if ((i == y) && j < x) continue;

		}
	}
	for (int rot = 0; rot < 4; rot++) {
		vector<pair<int, int>> tmp = block[rot];
		vector<pair<int, int>> v;
		while (!tmp.empty()) {
			pair<int, int> relative_loc = tmp.back(); tmp.pop_back();
			int abs_y = relative_loc.first + y; int abs_x = relative_loc.second + x;
			// 해당 rot block은 놓을 수 없다는 뜻. 종료.
			if (board[abs_y][abs_x] != 0) {
				v.clear();
				break;
			}
			v.push_back(make_pair(abs_y, abs_x));
		}
		while (!v.empty()) {
			pair<int, int> abs_loc = v.back(); v.pop_back();
			board[abs_loc.first][abs_loc.second] = 1;
		}
		
	}
}
void rotate() {
	for (int i = 0; i < 3; i++) {
		vector<pair<int, int>> tmp = block[i];
		while (!tmp.empty()) {
			pair<int, int> loc = tmp.back();
			tmp.pop_back();
			int newX = (C - 1) - loc.first; int newY = loc.second;
			block[i + 1].push_back(make_pair(newY, newX));
		}
	}
}
void start() {
	cin >> H >> W;
	cin >> R >> C;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = 0;
		}
		block[i].clear();
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			char ch;
			cin >> ch;
			if (ch != '.') {
				board[i][j] = 1;
			}
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			char x;
			cin >> x;
			if (x != '.') {
				block[0].push_back(make_pair(i,j));
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