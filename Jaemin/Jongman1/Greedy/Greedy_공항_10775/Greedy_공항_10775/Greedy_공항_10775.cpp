#include <iostream>
#include <vector>
#include <set>
using namespace std;
int G, P;
vector<int> plane;
// gi보다 작거나 같은 container 빠르게 찾기 위해 multiset으로 관리
multiset<int, greater<int>> container;

int docking() {
	int cnt = 0;
	while (!plane.empty()) {
		int Gi = plane[0]; plane.erase(plane.begin());
		multiset<int>::iterator it = container.lower_bound(Gi);
		if (it != container.end()) {
			container.erase(it);
			cnt++;
		}
		else {
			break;
		}	
	}
	
	return cnt;
}
int main() {
	cin >> G >> P;
	for (int i = 0; i < P; i++) {
		int x;
		cin >> x;
		plane.push_back(x);
	}
	for (int i = 1; i <= G; i++) {
		container.insert(i);
	}
	int ret = docking();
	cout << ret << endl;
	return 0;
}