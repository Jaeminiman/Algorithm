#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
int board[500][500]; // 1MB
int cache[500][500]; // 1MB
const int direction[4][2] = {
	{-1, 0}, {1,0}, {0,-1}, {0,1}
};

int move(int y, int x) {
	int& ret = cache[y][x];
	if (ret != -1) return ret;

	int nextY, nextX;
	ret = 1;
	for (int d = 0; d < 4; d++) {
		nextY = y + direction[d][0];
		nextX = x + direction[d][1];
		if (nextY < N && nextY >= 0 && nextX < N && nextX >= 0) {
			// 이전의 y,x와 nextY, nextX를 비교하는 작업이므로 base case로 빼지않고
			// 밖에서 처리해야 가지고 들어가는 정보가 최소화된다. 따라서 nextY,nextX범위
			// 체크도 여기서 해줘야함.
			if (board[y][x] < board[nextY][nextX]) {
				ret = max(ret, move(nextY, nextX) + 1);
			}
		}
		
	}
	return ret;
}
void start() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];
			cache[i][j] = -1;
		}
	}
}
int main() {
	start();
	vector<int> result;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			result.push_back(move(i, j));
		}
	}
	cout << *max_element(result.begin(), result.end()) << endl;
	return 0;
}