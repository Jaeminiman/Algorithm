#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int T;
int n, k;
vector<int> C;
vector<int> R;

// 시간 복잡도 : O(nlgn) -> sort때문
bool decision(long double x) {
	vector<long double> v;
	for (int i = 0; i < n; i++) {
		v.push_back(x * C[i] - R[i]);
	}
	sort(v.begin(), v.end(),greater<long double>());
	long double cum = 0;
	for (int i = 0; i < k; i++) {
		cum += v[i];
	}
	return cum >= 0;
}
long double optimization() {
	long double lo = 0, hi = 1;
	for (int i = 0; i < 100; i++) {
		long double mid = (lo + hi) / 2;
		if (decision(mid)) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}
	return hi;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	for (int epoch = 0; epoch < T; epoch++) {
		cin >> n >> k;
		C.clear(); R.clear();
		for (int i = 0; i < n; i++) {
			int c, r;
			cin >> r >> c;
			C.push_back(c);
			R.push_back(r);
		}
		cout << fixed;
		cout.precision(10);
		cout << optimization() << '\n';
	}
	return 0;
}