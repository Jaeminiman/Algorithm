#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int N, K;
int value[100] = {0,}; // 400B
int cache[99][10001]; // 4MB이다.. => 40KB 활용 가능

int coin(int idx, int val) {
	//base case : idx가 끝에 도달한 경우(성공)
	if (idx == N - 1) {
		return 1;
	}

	int& ret = cache[idx - 1][val];
	if (ret != -1) return ret;

	ret = 0;
	int nextVal = val;
	int t = 1;

	while (nextVal >= 0) {
		ret += coin(idx + 1, nextVal);
		nextVal = val - t * value[idx];
		t++;
	}
	return ret;
}
bool desc(int a, int b) {
	return a > b;
}
void start() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> value[i];
	}
	sort(value, value + 100, desc);
	memset(cache, -1, sizeof(cache));
}
int main() {
	start();
	int result = coin(0, K);
	cout << result << endl;

	return 0;
}