#include <iostream>
#include <vector>
#include <algorithm>
#include<cstring> // memset 초기화를 위한 헤더파일

using namespace std;
int N, K;
const int NEGINF = -123456789;
vector<pair<int, int>> database;
int cache[100001][100]; // Weight 범위가 0부터 K까지이므로 K+1 공간 할당이 필요함.

int bag(int weight, int idx) {
	// 이 base case 설계 부분이 약간 헷깔리는데, ret 형식(점화식)을 보고 적절히 설계를 해야함
	// 점화식에서 보면 idx위치의 item을 넣고 다음거를 볼지 안넣고 다음거를 볼지 결정한다.
	// 만약 넣는다는 선택을 하는 경우에는 넣은 후 상태의 bag()함수가 호출되는데, 이때는
	// 무게가 초과되는 경우 절대 케이스 고려를 하지 못하도록 설정해야 한다. 
	// 그를 위해 NEGINF를 반환하도록 하고, 만약 보고있는 idx가 배열 범위를 다 봤다면
	// 그를 input으로 하는 bag()호출 값은 선택안하고 종료하는 것이 맞기 때문에 0을 반환한다.
	// 그렇게 되면 만약 이전에서 선택을 하고 들어간 경우에는 이전 idx위치의 value만을
	// 넣은 채로 종료하게 된다.
	
	// base case : 무게를 초과한 경우(실패)
	if (weight > K) return NEGINF;
	// base case : idx 범위 다 본 경우(종료)
	if (idx == N) return 0;

	int& ret = cache[weight][idx];
	if (ret != -1) return ret;
	
	ret = max(bag(weight + database[idx].first, idx + 1) + database[idx].second,
		bag(weight, idx + 1));
	
	return ret;
}
void start() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int w, v;
		cin >> w >> v;
		database.push_back(make_pair(w, v));
	}
	// -1로 초기화 하기위한 코드
	memset(cache, -1, sizeof(cache));
}
int main() {
	start();
	int ret = bag(0, 0);
	cout << ret << endl;
	return 0;
}