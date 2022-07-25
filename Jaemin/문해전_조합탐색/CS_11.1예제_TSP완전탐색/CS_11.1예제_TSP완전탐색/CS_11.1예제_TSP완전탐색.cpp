// �ڵ� 6.7
#include <vector>
#include <algorithm>
using namespace std;
int n; // ���� ��
double dist[100][100];
const int INF = 123456789;
vector<int> path; vector<bool> visited;

double shortestPath(double currentLength) {
	// ������� : ��� ���� �湮�ϰ� ���۵��÷� ���ư��� ����
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

//�ڵ� 11.1

const double INF = 1e200;
const int MAX = 30;
int n; //������ ��
double dist[MAX][MAX];
// ���ݱ��� ã�� ������
double best;

void search(double currentLength) {

	// ������ ����ġ�� ���� : ���ݱ��� ã�� ���� ���� ��(best) �̻��� ��� �ߴ�
	if (best <= currentLength) return;

	int here = path.back();
	//������� : ��� ���� �湮���� �� 0�� ���÷� ���ư��� ����.
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	for (int next = 0; next < n; ++next) {
		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		// ������ ��θ� ���ȣ��� �ϼ��Ѵ�.
		search(currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

// �ڵ� 11.2 �ܼ��� �޸���ƽ�� �̿��� ����ġ��

const double INF = 1e200;
const int MAX = 30;
int n; //������ ��
double dist[MAX][MAX];
// ���ݱ��� ã�� ������
double best;
// �� ���ÿ� ������ ���� �� ���� ª�� �� �̸� ã�Ƶ�
double minEdge[MAX];
double simpleHeuristic() {
	double ret = minEdge[0]; // �������� ���������� ���ư� �� ����� ����
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			ret += minEdge[i];
		}
	}
	return ret;
}

void search(double currentLength) {

	// ������ ����ġ�� ���� : ���ݱ��� ã�� ���� ���� ��(best) �̻��� ��� �ߴ�
	if (best <= currentLength + simpleHeuristic()) return;

	// ... �������� �ڵ�11.1�� ����
}
double solve() {

	// simpleHeuristic�� ���� minEdge �ʱ�ȭ �۾�
	for (int i = 0; i < n; i++) {
		minEdge[i] = INF;
		for (int j = 0; j < n; j++) {
			if (i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
		}
	}
	// ... ����
}

// �ڵ� 11.3 ����� ���ú��� �湮�ϴ� ����ȭ (������ ���� ���� ã���� �Ͽ� ����ð� ����)

// �� ���ø��� �ٸ� ���õ��� ����� ������� ������ �д�.
vector<int> nearest[MAX];
void search(double currentLength) {
	// ���� �湮�� ���õ��� ���� �õ��� ����
	int here = path.back();
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];
		// ... ����
	}
}
double solve() {
	//nearest �ʱ�ȭ
	// pair�� ��� dist������� �����ϰ� index���� �����ϴ� nearest�� �޴� ������� ���� dist ���� ������ index����
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
	// ..����..
}

// �ڵ� 11.4. ������ ��θ� �̿��ϴ� �� ���� ����ġ�� ������ ����

// path�� ������ 4���� ���� �� ��� �ִ� �� ������ ������ �ٲپ��� ��
// ��ΰ� �� ª�������� ���θ� ��ȯ�Ѵ�.
bool pathSwapPruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}
// �̰͸� �����ϴ��� ���� �Է�(n=20)�� �ð� ���� ���� ���´�.

// ���� ���ÿ� ���� ���ø� ������ path�� �κ� ��θ�
// ������ ���� �� ª�������� Ȯ���Ѵ�.
// �� �˰����� �ڱ� �ڽ��� �����ϴ� ��θ� ������ �ʵ��� ���ش�. 2���� ����� TSP ��ο��� �ڱ� �ڽ��� �����ϸ� �׻� ������ ���� �ƴϹǷ�, �� ���� ���¸� Ǯ���ִ� ���̴�.
bool pathReversePruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	for (int i = 0; i + 3 < path.size(); ++i) {
		int p = path[i];
		int a = path[i + 1];
		// [..,p,a...,b,q]�� [..,p,b,...,a,q]�� �ٲپ� ����
		if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q]) return true;
	}
	return false;
}

// �ڵ� 11.5. MST(�ּ� ���д� Ʈ��) �޸���ƽ ����
// 1. �� ������ �ִ� �� ���� ������ �� �ִ�.
// 2. �������� ���� ������ ��� ������ �� �׷����� �� �̻����� �ɰ����� �� �ȴ�.

// �ڵ� 11.6. �κ������� �޸������̼��� ����ϴ� ����ȭ�� ����

// ���� ���� ���� CACHED_DEPTH ���ϸ� ���� ��ȹ������ �ٲ۴�.
const int CACHED_DEPTH = 5;

#include <map>
map<int, double> cache[MAX][CACHED_DEPTH + 1];

double dp(int here, int visited) {
	// ���� ���: �� �湮�� ���ð� ������ ���������� ���ư���. (��Ʈ�����ڷ� 32bit���� �ִ� int������ 1�� 32���и� ���ʷ� -1�� �����Ѵ�.
	if (visited == (1 << n) - 1) return dist[here][0];
	// visited�� �Ҹ� �迭�� �ƴ� ���� ������ ������ ���, dp()�� ȣ���� ������ ��ȯ�ϴ� ������ ���� ���� �ʾƵ� �ȴ�.(9.11�� ����)

	// __builtin_popcount : g++ �����Լ�, �־��� ������ ������ ǥ������ 1�� ������ ����.
	// � ���ø� �湮������ �ش� ��Ʈ�� 1, �ƴϸ� 0���� �ϱ� ������ __builtin_popcount(visited)�� ���ݱ��� �湮�� ���� ���� �ȴ�.
	int remaining = n - __builtin_popcount(visited);
	// remaining�� �������� map�� ����� map�� �����ϴ� �ð��� ���� ���� �� �ִ�.
	double& ret = cache[here][remaining][visited];
	if (ret > 0) return ret;
	ret = INF;
	// ���� ���ø� �ϳ��� �õ��Ѵ�.
	for (int next = 0; next < n; ++next) {
		if (visited & (1 << next)) continue; // 1<<next�� ������ �湮�� ������ bit���̰�, �̰Ͱ� ���� ���� visited bit�� ��ġ�ϸ� �̹� �湮�ߴٴ� ���� �ȴ�.
		ret = min(ret, dp(next, visited + (1 << next)) + dist[here][next]);
	}
	return ret;
}

void search(int visited, double currentLength) {
	// ..����..

	// ������� : ���� ���� ���� CACHED_DEPTH���ϸ� ���� ��ȹ������ �ٲ۴�.
	if (path.size() + CACHED_DEPTH >= n) {
		best = min(best, currentLength + dp(path.back(), visited));
		return;
	}
	//.. ����
}

double solve() {
	//..����..
	// cache �ʱ�ȭ
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < CACHED_DEPTH; j++) {
			cache[i][j].clear();
		}
	}
}