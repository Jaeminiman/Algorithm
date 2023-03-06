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
	// end ������ �ð� �������� �������� �����Ͽ� O(nlgn)�� ����!!!! Sort �߿�! nlgn�� sorting�� ���� �ҿ�ð���.
	sort(order.begin(), order.end());

	// earliest : ���� ȸ�ǰ� ������ �� �ִ� ���� ���� �ð�
	// selected : ���ݱ��� ������ ȸ�� ��
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