#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int A[5][5];
int in[5][5];
int N, M;
int temp[5][5];

void mul(int B[5][5], int C[5][5]){
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			temp[i][j] = 0;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
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

void divide(int input[5][5], int r, int l){
	// base case
	if (l - r == 1) {
		mul(input, input);
		return;
	}
	// base case
	if (l == r) {
		return;
	}

	int left[5][5] = { 0 };
	int right[5][5] = { 0 };
	int mid = (l + r) / 2;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			left[i][j] = input[i][j];
			right[i][j] = input[i][j];
		}
	}
	divide(left, r, mid);
	divide(right, mid + 1, l);
	mul(left,right );
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			input[i][j] = left[i][j];
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
			in[i][j] = stoi(x[j]);
		}
		x.clear();
		
	}
}
void print() {
	// 출력 부분
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << in[i][j];
			if (j != N - 1) {
				cout << " ";
			}
			else {
				cout << "" << endl;
			}
		}
	}
}
int main() {
	start();
	divide(in, 0, M-1);
	print();

	return 0;
}