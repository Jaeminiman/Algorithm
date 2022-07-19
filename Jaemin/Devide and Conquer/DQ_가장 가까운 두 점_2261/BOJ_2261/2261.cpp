#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
vector<pair<int, int>> v;
int N;

int nearest(int start, int last) {
	//base case: 한 개만 남은 경우
	
	if (start < last) {
		pair<int,int> p1 = v[start], p2 = v[last];
		int x1 = p1.first, y1 = p1.second;
		int x2 = p2.first, y2 = p2.second;
		vector<pair<int, int>> tmp1;
		vector<pair<int, int>> tmp2;

		// 각 stage마다 평균 N번..!
		for (int i = start + 1; i <= last - 1; i++) {
			int x = v[i].first, y = v[i].second;
			int dist1 = pow(x1 - x, 2) + pow(y1 - y, 2);
			int dist2 = pow(x2 - x, 2) + pow(y2 - y, 2);
			if (dist1 > dist2) {
				tmp1.push_back(v[i]);
			}
			else {
				tmp2.push_back(v[i]);
			}
		}

		// 각 stage 마다 평균 N번 ...!
		int mid = start + tmp1.size();
		for (int i = start + 1; i <= mid; i++) {
			v[i] = tmp1[i];
		}
		for (int i = mid + 1; i <= last - 1; i++) {
			v[i] = tmp2[i];
		}

		int ret = min(nearest(start, mid), nearest(mid + 1, last));

		
		//case 3: 구분 경계를 기준으로 사이에 있는 경우
		int lo = mid, hi = mid + 1;
		while (lo >= start && hi <= last) {
			int lo_x = v[lo].first, lo_y = v[lo].second;
			int hi_x = v[hi].first, hi_y = v[hi].second;
			int dist = lo_x * lo_x + lo_y * lo_y;
			ret = min(ret, dist);
		}
		
		
	}
	
}
void start() {
	cin >> N;
	
	int x, y;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		v.push_back(pair<int, int>(x, y));
	}
}
int main() {
	start();

	return 0;
}