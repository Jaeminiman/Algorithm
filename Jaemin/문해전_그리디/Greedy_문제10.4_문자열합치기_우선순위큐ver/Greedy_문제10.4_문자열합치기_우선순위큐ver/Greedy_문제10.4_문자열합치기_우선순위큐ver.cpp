#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int C, N;
// greater<int>�� ����Ͽ� int�� ���� ���� �켱�Ѵ�.(min_heap)
// ū ������ �Ϸ��� less<�ڷ���>���� �Ѵ�.
// <�ڷ���, ����ü, �񱳿�����>�� ����
priority_queue<int, vector<int>, greater<int>> q;

int merge() {
	int cost = 0;
	while(q.size() > 1){
		// multiset�� Ȱ���ϴµ� �־ idx������ �������. �׷��� begin()�� ������ ��
		// �ִ� ������ �̷������� �غ��� �� �־���.
		// �ٸ� multiset�� �������δ�, ���� �Ź� ������ �� �ʿ䰡 �����ٴ� ���̴�.
		// �׷��� �����˻�Ʈ���� �̿��ؼ� max, min ���� ���� �� ���� Heap(�켱���� ť)�� ����ϴ� ���� �̷Ӵ�.

		int min_1 = q.top(); q.pop();
		int min_2 = q.top(); q.pop();
		q.push(min_1 + min_2);
		cost += min_1 + min_2;
	}
	q.pop();
	return cost;
}
void start() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		q.push(x);
	}
}
int main() {
	cin >> C;

	for (int epoch = 0; epoch < C; epoch++) {
		start();
		int ret = merge();
		cout << ret << endl;
	}
	return 0;
}