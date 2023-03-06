#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int N, K;
int value[100] = { 0, }; // 400B
int cache[10001] = {0,}; // 4MB�̴�.. => 40KB Ȱ�� ����

void coin() {

	
	// ������� cache[i][j] : 0 ~ i������ ������ �̿��ؼ� j�� ����� ����Ǽ���� ���Ǹ� �Ѵ�.
	// cache[j] = cache[0][j] + cache[1][j] + ... + cache[N- 1][j]�̹Ƿ�, �̸� for������ �ٱ����� ����
	// 1���� �迭�� �����ϰ�, �������� �ϵ��� �Ѵ�. �޸� ������ ���ؼ�!
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