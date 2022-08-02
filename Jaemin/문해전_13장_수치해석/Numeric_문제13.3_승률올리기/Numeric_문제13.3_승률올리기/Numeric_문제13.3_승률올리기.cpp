#include <iostream>
using namespace std;

int C;
long long N, M;
int target;
const int MAX = 2000000000;

bool decision(long long x) {
	long long cand = ((M + x) * 100) / (N + x);
	return target <= cand;
}
int calc() {
	long long lo = 0, hi = MAX;
	for (int i = 0; i < 100; i++) {
		long long mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> C;
	for (int epoch = 0; epoch < C; epoch++) {
		cin >> N >> M;
		// (long long / long long)임에도, 백분율에서 100을 선제적으로 곱해
		// double 형 변환 필요 없이 1이상의 값이 나올 수 있도록 해줌.
		target = (M * 100) / N;
		target++;
		int ret = 0;
		if (decision(MAX))
			ret = calc();
		else
			ret = -1;

		cout << ret << '\n';
	}
}