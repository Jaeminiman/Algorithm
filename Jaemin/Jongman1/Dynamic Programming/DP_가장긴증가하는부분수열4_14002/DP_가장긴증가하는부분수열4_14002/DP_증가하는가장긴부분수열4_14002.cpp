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
	//base case : 끝 도달(종료)
	if (idx == N) return 0;

	// idx = -1부터 시작하기 위한 tool
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
	// idx + 1에 넣는 이유는 마찬가지로 idx = -1 부터 시작하기 위한 선택
	// 즉, 1번 idx에 대한 선택은 2번째 idx에서의 선택과 상황적으로 동일.
	choices[idx + 1] = bestNext;
	return ret;
}
 void reconstruct(int start) {
	if (start != -1) seq.push_back(A[start]);
	int next = choices[start + 1];
	// next == -1이면, 더 이상 뒤가 존재하지 않는 것임.
	if(next != -1) reconstruct(next);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	memset(DP, -1, sizeof(DP));
	memset(choices, -1, sizeof(choices));
	// idx == -1부터 시작했으므로 길이 - 1 해줘야 함
	int length = LIS(-1) - 1;
	cout << length << endl;

	reconstruct(-1);
	for (int i = 0; i < seq.size(); i++) {
		cout <<  seq[i] << " ";
	}
	return 0;
}