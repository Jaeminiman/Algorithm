#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int N;
vector<pair<int, int>> wire;
int cache[100][500];

int lis(int idx, int val) {
	//base case : 순회 종료
	if (idx == N) return 0;

	int& ret = cache[idx][val];
	if (ret != -1) return ret;

	if (wire[idx].second > val)
		ret = max(lis(idx + 1, val), lis(idx + 1, wire[idx].second) + 1);
	else {
		ret = lis(idx + 1, val);
	}
	return ret;
}
bool compare(pair<int,int> a, pair<int,int> b) {
	return a.first <= b.first;
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int left, right;
		cin >> left >> right;
		wire.push_back(make_pair(left, right));
	}
	sort(wire.begin(), wire.end(), compare);
	memset(cache, -1, sizeof(cache));

	int result = N - lis(0, 0);
	cout << result << endl;
	return 0;
}