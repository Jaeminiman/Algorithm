#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int T, n, m;

// eaters[food] : food를 먹을 수 있는 친구들 번호
vector<int> eaters[50];
vector<int> edible; // set Cover문제에서, edible같은 것을 불린이 아닌 정수형으로 하여, 덮었다 빼는 것을 용이하게 함.
vector<int> peoples[50];
int best = 123456789;

void slowSearch(int select) {
	// 간단한 가지치기
	if (best <= select) return;
	
	auto it = find(edible.begin(), edible.end(), 0);
	// 기저 사례 : 모든 음식에 대해 만들지 여부를 결정했으면,
	// 모든 친구가 음식을 먹을 수 있는지를 확인하고 그렇다면 최적해를 갱신한다.
	if (it == edible.end()) {
		best = select;
		return;
	}

	int hungry_man = it - edible.begin();;

	for (int cand = 0; cand < peoples[hungry_man].size(); cand++) {
		int food = peoples[hungry_man][cand];

		// 만드는 경우
		vector<int> tmp = eaters[food];
		for (int i = 0; i < tmp.size(); i++) {
			edible[tmp[i]] += 1;
		}
		slowSearch(select + 1);

		for (int i = 0; i < tmp.size(); i++) {
			edible[tmp[i]] -= 1;
		}
	}
	return;
}
void start() {
	cin >> n >> m;
	best = 123456789;
	edible.clear();
	for (int i = 0; i < 50; i++) {
		eaters[i].clear();
		peoples[i].clear();
	}

	vector<string> people;

	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		people.push_back(s);
		edible.push_back(0);
	}

	for (int i = 0; i < m; i++) {
		int num;
		string s;
		cin >> num;
		for (int j = 0; j < num; j++) {
			cin >> s;
			int man = find(people.begin(), people.end(), s) - people.begin();
			eaters[i].push_back(man);
			peoples[man].push_back(i);
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> T;
	for (int epoch = 0; epoch < T; epoch++) {
		start();
		slowSearch(0);
		cout << best << '\n';
	}
	return 0;
}