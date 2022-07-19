#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

using namespace std;
int N;
vector<int> hist;
vector<int> out;


int rectangular(int r, int l) {
	//base case : �Ѱ� ���� ���
	if (l - r == 0) {
		return hist[r];
	}

	int mid = (r + l) / 2;
	//case 1, 2 ���� ������ �ִ� ���. divide
	int ret = max(rectangular(r, mid), rectangular(mid + 1, l));
	
	//case 3. ��� ��ġ�� ��� (Ȯ��)
	int lo = mid, hi = mid + 1;
	int height = min(hist[lo], hist[hi]);
	ret = max(height * (hi - lo + 1), ret);

	// &&�� �ƴ� ������ �ȿ��� �ϳ��� ���� ������������ ��� ����ǵ��� �ϱ�����
	while (lo > r || hi < l) {
		// �������� Ȯ��
		if (lo > r && ( hi == l || (hist[lo - 1] > hist[hi + 1]))) {
			lo--;
			height = min(height,hist[lo]);
		}
		// ���������� Ȯ��
		else {
			hi++;
			height = min(height, hist[hi]);
		}

		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
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
		}
	}

	return start;
}
signed main() {
	while (start()) {
		int ret = rectangular(0, N-1);
		out.push_back(ret);
		hist.clear();
	}

	for (int i = 0; i < out.size(); i++) {
		cout << out[i] << endl;
	}
	return 0;
}