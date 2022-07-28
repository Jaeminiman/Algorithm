#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
int M, N, K;
const int p = 1000000007;
long long factorial[4000001];
void fact() {
	factorial[0] = 1;
	for (int i = 0; i < 4000000; i++) {
		factorial[i + 1] = factorial[i] * (i + 1);
		factorial[i + 1] %= p;
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	// 팩토리얼 DP 생성 O(N)
	fact();
	cin >> M;
	for (int epoch = 0; epoch < M; epoch++) {
		cin >> N >> K;

		long long left = factorial[N];
		long long mid = factorial[N-K];
		long long right = factorial[K];
		long long num = p - 2;

		long long right_pow = 1;
		long long mid_pow = 1;
		while (num != 0) {
			if (num % 2 != 0) {
				right_pow *= right;
				right_pow %= p;
				mid_pow *= mid;
				mid_pow %= p;
			}
			mid *= mid;
			mid %= p;
			right *= right;
			right %= p;
			num /= 2;
		}

		long long ret = ((left * right_pow) % p * mid_pow) % p;

		cout << ret << '\n';
	}

	return 0;
}