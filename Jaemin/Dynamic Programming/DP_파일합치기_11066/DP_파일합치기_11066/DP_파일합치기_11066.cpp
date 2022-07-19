#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int K, T;
vector<int> files;
int DP[500][500];
const int INF = 123456789;

int Merge(int start, int last) {
	//base case : 시작과 끝이 같음. 연산 종료
	if (start == last) {
		return 0;
	}

	int& ret = DP[start][last];
	if (ret != -1) return ret;

	ret = INF;
	int cost = 0;
	for (int i = start; i <= last; i++) {
		cost += files[i];
	}
	for (int line = start; line < last; line++) {
		ret = min(ret, Merge(start, line) + Merge(line + 1, last) + cost);
	}
	return ret;
}
int main() {
	cin >> T;
	for (int epoch = 0; epoch < T; epoch++) {
		cin >> K;
		for (int i = 0; i < K; i++) {
			int a;
			cin >> a;
			files.push_back(a);
		}
		memset(DP, -1, sizeof(DP));
		int result = Merge(0, K - 1);
		cout << result << endl;
		files.clear();
	}

	return 0;
}