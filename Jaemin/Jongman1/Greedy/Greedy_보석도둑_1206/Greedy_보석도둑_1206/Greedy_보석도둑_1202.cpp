#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

struct cmp {
	// 가치 최대인게 max로 오도록(가치가 pair.second에 위치하므로) a < b를 return해야 내림차순임!
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
		// 가치가 최대인 아이템 V_max의 Weight보다 큰 가방 중 가장 작은 것 선택하고 채우기(erase)
		// bag의 가장 용량 큰 것이 지금 보고있는 item의 무게보단 크거나 같은 경우에만 진입
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