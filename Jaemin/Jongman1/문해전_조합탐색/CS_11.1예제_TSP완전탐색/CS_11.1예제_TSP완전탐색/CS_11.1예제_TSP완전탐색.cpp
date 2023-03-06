// 코드 6.7
#include <vector>
#include <algorithm>
using namespace std;
int n; // 도시 수
double dist[100][100];
const int INF = 123456789;
vector<int> path; vector<bool> visited;

double shortestPath(double currentLength) {
	// 기저사례 : 모든 도시 방문하고 시작도시로 돌아가며 종료
	if (path.size() == n) {
		return currentLength + dist[path[0]][path.back()];
	}

	double ret = INF;
	for (int next = 0; next < n; next++) {
		if (visited[next]) continue;
		int here = path.back();
		path.push_back(next);
		visited[next] = true;
		double cand = shortestPath(currentLength + dist[here][next]);

		ret = min(ret, cand);
		visited[next] = false;
		path.pop_back();
	}
	return ret;
}

//코드 11.1

const double INF = 1e200;
const int MAX = 30;
int n; //도시의 수
double dist[MAX][MAX];
// 지금까지 찾은 최적해
double best;

void search(double currentLength) {

	// 간단한 가지치기 적용 : 지금까지 찾은 가장 좋은 답(best) 이상일 경우 중단
	if (best <= currentLength) return;

	int here = path.back();
	//기저사례 : 모든 도시 방문했을 때 0번 도시로 돌아가고 종료.
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	for (int next = 0; next < n; ++next) {
		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		// 나머지 경로를 재귀호출로 완성한다.
		search(currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

// 코드 11.2 단순한 휴리스틱을 이용한 가지치기

const double INF = 1e200;
const int MAX = 30;
int n; //도시의 수
double dist[MAX][MAX];
// 지금까지 찾은 최적해
double best;
// 각 도시에 인접한 간선 중 가장 짧은 것 미리 찾아둠
double minEdge[MAX];
double simpleHeuristic() {
	double ret = minEdge[0]; // 마지막에 시작점으로 돌아갈 때 사용할 간선
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			ret += minEdge[i];
		}
	}
	return ret;
}

void search(double currentLength) {

	// 간단한 가지치기 적용 : 지금까지 찾은 가장 좋은 답(best) 이상일 경우 중단
	if (best <= currentLength + simpleHeuristic()) return;

	// ... 나머지는 코드11.1과 동일
}
double solve() {

	// simpleHeuristic을 위한 minEdge 초기화 작업
	for (int i = 0; i < n; i++) {
		minEdge[i] = INF;
		for (int j = 0; j < n; j++) {
			if (i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
		}
	}
	// ... 생략
}

// 코드 11.3 가까운 도시부터 방문하는 최적화 (최적의 답을 빨랑 찾도록 하여 수행시간 감소)

// 각 도시마다 다른 도시들을 가까운 순서대로 정렬해 둔다.
vector<int> nearest[MAX];
void search(double currentLength) {
	// 다음 방문할 도시들을 전부 시도해 본다
	int here = path.back();
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];
		// ... 생략
	}
}
double solve() {
	//nearest 초기화
	// pair로 묶어서 dist순서대로 정렬하고 index만을 저장하는 nearest를 받는 기법으로 가장 dist 작은 순으로 index저장
	for (int i = 0; i < n; i++) {
		vector<pair<double, int>> order;
		for (int j = 0; j < n; j++) {
			if (i != j) {
				order.push_back(make_pair(dist[i][j], j));
			}
		}
		sort(order.begin(), order.end());
		nearest[i].clear();
		for (int j = 0; j < n - 1; ++j) {
			nearest[i].push_back(order[j].second);
		}
	}
	// ..생략..
}

// 코드 11.4. 지나온 경로를 이용하는 두 가지 가지치기 전략의 구현

// path의 마지막 4개의 도시 중 가운데 있는 두 도시의 순서를 바꾸었을 때
// 경로가 더 짧아지는지 여부를 반환한다.
bool pathSwapPruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}
// 이것만 적용하더라도 대형 입력(n=20)이 시간 범위 내로 들어온다.

// 시작 도시와 현재 도시를 제외한 path의 부분 경로를
// 뒤집어 보고 더 짧아지는지 확인한다.
// 이 알고리즘은 자기 자신을 교차하는 경로를 만들지 않도록 해준다. 2차원 평면의 TSP 경로에서 자기 자신을 교차하면 항상 최적의 답이 아니므로, 이 꼬인 상태를 풀어주는 것이다.
bool pathReversePruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	for (int i = 0; i + 3 < path.size(); ++i) {
		int p = path[i];
		int a = path[i + 1];
		// [..,p,a...,b,q]를 [..,p,b,...,a,q]로 바꾸어 본다
		if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q]) return true;
	}
	return false;
}

// 코드 11.5. MST(최소 스패닝 트리) 휴리스틱 구현
// 1. 한 간선은 최대 한 번만 선택할 수 있다.
// 2. 선택하지 않은 간선을 모두 지웠을 때 그래프가 둘 이상으로 쪼개지면 안 된다.

// 코드 11.6. 부분적으로 메모이제이션을 사용하는 최적화의 구현

// 남은 도시 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다.
const int CACHED_DEPTH = 5;

#include <map>
map<int, double> cache[MAX][CACHED_DEPTH + 1];

double dp(int here, int visited) {
	// 기저 사례: 더 방문할 도시가 없으면 시작점으로 돌아간다. (비트연산자로 32bit까지 있는 int형에서 1을 32번밀면 최초로 -1에 도달한다.
	if (visited == (1 << n) - 1) return dist[here][0];
	// visited를 불린 배열이 아닌 정수 값으로 설정할 경우, dp()를 호출할 때마다 변환하는 귀찮은 일을 하지 않아도 된다.(9.11절 참고)

	// __builtin_popcount : g++ 내장함수, 주어진 숫자의 이진수 표현에서 1의 개수를 센다.
	// 어떤 도시를 방문했으면 해당 비트를 1, 아니면 0으로 하기 떄문에 __builtin_popcount(visited)는 지금까지 방문한 도시 수가 된다.
	int remaining = n - __builtin_popcount(visited);
	// remaining을 기준으로 map을 나누어서 map에 접근하는 시간을 조금 줄일 수 있다.
	double& ret = cache[here][remaining][visited];
	if (ret > 0) return ret;
	ret = INF;
	// 다음 도시를 하나씩 시도한다.
	for (int next = 0; next < n; ++next) {
		if (visited & (1 << next)) continue; // 1<<next는 다음에 방문할 도시의 bit값이고, 이것과 현재 가진 visited bit이 일치하면 이미 방문했다는 것이 된다.
		ret = min(ret, dp(next, visited + (1 << next)) + dist[here][next]);
	}
	return ret;
}

void search(int visited, double currentLength) {
	// ..생략..

	// 기저사례 : 남은 도시 수가 CACHED_DEPTH이하면 동적 계획법으로 바꾼다.
	if (path.size() + CACHED_DEPTH >= n) {
		best = min(best, currentLength + dp(path.back(), visited));
		return;
	}
	//.. 생략
}

double solve() {
	//..생략..
	// cache 초기화
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < CACHED_DEPTH; j++) {
			cache[i][j].clear();
		}
	}
}