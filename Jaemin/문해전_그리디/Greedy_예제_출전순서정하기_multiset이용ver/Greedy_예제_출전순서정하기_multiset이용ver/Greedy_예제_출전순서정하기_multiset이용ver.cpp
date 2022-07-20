#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
int C, N;
vector<int> russian;
vector<int> korean;
int win;

int order() {
	// 이진 검색 트리인 multiset으로 korean rating을 관리함으로써
	// 검색과 삭제를 O(nlgn)시간에 해결할 수 있도록 한다.
	multiset<int> ratings(korean.begin(), korean.end());

	for (int rus = 0; rus < N; rus++) {
		// multiset활용법 : ratings의 가장 뒤 idx의 "값"을 리턴함
		// 항상 패배하는 경우
		if (*ratings.rbegin() < russian[rus]) {
			ratings.erase(ratings.begin());
		}
		else {
			// russian[rus]보다 큰 것중 가장 작은 것
			ratings.erase(ratings.lower_bound(russian[rus]));
			win++;
		}
	}
	return win;
}

int main() {
	cin >> C;
	for (int epoch = 0; epoch < C; epoch++) {
		// epoch 전처리
		win = 0;
		russian.clear();
		korean.clear();

		cin >> N;
		for (int i = 0; i < N; i++) {
			int ele;
			cin >> ele;
			russian.push_back(ele);
		}
		for (int i = 0; i < N; i++) {
			int ele;
			cin >> ele;
			korean.push_back(ele);
		}
		sort(russian.begin(), russian.end());
		sort(korean.begin(), korean.end());



		int result = order();

		cout << result << endl;

	}
	return 0;
}