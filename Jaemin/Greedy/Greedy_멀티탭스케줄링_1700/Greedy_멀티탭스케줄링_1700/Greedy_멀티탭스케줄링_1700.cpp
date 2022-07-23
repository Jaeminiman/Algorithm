#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;
int N, K;
vector<priority_queue<int,vector<int>,greater<int>>> database;
queue<int> S;
// consent는 다음에 올 전기용품 idx를 기준으로 정렬된 Container
multiset<pair<int,int>> consent;
const int INF = 123456789;
const int NO_USE = 123456;

// 넣고자하는 item의 가장 첫번째 등장할 idx와 consent에서 가장 먼저 다시 등장할 idx가 일치하면
// consent에 지금 넣으려는 item이 꽂혀있는 것임.
bool plug_check(int item) {
	pair<int, int> next = *consent.begin(); 

	//꽂혀있는 경우 처리
	if (next.second == item) {
		consent.erase(*consent.begin());
		if (!database[item].empty()) {
			next.first = database[item].top();
		}
		else {
			next.first = NO_USE;
		}
		consent.insert(next);
		return true;
	}
	return false;
}

int plug() {
	int cnt = 0;
	
	while (!S.empty()) {
		int item = S.front(); S.pop();
		database[item].pop();

		// 이미 꽂혀있지는 않은 경우
		if (!plug_check(item)) {


			// consent.erase(val)로 제거를 하니까 중복된 값이 모두 제거되는 문제가 발생함. iterator idx로 접근해야함!

			pair<int, int> target = *consent.rbegin(); 
			
			multiset<pair<int, int>>::iterator it = consent.find(target);
			consent.erase(it);
			// target.first = 해당 콘센트에 꽂힌 전기용품이 가장 빨리 다음으로 쓰이는 시점(INF면 안 꽂힌거)
			// consent.second = 해당 전기용품 번호

			// 꽂혀있는 consent가 target이면 무조건 뽑히므로 cnt ++
			if (target.first != INF) {
				cnt++;
			}

			if (!database[item].empty()) {
				target.first = database[item].top(); 
				target.second = item;
			}
			// 다음으로 안쓰인다면?
			else {
				target.first = NO_USE;
				target.second = item;
			}

			consent.insert(target);
		}
	}
	return cnt;
}

int main() {
	cin >> N >> K;
	// 자료구조 만들기
	for (int i = 0; i < 100; i++) {
		priority_queue<int, vector<int>, greater<int>> q;
		database.push_back(q);
	}
	// 콘센트 만들기
	for (int i = 0; i < N; i++) {
		consent.insert(make_pair(INF , -1));
	}

	for (int i = 0; i < K; i++) {
		int x;
		cin >> x;
		S.push(x - 1);
		database[x - 1].push(i);
	}
	int ret = plug();

	cout << ret << endl;

	return 0;
}
