#include <iostream>

using namespace std;
int T;
double N, P;
int M;

// monthly_payment로 M개월 내에 갚을 수 있다.
bool decision(long double monthly_payment) {
	long double remains = N;
	for (int month = 0; month < M; month++) {
		remains *= (1 + P / 12 * 0.01);
		remains -= monthly_payment;
	}
	return remains <= 0;
}
long double payment() {
	long double lo = 0, hi = N*(1 + (P/12)*100);
	for (int i = 0; i < 100; i++) {
		long double mid = (lo + hi) / 2;
		if (decision(mid)) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}
	return hi;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> T;
	for (int epoch = 0; epoch < T; epoch++) {
		cin >> N >> M >> P;
		cout << fixed;
		cout.precision(10);
		cout << payment() << '\n';

	}
	return 0;
}