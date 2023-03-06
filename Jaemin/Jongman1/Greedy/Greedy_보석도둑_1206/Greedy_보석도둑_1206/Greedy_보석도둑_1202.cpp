#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

struct cmp {
	// ��ġ �ִ��ΰ� max�� ������(��ġ�� pair.second�� ��ġ�ϹǷ�) a < b�� return�ؾ� ����������!
	bool operator()(pair<int, int> a, pair<int, int> b) {
		return a.second < b.second;
	}
};
int K, N;
priority_queue<pair<int, int>,vector<pair<int,int>>, cmp> item;
multiset<int> bags;

long long int jewel() {
	long long int values = 0;

	while(!item.empty() && !bags.empty()){
		pair<int, int> max_item = item.top(); item.pop();
		// ��ġ�� �ִ��� ������ V_max�� Weight���� ū ���� �� ���� ���� �� �����ϰ� ä���(erase)
		// bag�� ���� �뷮 ū ���� ���� �����ִ� item�� ���Ժ��� ũ�ų� ���� ��쿡�� ����
		if (*bags.rbegin() >= max_item.first) {
			bags.erase(bags.lower_bound(max_item.first));
			values += max_item.second;
		}
		
	}
	return values;
}
void start() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int weight, value;
		cin >> weight >> value;
		item.push(make_pair(weight, value));
	}
	for (int i = 0; i < K; i++) {
		int bag;
		cin >> bag;
		bags.insert(bag);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	start();
	long long int ret = jewel();

	cout << ret << '\n';
	return 0;
}