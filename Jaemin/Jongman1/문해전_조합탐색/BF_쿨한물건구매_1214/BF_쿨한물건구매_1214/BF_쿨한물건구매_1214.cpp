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
	// ū�Ű� P
	if (P < Q) swap(P, Q);
	long long LCM = lcm(P, Q);
	int lcm_cnt = LCM / P;
	// ���ʿ� ���� �� ���� ���. (������ �� ŭ)
	if (Q > D) {
		num = Q;
	}
	else {
		// O(10^9) ��, D /= P ������ ���� Ƚ�� -> �׳� ��� �ð����� �ٲ����
		if (D % P != 0) {
			num += ((D / P) + 1) * P;
			p_cnt += (D / P) + 1;
		}
		else {
			num += D;
		}
	}
	
	// �ٱ� -> O(D/=P)
	// ���� -> O(P/=Q)
	long long best = num;
	while ( p_cnt != 0 && lcm_cnt != 0) {
		// ���� �ð� ���� ���̱�
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