#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int N, M;
int S[2000];
int DP[2000][2000] = {0,};

void pelindrom() {

	for (int mid = 0; mid < N; mid++) {
		// 홀수 개수에 대한 DP 계산
		int start = mid, last = mid;
		while (start >= 0 && start < N && last >= 0 && last < N) {
			if (S[start] != S[last]) {
				break;
			}
			else {
				int size = last - start + 1;
				DP[mid][size] = 1;
			}
			start--;
			last++;
		}
		// 짝수 개수에 대한 DP 계산
		start = mid, last = mid + 1;
		while (start >= 0 && start < N && last >= 0 && last < N) {
			if (S[start] != S[last]) {
				break;
			}
			else {
				int size = last - start + 1;
				DP[mid][size] = 1;
			}
			start--;
			last++;
		}
	}

}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> S[i];
	}

	pelindrom();

	cin >> M;
	for (int i = 0; i < M; i++) {
		int start, last;
		cin >>  start >> last;
		int mid = (start + last - 2)/2;
		int size = last - start + 1;
		cout << DP[mid][size] << '\n';
	}
	return 0;
}