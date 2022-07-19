#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm> // max 쓰기위한 라이브러리
using namespace std;


int board[8][8];
int tmp_board[8][8];

bool visited[8][8] = {false};
vector<pair<int,int>> candidate;
int N, M;
int max_total = 0;
int total = 0;

const int direction[8][2] = {
	{0,1},{0,-1},{1,0},{-1,0} , {1,1},{1,-1}, {-1,1},{-1,-1}
};


void copy() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tmp_board[i][j] = board[i][j];
		}
	}
}

void bfs() {
	queue<pair<int, int>> q;
	copy();

	// bfs로 돌아보기 위해 virus에 해당하는 녀석들을 queue에 삽입
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmp_board[i][j] == 2) {
				q.push({ i,j });
			}
		}
	}

	// 2의 bfs 방식으로 확산
	// 확산이 board 망치게 하지 않기 위해 tmp_Board로 관리
	while (q.size()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int ny = y + direction[k][0];
			int nx = x + direction[k][1];

			if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
			
			if (tmp_board[ny][nx] == 0) {
				tmp_board[ny][nx] = 2;
				q.push({ ny,nx });
			}
		}
	}

	int total = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmp_board[i][j] == 0) {
				total += 1;
			}
		}
	}
	max_total = std::max(total, max_total);
}

// 벡터로 후보자 관리하기 -> 3번 예제를 처리할 수 없는 문제 발생. => 폐기!
//void find_candidate() {
//
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < M; j++) {
//			if (board[i][j]== 2 || board[i][j] == 1) {
//				for (int d = 0; d < 8; d++) {
//					int nextY = i + direction[d][0];
//					int nextX = j + direction[d][1];
//					if (nextY >= 0 && nextY < N && nextX >= 0 && nextX < M){			
//						if (!visited[nextY][nextX] && board[nextY][nextX] == 0) {
//							candidate.push_back({ nextY, nextX });
//							visited[nextY][nextX] = true;
//						}
//					}
//				}
//			}
//		}
//	}
//}
void find_candidate() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 0) {
				candidate.push_back({ i,j });
			}
		}
	}
}

// y,x로의 2차원 배열 접근이 아닌 벡터로 pair받아서 처리하는 방법
void find_wall(int remain, int idx) {
	//base case
	if (remain == 0) {
		int total_virus = 0;
		bfs();
		return;
	}

	//idx로 관리하고 재귀로 짜면, 중복없이 for문 돌면서 여러개 선택하는 코드를 짤 수 있다. : input : idx, remain
	for (int i = idx; i < candidate.size(); i++) {
		int y = candidate[i].first;
		int x = candidate[i].second;
		board[y][x] = 1;
		find_wall(remain - 1, i + 1);
		board[y][x] = 0;
	}
}
void make_board() {
	string line;
	string stringBuffer;
	vector<string> x;
	x.clear();

	
	getline(cin, line);
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
int main(void) {
	std::cin >> N;
	std::cin >> M;
	make_board();
	find_candidate(); // 여기까진 유의미한 시간 소요 x
	find_wall(3,0);

	std::cout << max_total << std::endl;
	return 0;
}


// 처음 접근 : 일단 3개의 wall을 박고서 2에서 퍼져나가게 한다음에 0을 세는 방식으로
// 각각의 효용성을 계산하고 가장 효용이 좋은 case만을 출력한다.
// 문제점 : spread를 일단 퍼뜨리고 나면 다시 되돌리는게 복잡했고, 또한 spread 진행동안
// 중복되는 칸이 있어 2가 있는 칸의 개수를 tracking하는데 어려움이 있었다.

// 다음 접근 : 2를 퍼뜨리고 개수를 세는게 아니라, 모든 0에 대해 2에 접근 가능한지를 조사하고
// 2에 접근 가능한 0만을 control하는 방식으로 갯수 counting
// 문제점 : 1을 설치하는 모든 케이스에 대해 모든 0에 대해 조사를 하니까 너무 오래걸림

// 다음 접근 : 모든 0에 대해 2에 접근 가능한지가 아닌 모든 2에 대해 접근 가능한 0을 제외하는게 더 빠르겠다..!
// 그리고 wall를 무지성으로 깔지말고, 최소한 2 근처나 1근처에 배치하도록 상황을 변경 시킨다. 왜냐하면 이미 1배치만해도
// 8x8의 경우 2^24 = 8백만번의 case이므로 적지 않다.