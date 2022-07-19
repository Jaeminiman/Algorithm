#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> int_int_pair;
using namespace std;
int N;
vector<int_int_pair> v;



bool comparator(const int_int_pair& l, const int_int_pair& r) {
	return l.first < r.first;
}

void start() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		v.push_back(int_int_pair(x,i));
	}
}
int main(void) {
	start();
	stable_sort(v.begin(), v.end(), comparator);

	// 이렇게 count하면 실질적으로 bubblesort를 직접 구현하는 것과
	// 시간 복잡도가 똑같아 진다.
	vector<int> cnt(N, 0);
	int shift = 0;
	for (int i = v.size() - 1; i >= 0; i--) {
		shift += i - v[i].second + cnt[v[i].second];
		for (int j = v[i].second; j < v.size(); j++) {
			cnt[j]++;
		}
	}
	cout << shift << endl;
	
	return 0;
}