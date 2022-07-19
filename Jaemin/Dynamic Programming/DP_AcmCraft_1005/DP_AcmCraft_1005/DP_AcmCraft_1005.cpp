#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int T, N, K, Goal;
int delay[1000];
int adj[1000][1000] = {0,};
int cache[1000];
vector<int> result;

int ACM(int target) {

	int& ret = cache[target];
	if (ret != -1) return ret;

	ret = delay[target];
	for (int v = 0; v < N; v++) {	
		if (adj[v][target] == 1) {
			ret = max(ret, ACM(v) + delay[target]);
		}
	}
	return ret;
}
void start() {
	cin >> N >> K;

	//초기화
	memset(cache, -1, sizeof(cache));
	memset(adj, 0, sizeof(adj));
	memset(delay, 0, sizeof(delay));

	for (int i = 0; i < N; i++) {
		cin >> delay[i];
	}
	for (int i = 0; i < K; i++) {
		int out, in;
		cin >> out >> in;
		adj[out - 1][in - 1] = 1;
	}
	
	cin >> Goal;
}
int main() {
	cin >> T;
	for (int epoch = 0; epoch < T; epoch++) {
		start();
		result.push_back(ACM(Goal - 1));
		// idx다 1씩 줄였으므로 목표지점도 idx 1 줄임.
	}

	for (int i = 0; i < T; i++) {
		cout << result[i] << endl;
	}
	return 0;
}