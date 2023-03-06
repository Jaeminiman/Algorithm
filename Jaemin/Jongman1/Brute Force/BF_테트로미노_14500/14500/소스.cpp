#include <iostream>
#include <string>
// #include <algorithm> // 입력받을 때, getline하고, std::erase()할 때, 필요했던 것인데 안썼음.
#include <sstream> // sstream : string을 공백을 기준으로 자를 때 사용
#include <vector>

using namespace std;
int N, M;
int board[500][500]; // 10^6 B = 1 MB
int max_total = 0;
int total;

const int tetroDirection[4][2] = {
	{0, -1} ,{0,1}, {1,0}, {-1,0}
}; //왼쪽 위부터 시작하므로 오른쪽, 아래로 뻗는 Type만을 고려한다.

//t_shpae은 깊이 우선 완전 탐색방식을 적용할 수 없어서 따로 shape을 관리하였다.
void select_Tshape(int y, int x) {
	int nextX, nextY;

	//x,y를 중심점으로 하고, exclude를 통해 4가지 방향 중 3가지 방향만을 선택하여 만들 수 있는 모든 case를 고려.
	for (int exclude = 0; exclude < 4; exclude++) {
		total = board[y][x];
		for (int d = 0; d < 4; d++) {
			if (d != exclude) {
				nextY = y + tetroDirection[d][0];
				nextX = x + tetroDirection[d][1];

				// 보드판 벗어나는 경우 실패
				if (nextY >= N || nextY < 0 || nextX >= M || nextX < 0) {
					break;
				}
				total += board[nextY][nextX];
			}
		}
		if (total > max_total) {
			max_total = total;
		}
		
	}
}

// t_shape외에 모든 shape고려
void select(int y, int x, int remain, int direction) {


	//base case 1 : board를 벗어난 경우(실패)
	if (y >= N || y < 0 || x >= M || x < 0) {
		return;
	}

	// board내부에 있는 경우
	else {
		total += board[y][x];

		//base case 2 : 다 선택 완료(성공)
		if (remain == 1) {
			if (total > max_total) {
				max_total = total;
			}
			total -= board[y][x];
			return;
		}


		int nextX, nextY;
		for (int d = 0; d < 3; d++) {
			// 앞에서 선택한 것으로 돌아가는 경우 : t_shape에서만 고려(BFS)
			if ((direction == 1 && d == 0) || (direction == 0 && d == 1)) {
				continue;
			}

			// 완전 탐색(DFS : 깊이우선)
			nextY = y + tetroDirection[d][0];
			nextX = x + tetroDirection[d][1];
			select(nextY, nextX, remain - 1, d);
		}
		total -= board[y][x];
	}

}

// board판을 돌면서 각 지점을 시작점으로 하는 shape을 확인
// 중복을 피하기 위해, select의 경우는 위로 향하는 방향을 고려하지 않았고, select_Tshape의 경우는 중심점에 따라 unique하므로 고려할 필요없다.
void tetromino(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			total = 0;
			select(i, j, 4,4);
			select_Tshape(i, j);
		}
	}

}
void make_board() {
	// board판 구성하기
	string line;
	string stringBuffer;
	vector<string> x;
	x.clear();

	// 맨 처음에 getline을 통해 공백을 제거해주고 for문 시작
	std::getline(cin, line);

	// 여기서 i는 행 번호.
	// 공백으로 구분되어있고, int값이 10이상인 경우를 받기 위한 코드
	for (int i = 0; i < N; i++) {
		getline(cin, line);
		istringstream ss(line);

		while (getline(ss, stringBuffer, ' ')) {
			x.push_back(stringBuffer);
		}
		for (int j = 0; j < x.size(); j++) {
			board[i][j] = stoi(x[j]);
		}
		x.clear();
	}
}
int main() {
	std::cin >> N;
	std::cin >> M;
	make_board();
	tetromino();
	cout << max_total << endl;
}