#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int N, K;
int value[100] = { 0, }; // 400B
int cache[10001] = {0,}; // 4MB이다.. => 40KB 활용 가능

void coin() {

	
	// 원래라면 cache[i][j] : 0 ~ i까지의 코인을 이용해서 j를 만드는 경우의수라고 정의를 한다.
	// cache[j] = cache[0][j] + cache[1][j] + ... + cache[N- 1][j]이므로, 이를 for문으로 바깥으로 꺼내
	// 1차원 배열로 관리하고, 누적합을 하도록 한다. 메모리 관리를 위해서!
	cache[0] = 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= K; j++) {
			if (j >= value[i]) {
				cache[j] += cache[j - value[i]];
			}
		}	
	}
}

void start() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		cin >> value[i];
	}
}
int main() {
	start();
	coin();
	cout << cache[K] << endl;

	return 0;
}