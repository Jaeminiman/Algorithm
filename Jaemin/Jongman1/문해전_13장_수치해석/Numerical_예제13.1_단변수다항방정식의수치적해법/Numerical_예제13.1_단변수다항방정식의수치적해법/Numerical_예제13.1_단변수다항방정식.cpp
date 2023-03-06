#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// 코드 13.3 단변수 다항 방정식의 해를 이분법으로 찾기
int C;
int n;
const double L = 10;

vector<double> naiveSolve(const vector<double>& poly) {
	// x1 = (-b + root(b - 4 * a * c)) / (2a)
	double a = poly[0], b = poly[1], c = poly[2];
	vector<double> ret;
	if (pow(b, 2) - 4 * a * c > 0) {
		double x1 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		double x2 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		ret.push_back(x1); ret.push_back(x2);
	}
	else if (pow(b, 2) - 4 * a * c == 0) {
		ret.push_back(-b / (2 * a));
	}
	return ret;
}
double evaluate(const vector<double>& poly, double x0) {
	double ret = 0;
	int n = poly.size() - 1;
	for (int i = 0; i < n + 1; i++) {
		ret += poly[i] * pow(x0, n - i);
	}
	return ret;
}
vector<double> differentiate(const vector<double>& poly) {
	vector<double> ret;
	int n = poly.size() - 1;
	for (int i = 0; i< n; i++) {
		ret.push_back(poly[i] * (n - i));
	}
	return ret;
}
vector<double> solve(const vector<double>& poly) {
	int n = poly.size() - 1; // 몇 차식인지
	// 기저 사례 : n <= 2 일 때는 근의 공식으로 구할 수 있다.
	if (n <= 2) return naiveSolve(poly);

	vector<double> derivative = differentiate(poly);
	vector<double> sols = solve(derivative);
	sols.insert(sols.begin(), -L - 1);
	sols.insert(sols.end(), L + 1);

	vector<double> ret;
	for (int i = 0; i + 1 < sols.size(); i++) {
		double x1 = sols[i], x2 = sols[i + 1];
		double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
		// 부호가 같으면 근이 존재 x
		if (y1 * y2 > 0) continue;
		// 불변 조건 : f(x1) < = 0 < f(x2)
		if (y1 > y2) {
			swap(x1, x2); swap(y1, y2);
		}


		for (int j = 0; j < 100; j++) {
			double xm = (x1 + x2) / 2, ym = evaluate(poly, xm);
			if (ym * y1 > 0) {
				x1 = xm;
				y1 = ym;
			}
			else {
				x2 = xm;
				y2 = ym;
			}
		}
		ret.push_back((x1 + x2) / 2);
	}
	return ret;

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> C;
	for (int epoch = 0; epoch < C; epoch++) {
		cin >> n;
		vector<double> polynom;
		for (int i = 0; i < n + 1; i++) {
			double a;
			cin >> a;
			polynom.push_back(a);
		} 
		vector<double> sol = solve(polynom);
	for (int j = 0; j < sol.size(); j++) {
		double ret = sol[j];
		cout << fixed;
		cout.precision(12);
		cout <<  ret;
		cout << " ";
	}
	cout << '\n';

	}
	return 0;
}