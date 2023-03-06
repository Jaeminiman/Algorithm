#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int C, N;
vector<int> russian;
vector<int> korean;


int main() {
	cin >> C;
	for (int epoch = 0; epoch < C; epoch++) {
		// epoch 전처리
		int win = 0;
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



		for (int rus = 0; rus < N; rus++) {
			// win할 수 없는 경우
			if (korean[korean.size() - 1] < russian[rus]) {
				korean.erase(korean.begin());
			}
			else {
				for (int kor = 0; kor < korean.size(); kor++) {
					if (korean[kor] >= russian[rus]) {
						korean.erase(korean.begin() + kor);
						win++;
						break;
					}
				}
			}
		}

		cout << win << endl;

	}
	return 0;
}