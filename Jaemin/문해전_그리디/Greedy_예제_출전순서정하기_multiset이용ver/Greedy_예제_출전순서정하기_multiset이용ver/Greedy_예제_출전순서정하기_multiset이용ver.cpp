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
	// ���� �˻� Ʈ���� multiset���� korean rating�� ���������ν�
	// �˻��� ������ O(nlgn)�ð��� �ذ��� �� �ֵ��� �Ѵ�.
	multiset<int> ratings(korean.begin(), korean.end());

	for (int rus = 0; rus < N; rus++) {
		// multisetȰ��� : ratings�� ���� �� idx�� "��"�� ������
		// �׻� �й��ϴ� ���
		if (*ratings.rbegin() < russian[rus]) {
			ratings.erase(ratings.begin());
		}
		else {
			// russian[rus]���� ū ���� ���� ���� ��
			ratings.erase(ratings.lower_bound(russian[rus]));
			win++;
		}
	}
	return win;
}

int main() {
	cin >> C;
	for (int epoch = 0; epoch < C; epoch++) {
		// epoch ��ó��
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