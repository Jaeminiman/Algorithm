#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int T;
int N, K;
vector<int> L;
vector<int> M;
vector<int> G;


bool decision(int d) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (d < L[i] - M[i]) {
			continue;
		}
		else {
			int intersect = min(d, L[i]) - (L[i] - M[i]);
			cnt += intersect / G[i] + 1;
		}
	}
	return cnt >= K;
}
int search() {
	int lo = 0, hi = 8030000;
	for (int i = 0; i < 100; i++) {
		int mid = (lo + hi) / 2;
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

	cin >> T;
	for (int epoch = 0; epoch < T; epoch++) {
		cin >> N >> K;
		int l, m, g;
		L.clear(); M.clear(); G.clear();
		for (int i = 0; i < N; i++) {
			cin >> l >> m >> g;
			L.push_back(l);
			M.push_back(m);
			G.push_back(g);
		}
		cout << search() << '\n';
	}
	return 0;
}