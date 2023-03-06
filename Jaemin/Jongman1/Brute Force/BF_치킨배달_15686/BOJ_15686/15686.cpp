#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
vector<pair<int,int>> chicken;
vector<pair<int, int>> house;
vector<int> selected_chicken;
int board[50][50];
int N, M;
int total;
int const INF = 1000000;
int min_total = INF;


void calculate() {
	
	total = 0;
	for (int i = 0; i < house.size(); i++) {
		int y_h = house[i].first;
		int x_h = house[i].second;
		
		int dist;
		int min_dist = INF;
		for (int j = 0; j < selected_chicken.size(); j++) {
			int idx = selected_chicken[j];
			int y_c = chicken[idx].first;
			int x_c = chicken[idx].second;
			
			dist = abs(x_h - x_c) + abs(y_h - y_c);
			min_dist = min(dist, min_dist);
		}
		total += min_dist;
	}
	min_total = min(total, min_total);
}
void do_chicken(int remain, int idx) {
	//base case 1 : 성공 => 치킨 거리 계산
	if (remain == 0) {
		calculate();
		return;
	}
	//base case 2 : 범위 벗어남(실패)
	if (idx >= chicken.size()) {
		return;
	}

	for (int i = idx; i < chicken.size(); i++) {
		selected_chicken.push_back(i);
		do_chicken(remain - 1, i + 1);
		selected_chicken.pop_back();
	}
}
void set_board() {
	cin >> N;
	cin >> M;
	string line;
	string stringBuffer;
	vector<string> x;
	x.clear();

	getline(cin, line);
	for (int i = 0; i < N; i++) {
		getline(cin, line);
		istringstream ss(line);

		while (getline(ss, stringBuffer, ' ')) {
			x.push_back(stringBuffer);
		}
		for (int j = 0; j < x.size(); j++) {
			int num = stoi(x[j]);
			board[i][j] = num;
			if (num == 1) {
				house.push_back({ i,j });
			}
			else if (num == 2) {
				chicken.push_back({ i,j });
			}
		}
		x.clear();
	}
}
int main() {
	set_board();
	do_chicken(M,0);

	cout << min_total;
	return 0;
}

// 특이사항 : chicken과 house를 벡터로 따로 관리하니까 코드 짜기가
// 정말 수월했다.