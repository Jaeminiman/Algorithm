#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
int N;
int v[500001];
int temp[500001];
long long result = 0;

void merge(int r,int l) {
	int mid = (r + l) / 2;
	int lo = r, hi = mid + 1;
	int i = r;
	int cnt = 0;

	while (lo <= mid && hi <= l) {
		if (v[lo] <= v[hi]) {
			temp[i++] = v[lo++];
			result += (long long)cnt;
		}
		//swap 발생
		else {
			temp[i++] = v[hi++];
			cnt++;
		}
	}
	// 오른쪽이 남은 경우
	if (lo > mid) {
		int s = hi;
		while (s <= l) {
			temp[i++] = v[s++];
			cnt++;
		}
	}
	// 왼쪽이 남은 경우
	else {
		int s = lo;
		while (s <= mid) {
			temp[i++] = v[s++];
			result += (long long)cnt;
		}
	}

	for (int j = r; j <= l; j++) {
		v[j] = temp[j];
	}
}

void merge_sort(int r, int l) {
	//base case: 1개만 남은 경우
	if (l - r == 0) {
		return;
	}

	int mid = (r + l) / 2;
	merge_sort(r, mid);
	merge_sort(mid + 1, l);
	merge(r,l);
}

void start() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> v[i];
	}
}
int main(void) {
	start();
	merge_sort(0,N-1);

	cout << result << endl;

	return 0;
}