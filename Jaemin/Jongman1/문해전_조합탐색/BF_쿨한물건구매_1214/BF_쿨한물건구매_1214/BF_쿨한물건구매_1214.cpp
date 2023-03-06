#include <iostream>
#include <algorithm>
using namespace std;
long long best;
int D, P, Q;
long long gcd(int a, int b) {
	int c;
	while (b != 0) {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}
long long lcm(long long a, long long b) {
	return a * b / gcd(a, b);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> D >> P >> Q;
	long long num = 0;
	int p_cnt = 0;
	// 큰거가 P
	if (P < Q) swap(P, Q);
	long long LCM = lcm(P, Q);
	int lcm_cnt = LCM / P;
	// 애초에 만들 수 없는 경우. (작은게 더 큼)
	if (Q > D) {
		num = Q;
	}
	else {
		// O(10^9) 즉, D /= P 정도의 연산 횟수 -> 그냥 상수 시간으로 바꿔버림
		if (D % P != 0) {
			num += ((D / P) + 1) * P;
			p_cnt += (D / P) + 1;
		}
		else {
			num += D;
		}
	}
	
	// 바깥 -> O(D/=P)
	// 내부 -> O(P/=Q)
	long long best = num;
	while ( p_cnt != 0 && lcm_cnt != 0) {
		// 연산 시간 낭비 줄이기
		if (best == D) {
			break;
		}
		num -= P;
		lcm_cnt--;
		p_cnt--;
		num += ((D - num) / Q)* Q;
		num += Q;
		if (num == D + Q) {
			best = D;
		}
		else {
			best = min(best, num);
		}
	}
	cout << best << '\n';
	return 0;
}