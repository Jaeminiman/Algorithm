#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int C;
int n, m;
const int MAX = 123456789;
struct Point {
	double y, x;
};
double MINX1, MINX2, MAXX1, MAXX2;
vector<pair<Point, Point>> upper, lower;
vector<Point> hull1, hull2;

// 어찌됐건 오목함수 ^ 는 점을 잇는 직선 중 min만을 택한 모양과 같다는 인사이트
double lower_evaluate(double x) {
	double ret = -MAX;
	for (int i = 0; i < lower.size(); i++) {
		Point p1 = lower[i].first;
		Point p2 = lower[i].second;
		double dx = p1.x - p2.x, dy = p1.y - p2.y;
		double y = p1.y + (dy * (x - p1.x)) / dx;
		ret = max(ret, y);
	}
	return ret;
}
// 어찌됐건 볼록함수V는 점을 잇는 직선 중 max만을 택한 모양과 같다는 인사이트
double upper_evaluate(double x) {
	double ret = MAX;
	for (int i = 0; i < upper.size(); i++) {
		Point p1 = upper[i].first;
		Point p2 = upper[i].second;
		double dx = p1.x - p2.x, dy = p1.y - p2.y;
		double y = p1.y + (dy * (x - p1.x)) / dx;
		ret = min(ret, y);
	}
	return ret;
}
double vertical(double x) {
	double up = upper_evaluate(x), down = lower_evaluate(x);
	return up - down;
}
void decompose(const vector<Point>& hull) {
	int N = hull.size();
	for (int i = 0; i < N; i++) {
		// 윗 껍질
		// 순환하는 것을 표현하는 Tool
		if (hull[i].x - hull[(i + 1) % N].x > 0)
			upper.push_back(make_pair(hull[i], hull[(i + 1) % N]));
		// 아랫 껍질
		else if (hull[i].x - hull[(i + 1) % N].x < 0) {
			lower.push_back(make_pair(hull[i], hull[(i + 1) % N]));
		}
	}
}
double solve() {
	double lo = max(MINX1, MINX2);
	double hi = min(MAXX1, MAXX2);
	// 기저 사례 : x 축에서 겹치지 않는 경우
	if (lo > hi) return 0.0;

	for (int i = 0; i < 100; i++) {
		double lolohi = (2 * lo + hi) / 3;
		double lohihi = (lo + 2 * hi) / 3;
		if (vertical(lolohi) < vertical(lohihi))
			lo = lolohi;
		else
			hi = lohihi;
	}
	return max(0.0,vertical(hi));
}
int main() {
	cin >> C;
	for (int epoch = 0; epoch < C; epoch++) {
		cin >> n >> m;
		MINX1 = MAX, MINX2 = MAX, MAXX1 = -MAX, MAXX2 = -MAX;
		upper.clear(); lower.clear();
		hull1.clear(); hull2.clear();

		for (int i = 0; i < n; i++) {
			double y, x;
			cin >> x >> y;
			hull1.push_back({ y,x });
			MINX1 = min(MINX1, x);
			MAXX1 = max(MAXX1, x);
		}
		for (int i = 0; i < m; i++) {
			double y, x;
			cin >> x >> y;
			hull2.push_back({ y,x });
			MINX2 = min(MINX2, x);
			MAXX2 = max(MAXX2, x);
		}
		decompose(hull1);
		decompose(hull2);
		double ret = solve();
		cout << fixed;
		cout.precision(10);
		cout << ret << '\n';
	}
	return 0;
}