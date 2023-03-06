#include <iostream>
#include <cstring>
using namespace std;
int N;
int board[16][16];
int DP[16][16][3];


int pipe(int y, int x, int stance) {
	
	// base case : ���� ���(����)
	if (y < 0 || y >= N || x < 0 || x >= N) {
		return 0;
	}
	// base case : ���� ����(����)
	if (board[y][x] == 1) {
		return 0;
	}
	// base case : ���� �밢������ ����(����)
	if (stance == 2) {
		if (board[y][x - 1] == 1 || board[y - 1][x] == 1) {
			return 0;
		}
	}
	// base case : ����
	// ������ ������ �� �ڿ��� �ϴ� ������, �밢���� ��Ȳ���� ���и� �����ؾ��ϱ� ����
	if (y == N - 1 && x == N - 1) {
		return 1;
	}
	int& ret = DP[y][x][stance];
	if (ret != -1) return ret;

	ret = 0;
	switch (stance) {
	case 1:
		ret = pipe(y, x + 1, 1) + pipe(y + 1, x + 1, 2);
		break;
	case 2:
		ret = pipe(y, x + 1, 1) + pipe(y + 1, x + 1, 2) + pipe(y + 1, x, 3);
		break;
	case 3:
		ret = pipe(y + 1, x + 1, 2) + pipe(y + 1, x, 3);
		break;
	}
	return ret;
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
		}
	}
	memset(DP, -1, sizeof(DP));
	int result = pipe(0, 1, 1);
	cout << result << endl;

	return 0;
}