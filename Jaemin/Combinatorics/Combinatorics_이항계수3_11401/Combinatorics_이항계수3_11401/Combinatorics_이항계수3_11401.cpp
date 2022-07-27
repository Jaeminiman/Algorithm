#include <iostream>
#include <map>

using namespace std;
int N, K;
map<int,map<int,int>> DP;

long long dp_combination_bi(int n, int k) {
	if (n == k || k == 0) {
		return 1;
	}
	if (n / 2 < k) {
		return dp_combination_bi(n, n - k);
	}

	auto it = DP.find(n);
	if (it != DP.end()) {
		// Memoization nCk가 있는지 check 있으면 그것 사용
		auto iter = it->second.find(k);
		if (iter != it->second.end()) return iter->second;
	}
	else {
		map<int, int> m;
		DP.insert({ n, m });
	}

	long long ret = 0;

	ret += dp_combination_bi(n - 1, k) + dp_combination_bi(n - 1, k - 1);
	ret %= 1000000007;


	auto it2 = DP.find(n);
	it2->second.insert({ k, ret });
	return ret;
}
long long dp_combination(int n, int k) {
	if (n == k || k == 0) {
		return 1;
	}
	if (n < k) {
		return 0;
	}
	// 시간 개선을 위해 절반 뒤집기
	if (n / 2 < k) {
		return dp_combination(n, n - k);
	}
	// combination 전환
	if (K > n / log2(n) && n < K) {
		return dp_combination_bi(n, k);
	}

	auto it = DP.find(n);
	if (it != DP.end()) {
		// Memoization nCk가 있는지 check 있으면 그것 사용
		auto iter = it->second.find(k);
		if (iter != it->second.end()) return iter->second;
	}
	else {
		map<int, int> m;
		DP.insert({ n, m});
	}
	
	long long ret = 0;
	if (n % 2 == 0) {
		for (int i = 0; i <= k; i++) {
			ret += (dp_combination(n / 2, i) * dp_combination(n / 2, k - i));
			ret %= 1000000007;
		}
	}
	
	else {
		
		for (int i = 0; i <= k; i++) {
			ret += (dp_combination(n / 2, i) * dp_combination(n / 2 + 1, k - i));
			ret %= 1000000007;
		}
	}

	auto it2 = DP.find(n);
	it2->second.insert({ k, ret });
	return ret;
}

int main() {
	cin >> N >> K;
	int result = dp_combination(N, K);
	cout << result << endl;
	return 0;
}