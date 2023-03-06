#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int begin[100] = { 0, }, end[100] = { 0, };

int schedule(void) {
	vector<pair<int, int>> order;
	for (int i = 0; i < n; ++i) {
		order.push_back(make_pair(end[i], begin[i]));
	}
	// end 끝나는 시간 기준으로 오름차순 정렬하여 O(nlgn)을 보장!!!! Sort 중요! nlgn은 sorting에 의한 소요시간임.
	sort(order.begin(), order.end());

	// earliest : 다음 회의가 시작할 수 있는 가장 빠른 시간
	// selected : 지금까지 선택한 회의 수
	int earliest = 0, selected = 0;
	for (int i = 0; i < n; i++) {
		int meetingBegin = order[i].second, meetingEnd = order[i].first;

		if (earliest <= meetingBegin) {
			earliest = meetingEnd;
			selected++;
		}
	}
	return selected;
}

int main() {
	cout << schedule() << endl;
	return 0;
}