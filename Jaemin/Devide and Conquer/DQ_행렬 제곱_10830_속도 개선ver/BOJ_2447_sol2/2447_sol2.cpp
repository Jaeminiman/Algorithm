#include <iostream>
#include <vector>
#include <sstream>
#include <string>

// ��� int�� long long���� ó���Ͽ� ������ ���� �Ѿ�� ��츦 �����ϴ� ���
// #define int long long �ϰ� , signed main(){}���� �����Լ��� ¥�� �ذ� ����
#define int long long
using namespace std;

long long A[5][5];
long long out[5][5];
int N, M;
long long temp[5][5];

void mul(long long B[5][5], long long C[5][5]) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp[i][j] = 0; // �ʱ�ȭ

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

			// ����! ������ ���� ����̾�� ÷ ���� ���� ����.
			out[i][i] = 1;
		}
		x.clear();

	}
}

void print() {
	// ��� �κ�
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

	// divide. �ؼ� ���? ���� ����� �� ���� �ʰ� �׳� �ѹ��� ó���ع�����.
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