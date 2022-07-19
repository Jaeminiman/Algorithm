#include <iostream>
#include <string>
// #include <algorithm> // �Է¹��� ��, getline�ϰ�, std::erase()�� ��, �ʿ��ߴ� ���ε� �Ƚ���.
#include <sstream> // sstream : string�� ������ �������� �ڸ� �� ���
#include <vector>

using namespace std;
int N, M;
int board[500][500]; // 10^6 B = 1 MB
int max_total = 0;
int total;

const int tetroDirection[4][2] = {
	{0, -1} ,{0,1}, {1,0}, {-1,0}
}; //���� ������ �����ϹǷ� ������, �Ʒ��� ���� Type���� ����Ѵ�.

//t_shpae�� ���� �켱 ���� Ž������� ������ �� ��� ���� shape�� �����Ͽ���.
void select_Tshape(int y, int x) {
	int nextX, nextY;

	//x,y�� �߽������� �ϰ�, exclude�� ���� 4���� ���� �� 3���� ���⸸�� �����Ͽ� ���� �� �ִ� ��� case�� ���.
	for (int exclude = 0; exclude < 4; exclude++) {
		total = board[y][x];
		for (int d = 0; d < 4; d++) {
			if (d != exclude) {
				nextY = y + tetroDirection[d][0];
				nextX = x + tetroDirection[d][1];

				// ������ ����� ��� ����
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

// t_shape�ܿ� ��� shape���
void select(int y, int x, int remain, int direction) {


	//base case 1 : board�� ��� ���(����)
	if (y >= N || y < 0 || x >= M || x < 0) {
		return;
	}

	// board���ο� �ִ� ���
	else {
		total += board[y][x];

		//base case 2 : �� ���� �Ϸ�(����)
		if (remain == 1) {
			if (total > max_total) {
				max_total = total;
			}
			total -= board[y][x];
			return;
		}


		int nextX, nextY;
		for (int d = 0; d < 3; d++) {
			// �տ��� ������ ������ ���ư��� ��� : t_shape������ ���(BFS)
			if ((direction == 1 && d == 0) || (direction == 0 && d == 1)) {
				continue;
			}

			// ���� Ž��(DFS : ���̿켱)
			nextY = y + tetroDirection[d][0];
			nextX = x + tetroDirection[d][1];
			select(nextY, nextX, remain - 1, d);
		}
		total -= board[y][x];
	}

}

// board���� ���鼭 �� ������ ���������� �ϴ� shape�� Ȯ��
// �ߺ��� ���ϱ� ����, select�� ���� ���� ���ϴ� ������ ������� �ʾҰ�, select_Tshape�� ���� �߽����� ���� unique�ϹǷ� ����� �ʿ����.
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
	// board�� �����ϱ�
	string line;
	string stringBuffer;
	vector<string> x;
	x.clear();

	// �� ó���� getline�� ���� ������ �������ְ� for�� ����
	std::getline(cin, line);

	// ���⼭ i�� �� ��ȣ.
	// �������� ���еǾ��ְ�, int���� 10�̻��� ��츦 �ޱ� ���� �ڵ�
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