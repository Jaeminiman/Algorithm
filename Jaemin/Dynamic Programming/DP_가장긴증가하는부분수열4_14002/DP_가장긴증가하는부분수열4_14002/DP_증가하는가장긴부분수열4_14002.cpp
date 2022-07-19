#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int N;
int A[1001];
int DP[1001];
int choices[1001];
vector<int> seq; 

int LIS(int idx) {
	//base case : �� ����(����)
	if (idx == N) return 0;

	// idx = -1���� �����ϱ� ���� tool
	int& ret = DP[idx + 1];
	if (ret != -1) return ret;
	
	ret = 1;
	int bestNext = -1;
	for (int next = idx + 1; next < N; next++) {
		if ( idx == -1 || A[idx] < A[next]) {
			int cand = LIS(next) + 1;
			if (cand > ret) {
				ret = cand;
				bestNext = next;
			}
		}
	}
	// idx + 1�� �ִ� ������ ���������� idx = -1 ���� �����ϱ� ���� ����
	// ��, 1�� idx�� ���� ������ 2��° idx������ ���ð� ��Ȳ������ ����.
	choices[idx + 1] = bestNext;
	return ret;
}
 void reconstruct(int start) {
	if (start != -1) seq.push_back(A[start]);
	int next = choices[start + 1];
	// next == -1�̸�, �� �̻� �ڰ� �������� �ʴ� ����.
	if(next != -1) reconstruct(next);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	memset(DP, -1, sizeof(DP));
	memset(choices, -1, sizeof(choices));
	// idx == -1���� ���������Ƿ� ���� - 1 ����� ��
	int length = LIS(-1) - 1;
	cout << length << endl;

	reconstruct(-1);
	for (int i = 0; i < seq.size(); i++) {
		cout <<  seq[i] << " ";
	}
	return 0;
}