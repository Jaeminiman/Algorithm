#include <iostream>
#include <stack>
#include <cstring>

using namespace std;
int R, C;
bool building[10002][502];
bool DP[10002][502];

//direction ��ġ ���� �߿�
const int direction[3][2] = {
	{-1,1}, {0,1},{1,1}
};


bool ENDSIGN = 0;
int cnt = 0;

void pipe(int y, int x) {
	// �� �� ���� ��ġ�� ������ ���(����)
	if (building[y][x]) {
		return;
	}
	// ����
	if (x == C) {
		ENDSIGN = 1;
		cnt++;
		return;
	}
	
	bool& visited = DP[y][x];
	if (visited) return;

	building[y][x] = true;
	visited = true;

	for (int d = 0; d < 3; d++) {
		int nextY = y + direction[d][0], nextX = x + direction[d][1];
		pipe(nextY, nextX);
		// ENDSIGN ������ �ξ� ���� route�� ã���� ���̻� DFS�� ���������ʰ� �����ϴ� ����� ���
		if (ENDSIGN) {
			break;
		}
	}
	// ���� ���������� return�Ҷ��� pipe�� �ٽ� ö���� �ʿ䰡 ���� �״�� ��.
	if (!ENDSIGN) {
		building[y][x] = false;
	}
	return;
}

void start() {
	cin >> R >> C;
	for (int i = 0; i <= R + 1; i++) {
		for (int j = 0; j <= C + 1; j++) {
			if (i == 0 || i == R + 1 || j == 0 || j == C + 1) {
				building[i][j] = true;
			}
			else {
				char x;
				cin >> x;
				if (x == '.') {
					building[i][j] = false;
				}
				else {
					building[i][j] = true;
				}
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	start();
	memset(DP, false, sizeof(DP));
	for (int i = 1; i <= R; i++) {
		pipe(i, 1);
		ENDSIGN = 0;
	}
	cout << cnt << '\n';
	return 0;
}