#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
int N;
int cache[100001][3]; // 1.2MB
int board[100000][3];
const int NEGINF = -123456;
const int INF = 123456;

int des_min(int y, int x) {
	//base case : 끝 도달(종료)
	if (y == N) return 0;
	//base case : x범위 벗어남(실패)
	if (x < 0 || x >= 3) return INF;

	// y 시작을 -1로 하기위한 tool
	int& ret = cache[y + 1][x];
	if (ret != -1) return ret;

	//y시작을 -1로 하기위한 tool 2
	int point = (y == -1) ? 0 : board[y][x];
	ret = min(des_min(y + 1, x - 1) + point, des_min(y + 1, x) + point);
	ret = min(ret, des_min(y + 1, x + 1) + point);
	return ret;
}
int des_max(int y, int x) {
	//base case : 끝 도달(종료)
	if (y == N) {
		return 0;
	}
	//base case : x범위 벗어남(실패)
	if (x < 0 || x >= 3) return NEGINF;

	// y 시작을 -1로 하기위한 tool
	int& ret = cache[y + 1][x];
	if (ret != -1) return ret;

	//y시작을 -1로 하기위한 tool 2
	int point = (y == -1) ? 0 : board[y][x];
	ret = max(des_max(y + 1, x - 1) + point, des_max(y + 1, x) + point);
	ret = max(ret, des_max(y + 1, x + 1) + point);
	return ret;
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> board[i][j];
		}
	}
	memset(cache, -1, sizeof(cache));
	int max_result = des_max(-1, 1);

	memset(cache, -1, sizeof(cache));
	int min_result = des_min(-1, 1);
	cout << to_string(max_result) + " " + to_string(min_result) << endl;
	return 0;
}