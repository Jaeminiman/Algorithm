#include <iostream>
#include <vector>
using namespace std;
int board[12][12];
struct Point {
	int y, x;
};
vector<Point> cand;
const int direction[4][2] = {
	{0,1},{1,0},{-1,0},{0,-1}
};

void search() {
	int nextY, nextX;
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			int bulb_cnt = 0;
			for (int d = 0; d < 4; d++) {
				nextY = i + direction[d][0];
				nextX = j + direction[d][1];
				if (board[nextY][nextX] == -1 || board[nextY][nextX] == 1) {
					bulb_cnt++;
				}
			}
			if (bulb_cnt >= 3) {
				cand.push_back({ i,j });
			}
		}
	}
	
}
int main() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (i == 0 || i == 11 || j == 0 || j == 11) {
				board[i][j] = -1;
				continue;
			}
			char ch;
			cin >> ch;
			if (ch == '#') {
				board[i][j] = 0;
			}
			else {
				board[i][j] = 1;
			}
		}
	}
	search();


	return 0;
}