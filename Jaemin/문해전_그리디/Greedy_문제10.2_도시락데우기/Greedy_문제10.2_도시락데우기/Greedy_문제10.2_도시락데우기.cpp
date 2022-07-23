#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int C, N;
vector<pair<int,int>> Time;
vector<int> heatTime;
vector<int> eatTime;

// 내림차순 정렬
bool compare(pair<int,int> a, pair<int,int> b) {
	return a.first > b.first;
}
int main() {
	cin >> C;

	for (int epoch = 0; epoch < C; epoch++) {
		Time.clear();
		heatTime.clear();
		eatTime.clear();

		cin >> N;
		for (int i = 0; i < N; i++) {
			int t;
			cin >> t;
			heatTime.push_back(t);
		}
		for (int i = 0; i < N; i++) {
			int t;
			cin >> t;
			eatTime.push_back(t);
		}
		for (int i = 0; i < N; i++) {
			int heat = heatTime[i], eat = eatTime[i];
			Time.push_back(make_pair(eat, heat));
		}
		sort(Time.begin(), Time.end(), compare);
		
		int total_time = 0, can_heat_time = 0;
		for (int i = 0; i < N; i++){
			can_heat_time += Time[i].second;
			total_time = max(total_time, can_heat_time + Time[i].first);
		}

		cout << total_time << endl;

	}
	return 0;
}