#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

string A, B;
int cache[1000][1000];

int LCS(int A_idx, int B_idx) {
	//base case : idx�� ������ ��� ���(����)
	if (A_idx == A.size() || B_idx == B.size()) return 0;
	
	int& ret = cache[A_idx][B_idx]; // cache[A_idx][B_idx]�� �ƴ� ������ ������idx_B�� �����ϸ� nextB ���� ������ ���̱� ���� => �׷��� nextB�� �����ϴ°� �� ��ġ�� ��찡 ����
	if (ret != -1) {
		return ret;
	}

	int nextB = B_idx;
	while ((nextB <= B.size() - 1) && (A[A_idx] != B[nextB])) {
		nextB++;
	}
	// ������ �ߴµ�, nextB�� ���� ���ϸ� �׳� �ȳִ� �������� �� ����� �ߴµ�, �������͹����� ���̻� ������ �ȵǾ���.
	if (nextB == B.size()) {
		ret = LCS(A_idx + 1, B_idx);
	}
	else {
		ret = max(LCS(A_idx + 1, B_idx), LCS(A_idx + 1, nextB + 1) + 1);
	}

	return ret;
}

int main() {
	std::getline(cin, A);
	std::getline(cin, B);
	memset(cache, -1, sizeof(cache));
	int result = LCS(0, 0);
	cout << result << endl;
	return 0;
}