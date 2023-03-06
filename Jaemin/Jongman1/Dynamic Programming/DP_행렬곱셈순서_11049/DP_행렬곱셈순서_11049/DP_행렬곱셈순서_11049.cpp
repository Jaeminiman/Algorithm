#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int N;
vector<pair<int, int>> mat;
int DP[500][500];
const int INF = 123456789;
int ORDER(int start, int last) {
	//base case : 시작과 끝이 같음. 연산 종료
	if (start == last) {
		return 0;
	}

	int& ret = DP[start][last];
	if (ret != -1) return ret;

	ret = INF;
	for (int line = start; line < last; line++) {
		ret = min(ret, ORDER(start, line) + ORDER(line + 1, last) + 
			mat[start].first * mat[line].second * mat[last].second);
	}
	return ret;
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a, b;
		cin >> a >> b;
		mat.push_back(make_pair(a, b));
	}
	memset(DP, -1, sizeof(DP));
	int result = ORDER(0, N - 1);
	cout << result << endl;
	return 0;
}