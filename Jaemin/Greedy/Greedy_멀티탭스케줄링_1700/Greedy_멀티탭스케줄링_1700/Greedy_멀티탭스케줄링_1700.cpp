#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;
int N, K;
vector<priority_queue<int,vector<int>,greater<int>>> database;
queue<int> S;
// consent�� ������ �� �����ǰ idx�� �������� ���ĵ� Container
multiset<pair<int,int>> consent;
const int INF = 123456789;
const int NO_USE = 123456;

// �ְ����ϴ� item�� ���� ù��° ������ idx�� consent���� ���� ���� �ٽ� ������ idx�� ��ġ�ϸ�
// consent�� ���� �������� item�� �����ִ� ����.
bool plug_check(int item) {
	pair<int, int> next = *consent.begin(); 

	//�����ִ� ��� ó��
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

		// �̹� ���������� ���� ���
		if (!plug_check(item)) {


			// consent.erase(val)�� ���Ÿ� �ϴϱ� �ߺ��� ���� ��� ���ŵǴ� ������ �߻���. iterator idx�� �����ؾ���!

			pair<int, int> target = *consent.rbegin(); 
			
			multiset<pair<int, int>>::iterator it = consent.find(target);
			consent.erase(it);
			// target.first = �ش� �ܼ�Ʈ�� ���� �����ǰ�� ���� ���� �������� ���̴� ����(INF�� �� ������)
			// consent.second = �ش� �����ǰ ��ȣ

			// �����ִ� consent�� target�̸� ������ �����Ƿ� cnt ++
			if (target.first != INF) {
				cnt++;
			}

			if (!database[item].empty()) {
				target.first = database[item].top(); 
				target.second = item;
			}
			// �������� �Ⱦ��δٸ�?
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
	// �ڷᱸ�� �����
	for (int i = 0; i < 100; i++) {
		priority_queue<int, vector<int>, greater<int>> q;
		database.push_back(q);
	}
	// �ܼ�Ʈ �����
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
