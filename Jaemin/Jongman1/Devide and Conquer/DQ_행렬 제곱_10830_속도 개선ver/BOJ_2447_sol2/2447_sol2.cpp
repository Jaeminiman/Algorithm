#include <iostream>
#include <vector>
#include <sstream>
#include <string>

// 모든 int를 long long으로 처리하여 숫자형 범위 넘어나는 경우를 제외하는 방법
// #define int long long 하고 , signed main(){}으로 메인함수를 짜면 해결 가능
#define int long long
using namespace std;

long long A[5][5];
long long out[5][5];
int N, M;
long long temp[5][5];

void mul(long long B[5][5], long long C[5][5]) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp[i][j] = 0; // 초기화

			for (int k = 0; k < N; k++) {
				temp[i][j] += B[i][k] * C[k][j];
			}
			temp[i][j] %= 1000;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			B[i][j] = temp[i][j];
		}
	}
}


void start() {
	cin >> N >> M;
	string line;
	string stringBuffer;
	vector<string> x;
	x.clear();

	getline(cin, line);
	for (int i = 0; i < N; i++) {
		getline(cin, line);
		istringstream ss(line);
		while (getline(ss, stringBuffer, ' ')) {
			x.push_back(stringBuffer);
		}
		for (int j = 0; j < x.size(); j++) {
			A[i][j] = stoi(x[j]);

			// 주의! 정답은 단위 행렬이어야 첨 곱한 값과 같다.
			out[i][i] = 1;
		}
		x.clear();

	}
}

void print() {
	// 출력 부분
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << out[i][j];
			cout << " ";
			if(j == N - 1){
				cout << endl;
			}
		}
	}
}

signed main() {
	start();

	// divide. 해소 방법? 같은 계산을 더 하지 않고 그냥 한번만 처리해버린다.
	while (M > 0) {
		if (M % 2 == 1) {
			mul(out, A);
		}

		mul(A, A);
		M /= 2;
	}
	print();
	return 0;
}