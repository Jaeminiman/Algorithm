#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int direction[2][2] = {
	{0,1}, {1,0}
};
int C, N, Q;
int board[22][22];
struct Hint {
	int y, x, d, num;
};
bool compare(Hint& a, Hint& b){
	return a.num > b.num;
}

vector<Hint> hints;
int visited[22][22] = {0,};
bool SIGNAL = 0;

void put(int y, int x, int direct, int remains, bool bin[]) {
	//기저 사례 1 : y,x가 범위를 벗어나거나 검은칸 or 힌트칸에 도달한 경우(실패)
	//기저 사례 2 : (remains = 0 && 끝에 도달) (성공)
	if (board[y][x] == -1) {
		// success
		if (remains == 0) {
			// 기저 사례 3 : 완전 탐색 끝난 경우(종료)
			if (hints.empty()) {
				SIGNAL = 1;
				return;
			}

			Hint hint = hints.back(); hints.pop_back();
			bool b[10] = {false,};
			b[0] = true;
			int nextY = hint.y, nextX = hint.x;
			while (board[nextY][nextX] != -1) {
				if (board[nextY][nextX] != 0) {
					b[board[nextY][nextX]] = true;
				}
				nextY = nextY + direction[hint.d][0];
				nextX = nextX + direction[hint.d][1];
			}
			put(hint.y, hint.x, hint.d, hint.num, b);
			return;
		}
		// fail
		else
			return;
	}

	visited[y][x] ++;
	int nextY = y + direction[direct][0], nextX = x + direction[direct][1];
	for (int i = 1; i <= min(remains,9); i++) {
		// 이미 사용한 숫자
		if (bin[i])	continue;

		else {
			// 이미 다른 수로 채움
			if (visited[y][x] > 1) {

				put(nextY, nextX, direct, remains - board[y][x], bin);
				// 완전 종료 시그널
				if (SIGNAL) {
					return;
				}
			}
			else {
				board[y][x] = i;
				bin[i] = true;
				put(nextY, nextX, direct, remains - i, bin);
				bin[i] = false;
				// 완전 종료 시그널
				if (SIGNAL) {
					return;
				}
				board[y][x] = 0;
			}
		}

	}
	visited[y][x] --;
}
void hint_setting() {
	cin >> Q;
	hints.clear();
	int y, x, d, sum;
	for (int i = 0; i < Q; i++) {
		cin >> y >> x >> d >> sum;
		int nextY = y + direction[d][0], nextX = x + direction[d][1];
		Hint hint = { nextY, nextX, d, sum};
		hints.push_back(hint);
	}
	sort(hints.begin(), hints.end(), compare);
}
void board_setting() {
	cin >> N;
	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {
			// 외곽부 -1로 통일
			if (i == 0 || i == N + 1 || j == 0 || j == N + 1) {
				board[i][j] = -1;
			}
			// 1(백지)에는 0을 놓고
			// 0(힌트나 검은칸)에는 -1을 넣는다.
			else {
				int x;
				cin >> x;
				if (x == 1) {
					board[i][j] = 0;
				}
				else {
					board[i][j] = -1;
				}
			}
		}
	}
}
int main() {
	cin >> C;
	for (int epoch = 0; epoch < C; epoch++) {
		board_setting();
		hint_setting();
		Hint hint = hints.back(); hints.pop_back();
		bool b[10] = {false,};
		b[0] = true;
		put(hint.y, hint.x, hint.d, hint.num, b);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {

				cout << max(0,board[i][j]) << " ";
			}
			cout << '\n';
		}
	}
	return 0;
}