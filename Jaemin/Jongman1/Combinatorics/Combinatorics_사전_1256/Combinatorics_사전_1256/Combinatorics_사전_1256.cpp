#include <iostream>
#include <vector>
#include <string>

using namespace std;
int A, B;
int K;
long long DP[101][101];
vector<char> output;
long long standard = 0;

void search() {

	int numA = A;
	for (int b = B; b > 0; b--) {
		for (int a = 0; a <= numA; a++) {
			if (standard + DP[a][b] == K) {
				standard += DP[a][b];

				// output 만들어 주는 방식 (vector로 관리)
				for (int i = 0; i < numA - a; i++) {
					output.push_back('a');
				}
				for (int i = 0; i < b; i++) {
					output.push_back('z');
				}
				for (int i = 0; i < a; i++) {
					output.push_back('a');
				}
				return;
			}

			// 임계지점에 도달했을 때
			if (standard + DP[a][b] > K && a > 0) {
				standard += DP[a - 1][b];
				// output 만들어 주는 방식 (vector로 관리)
				for (int i = 0; i < numA - a; i++) {
					output.push_back('a');
				}
				output.push_back('z');
				numA = a;
				break;
			}
		}
	}
	return;
	
}
void calc() {
	for (int i = 0; i <= B; i++) {
		DP[0][i] = 1;
	}
	for (int i = 0; i <= A; i++) {
		DP[i][0] = 1;
	}
	for (int i = 1; i <= A; i++) {
		for (int j = 1; j <= B; j++) {
			DP[i][j] = DP[i - 1][j] + DP[i][j - 1];
			if (DP[i][j] > 1000000000) DP[i][j] = 1000000001;
		}
	}
}
int main() {
	cin >> A >> B;
	cin >> K;
	calc();
	search();

	// K가 존재 하는 경우
	if (DP[A][B] >= K) {
		for (int i = 0; i < output.size(); i++) {
			cout << output[i];
		}
		cout << '\n';
	}
	else {
		cout << -1 << '\n';
	}
	return 0;
}