#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

using namespace std;
int N;
vector<int> hist;
vector<int> out;


int rectangular(int r, int l) {
	//base case : 한개 남은 경우
	if (l - r == 0) {
		return hist[r];
	}

	int mid = (r + l) / 2;
	//case 1, 2 왼쪽 오른쪽 있는 경우. divide
	int ret = max(rectangular(r, mid), rectangular(mid + 1, l));
	
	//case 3. 가운데 걸치는 경우 (확장)
	int lo = mid, hi = mid + 1;
	int height = min(hist[lo], hist[hi]);
	ret = max(height * (hi - lo + 1), ret);

	// &&이 아닌 이유는 안에서 하나가 끝에 도달했을때도 계속 진행되도록 하기위함
	while (lo > r || hi < l) {
		// 왼쪽으로 확장
		if (lo > r && ( hi == l || (hist[lo - 1] > hist[hi + 1]))) {
			lo--;
			height = min(height,hist[lo]);
		}
		// 오른쪽으로 확장
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