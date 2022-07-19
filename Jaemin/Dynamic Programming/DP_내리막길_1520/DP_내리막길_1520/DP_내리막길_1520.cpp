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
	//base case : 목표지점에 도달(성공)
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

		//board판 벗어난 경우. 이것을 기저사례로 처리하고자 했으나, 높이가 감소하는 조건을
		//만족시키는 애들만 계산값에 추가하는 조건문을 확인하기 위해서는 이전의 y,x와 이후의
		//nextX, nextY 값이 필요했기 때문에 여기서 한번에 처리할 수 밖에 없었음.
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