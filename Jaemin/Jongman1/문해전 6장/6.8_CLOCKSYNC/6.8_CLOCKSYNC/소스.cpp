#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> button;
int need_button[16];
int clock_cnt[16] = {0};
int button_cnt[10] = { 0 };
int N;
int cnt = 0;
const int INF = 10000000;
int min_cnt = INF;

// 12시 가르키는지 체크
bool check() {
	bool okay = true;
	for (int i = 0; i < 16; i++) {
		if (need_button[i] != (clock_cnt[i]%4)) {
			okay = false;
			break;
		}
	}
	return okay;
}
void try_button(int idx) {

	//base case 1 : 같은 버튼 4번 이상 누른경우(실패)
	if (button_cnt[idx] > 3) {
		return;
	}
	//base case 2 : 모든 clock이 12시를 가르킴(need_button == clock_cnt)
	if (check()) {
		min_cnt = min(min_cnt, cnt);
		return;
	}

	for (int i = idx; i < 10; i++) {
		// 버튼을 누름
		button_cnt[i] += 1;
		cnt += 1;

		// 버튼을 눌렀을 때의 효과
		for (int j = 0; j < button[i].size(); j++) {
			int clock = button[i][j];
			clock_cnt[clock] += 1;
		}
		try_button(i);

		//후퇴
		button_cnt[i] += -1;
		cnt += -1;
		for (int j = 0; j < button[i].size(); j++) {
			int clock = button[i][j];
			clock_cnt[clock] -= 1;
		}
	}
}

void calculate_need() {
	int clk;
	
	for (int j = 0; j < 16; j++) {
		cin >> clk;
		need_button[j] = 4 - (clk / 3);
	}
	
}
void set_button() {
	button.push_back({ 0,1,2 });
	button.push_back({ 3,7,9,11});
	button.push_back({ 4,10,14,15 });
	button.push_back({ 0,4,5,6,7});
	button.push_back({ 6,7,8,10,12 });
	button.push_back({ 0,2,14,15});
	button.push_back({ 3,14,15});
	button.push_back({ 4,5,7,14,15});
	button.push_back({ 1,2,3,4,5});
	button.push_back({ 3,4,5,9,13 });
}
int main(void) {
	cin >> N;
	set_button();

	for (int i = 0; i < N; i++) {
		calculate_need();
		cnt = 0;
		try_button(0);
		if (min_cnt != INF) {
			cout << min_cnt << endl;
		}
		else {
			cout << -1 << endl;
		}
		min_cnt = INF;
	}
	

	return 0;
}