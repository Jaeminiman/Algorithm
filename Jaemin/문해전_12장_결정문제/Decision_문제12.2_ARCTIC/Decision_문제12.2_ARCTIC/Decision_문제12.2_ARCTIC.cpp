#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <cstring>
#include <cmath>
using namespace std;

int C, n;
// �� ���� ������ �Ÿ��� �̸� ����صд�.
double dists[100][100];

// ���� ���� : ������ ���̰� d ������ ��峢�� ������ �׷����� ���� ��� ��忡�� ����Ǵ°�?
// �׷��� ��ȸ���� �ʿ��� �ʵ� �� ����
// 1. visited(�湮�ߴ���) 2. queue / stack (BFS vs. DFS) 3. dist[here][there]
bool decision(double d) {
	vector<bool> visited(n, false);
	visited[0] = true;
	// queue�� ���� BFS ����
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front(); q.pop();
		++seen;
		for (int there = 0; there < n; there++) {
			if (!visited[there] && dists[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
		}
	}
	return seen == n;
}
double optimize() {
	double lo = 0, hi = 1416.00;
	for (int it = 0; it < 100; ++it) {
		double mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else {
			lo = mid;
		}
	}
	return hi;
}
int main() {
	cin >> C;
	for (int epoch = 0; epoch < C; epoch++) {
		cin >> n;
		memset(dists, 0, sizeof(dists));
		vector<pair<double, double>> points;
		for (int i = 0; i < n; i++) {
			double x, y;
			cin >> x >> y;
			points.push_back(make_pair(x, y));
		}
		
		for(int i = 0; i < n ; i++){
			pair<double, double> here = points[i];
			for (int j = i; j < n; j++) {
				pair<double, double> there = points[j];
				double dist = sqrt(pow(here.first - there.first, 2) + pow(here.second - there.second, 2));
				dists[i][j] = dist; dists[j][i] = dist;
			}	
		}

		// �Ҽ��� �Ʒ� n ��° �ڸ��� �ݿø� �ڵ�
		//	double result = optimize();
		//	result *= 100;
		//	result = round(result);
		//	result /= 100;

		// �Ҽ��� �Ʒ� 2�ڸ� �� ��� ���� �ڵ�
		cout << fixed;
		cout.precision(2);
		cout <<  optimize() << endl;
	}
	
	
	return 0;
}