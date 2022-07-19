#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int N, M;
int S[2000];
int DP[2001][2001];

bool pelindrom(int start, int last) {
	//base case : 성공
	if (start >= last) {
		return true;
	}

	int& ret = DP[start][last];
	if (ret != -1) return ret;

	ret = (S[start] == S[last]) ? pelindrom(start + 1, last - 1) : 0;
	return ret;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> S[i];
	}
	memset(DP, -1, sizeof(DP));
	cin >> M;
	for (int i = 0; i < M; i++) {
		int start, last;
		cin >> start >> last;
		// idx input이 나의 방식보다 idx가 하나 많으니까 빼줘서 넣어줌
		cout << pelindrom(start - 1, last - 1) << '\n';
	}
	return 0;
}