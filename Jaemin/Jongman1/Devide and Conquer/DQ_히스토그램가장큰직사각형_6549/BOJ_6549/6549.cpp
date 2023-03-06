#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

using namespace std;
int N;
vector<int> hist;
vector<int> width;
int max_area = 0;
vector<int> out;


void rectangular(int idx) {
	for (int i = idx; i < hist.size() - 1; i++) {
		// case 1
		if (hist[i + 1] > hist[i]) {
			int areaL = hist[i] * (width[i] + 1);
			int areaR = hist[i + 1] * width[i + 1];
			// ��ġ�°� �̵��� case
			if (areaL > areaR) {
				hist.erase(hist.begin() + i + 1);
				width.erase(width.begin() + i + 1);
				width[i]++;
				rectangular(i);
				break;
			}
		}
		// case 2
		else {
			int areaL = hist[i] * width[i];
			int areaR = hist[i + 1] * (width[i] + width[i+1]);
			// ��ġ�°� �̵��� case
			if (areaL < areaR) {
				hist.erase(hist.begin() + i);
				width.erase(width.begin() + i + 1);
				width[i]++;
				rectangular(i);
				break;
			}
		}
	}
}
bool start() {
	bool start = true;
	cin >> N;
	if (N == 0) {
		start = false;
	}
	else {
		for (int i = 0; i < N; i++) {
			int h;
			cin >> h;
			hist.push_back(h);
			width.push_back(1);
		}
	}
	
	return start;
}
void find_max() {
	for (int i = 0; i < hist.size(); i++) {
		max_area = max(max_area, hist[i] * width[i]);
	}
	out.push_back(max_area);
}
signed main() {
	while (start()) {
		rectangular(0);
		find_max();
	}
	
	for (int i = 0; i < out.size(); i++) {
		cout << out[i] << endl;
	}
	return 0;
}

// ���� 1: �ð��ʰ��� ����. �� ������ �𸣰���. ������ ��Ƚ���� N���ΰŰ����� 10^5�̸� �Ҹ����� �ʳ�?
// ���� 2: �ݷʸ� �ؼ����� ����. 5 1 2 3 4 5���� �� �ڵ�� �ش� �ݷʸ� ó���� �� ������. ���� �������� �ذ��ؾ� �Ѵ�. �� ����� ���� ������ �ƴ�.