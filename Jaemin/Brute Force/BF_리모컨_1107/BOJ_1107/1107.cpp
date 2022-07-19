#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<bool> num(10,true);
int N;
int M;

bool check(int channel) {
	string s = to_string(channel);
	for (int i = 0; i < s.size(); i++) {
		if (!num[s[i] - '0']) {
			return false;
		}
	}
	return true;
}

void start() {
	cin >> N;
	cin >> M;

	// 초기 고장난 버튼 처리
	for (int i = 0; i < M; i++) {
		int taboo_num;
		cin >> taboo_num;
		num[taboo_num] = false;
	}
}

int main(void) {
	start();
	string str = to_string(N);

	int min_cnt = abs(N - 100);
	for (int i = 0; i < 1000000; i++) {
		if (check(i)) {
			int cnt = abs(N - i) + to_string(i).size();
			min_cnt = min(min_cnt, cnt);
		}
	}

	cout << min_cnt << endl;

	return 0;
}