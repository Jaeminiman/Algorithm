#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
int N, K;
const int p = 1000000007;

long long fact(int n, int k) {
	long long ret = 1;
	for (int i = n; i > k; i--) {
		ret *= i;
		ret %= p;
	}
	return ret;
}
int main() {
	cin >> N >> K;
	

	long long left = fact(N, N - K);
	long long right = fact(K, 0);
	long long num = p - 2;
	long long right_pow = 1;
	while(num != 0){
		if (num % 2 != 0) {
			right_pow *= right;
			right_pow %= p;
		}
			right *= right;
			right %= p;
			num /= 2;
	}

	long long ret = (left * right_pow) % p;

	cout << ret << endl;

	return 0;
}