#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

string A, B;
int cache[1000][1000];

int LCS(int A_idx, int B_idx) {
	//base case : idx가 범위를 벗어난 경우(종료)
	if (A_idx == A.size() || B_idx == B.size()) return 0;
	
	int& ret = cache[A_idx][B_idx]; // cache[A_idx][B_idx]가 아닌 이유는 어차피idx_B로 접근하면 nextB 값과 동일할 것이기 때문 => 그러면 nextB로 접근하는게 더 겹치는 경우가 많음
	if (ret != -1) {
		return ret;
	}

	int nextB = B_idx;
	while ((nextB <= B.size() - 1) && (A[A_idx] != B[nextB])) {
		nextB++;
	}
	// 착각을 했는데, nextB가 존재 안하면 그냥 안넣는 선택으로 더 들어갔어야 했는데, 빠져나와버려서 더이상 진행이 안되었다.
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