#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
int cache[500][500];
int N, M;
int board[500][500]; // 1MB
const int direction[4][2] = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int des(int y, int x) {
	//base case : ��ǥ������ ����(����)
	if (y == N - 1 && x == M - 1) {
		return 1;
	}

	int& ret = cache[y][x];
	if (ret != -1) return ret;

	int nextY, nextX;
	ret = 0;
	for (int d = 0; d < 4; d++) {
		nextY = y + direction[d][0];
		nextX = x + direction[d][1];

		//board�� ��� ���. �̰��� ������ʷ� ó���ϰ��� ������, ���̰� �����ϴ� ������
		//������Ű�� �ֵ鸸 ��갪�� �߰��ϴ� ���ǹ��� Ȯ���ϱ� ���ؼ��� ������ y,x�� ������
		//nextX, nextY ���� �ʿ��߱� ������ ���⼭ �ѹ��� ó���� �� �ۿ� ������.
		if (nextY >= N || nextY < 0 || nextX >= M || nextX < 0) {
			continue;
		}
		if (board[y][x] > board[nextY][nextX]) {
			ret += des(nextY, nextX);
		}	
	}
	return ret;
}

void start() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
	memset(cache, -1, sizeof(cache));
}
int main() {
	start();
	int result = des(0, 0);
	cout << result << endl;

	return 0;
}