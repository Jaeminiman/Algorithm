#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
int C, N;
multiset<int> costs;

int merge() {
	int cost = 0;

	for (int i = 0; i < N - 1; i++) {
		// multiset�� Ȱ���ϴµ� �־ idx������ �������. �׷��� begin()�� ������ ��
		// �ִ� ������ �̷������� �غ��� �� �־���.
		// �ٸ� multiset�� �������δ�, ���� �Ź� ������ �� �ʿ䰡 �����ٴ� ���̴�.
		// �׷��� �����˻�Ʈ���� �̿��ؼ� max, min ���� ���� �� ���� Heap(�켱���� ť)�� ����ϴ� ���� �̷Ӵ�.

		int min_1 = *costs.begin();
		costs.erase(costs.begin());
		int min_2 = *costs.begin();
		costs.erase(costs.begin());

		costs.insert(min_1 + min_2);
		cost += min_1 + min_2;
	}
	return cost;
}
void start() {
	cin >> N;
	costs.clear();

	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		costs.insert(x);
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