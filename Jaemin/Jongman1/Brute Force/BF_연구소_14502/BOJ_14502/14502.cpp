#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm> // max �������� ���̺귯��
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

	// bfs�� ���ƺ��� ���� virus�� �ش��ϴ� �༮���� queue�� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tmp_board[i][j] == 2) {
				q.push({ i,j });
			}
		}
	}

	// 2�� bfs ������� Ȯ��
	// Ȯ���� board ��ġ�� ���� �ʱ� ���� tmp_Board�� ����
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

// ���ͷ� �ĺ��� �����ϱ� -> 3�� ������ ó���� �� ���� ���� �߻�. => ���!
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

// y,x���� 2���� �迭 ������ �ƴ� ���ͷ� pair�޾Ƽ� ó���ϴ� ���
void find_wall(int remain, int idx) {
	//base case
	if (remain == 0) {
		int total_virus = 0;
		bfs();
		return;
	}

	//idx�� �����ϰ� ��ͷ� ¥��, �ߺ����� for�� ���鼭 ������ �����ϴ� �ڵ带 © �� �ִ�. : input : idx, remain
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
	find_candidate(); // ������� ���ǹ��� �ð� �ҿ� x
	find_wall(3,0);

	std::cout << max_total << std::endl;
	return 0;
}


// ó�� ���� : �ϴ� 3���� wall�� �ڰ� 2���� ���������� �Ѵ����� 0�� ���� �������
// ������ ȿ�뼺�� ����ϰ� ���� ȿ���� ���� case���� ����Ѵ�.
// ������ : spread�� �ϴ� �۶߸��� ���� �ٽ� �ǵ����°� �����߰�, ���� spread ���ൿ��
// �ߺ��Ǵ� ĭ�� �־� 2�� �ִ� ĭ�� ������ tracking�ϴµ� ������� �־���.

// ���� ���� : 2�� �۶߸��� ������ ���°� �ƴ϶�, ��� 0�� ���� 2�� ���� ���������� �����ϰ�
// 2�� ���� ������ 0���� control�ϴ� ������� ���� counting
// ������ : 1�� ��ġ�ϴ� ��� ���̽��� ���� ��� 0�� ���� ���縦 �ϴϱ� �ʹ� �����ɸ�

// ���� ���� : ��� 0�� ���� 2�� ���� ���������� �ƴ� ��� 2�� ���� ���� ������ 0�� �����ϴ°� �� �����ڴ�..!
// �׸��� wall�� ���������� ��������, �ּ��� 2 ��ó�� 1��ó�� ��ġ�ϵ��� ��Ȳ�� ���� ��Ų��. �ֳ��ϸ� �̹� 1��ġ���ص�
// 8x8�� ��� 2^24 = 8�鸸���� case�̹Ƿ� ���� �ʴ�.