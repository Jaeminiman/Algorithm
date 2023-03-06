#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
vector<int> food;
long long total = 0;
const int MOD = 1000000007;


long long power(int x, int num) {
	long long ret = 1;
	long long a = x;
	while (num != 0) {
		if (num % 2 == 1) {
			ret *= a;
			ret %= MOD;
		}
		a *= a;
		a %= MOD;
		num /= 2;
	}
	return ret;
}
void calc() {
	// hi 제외하고 한 개 이상 선택한 경우
	for (int hi = food.size() - 1; hi >= 0 ; hi--) {
		long long plus_scovil = (food[hi] * (power(2, hi) - 1)) % MOD;
		long long minus_scovil = (food[hi] * (power(2, N - hi - 1) - 1))%MOD;
		total += plus_scovil;
		total -= minus_scovil;
		
		total %= MOD;
		
		
		
	}

	return;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		food.push_back(x);
	}
	sort(food.begin(), food.end());
	calc();
	if (total < 0) {
		total += MOD;
	}
	cout << total << '\n';
	return 0;
}