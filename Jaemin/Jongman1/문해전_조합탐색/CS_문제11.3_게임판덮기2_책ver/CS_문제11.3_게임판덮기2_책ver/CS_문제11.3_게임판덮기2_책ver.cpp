#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int T, boardH, boardW, R, C;
vector<string> board;
vector<string> block;
// �������� �� ĭ�� ���������� ��Ÿ����. 1�̸� ���� ĭ�̰ų� �̹� ���� ĭ, 0�̸� �� ĭ
int covered[10][10];
int best;
int total_blank = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Rotation��� �߿�!!

vector<vector<pair<int, int>>> rotations;
int blockSize;

// ���;ȿ� �迭�� �ְ� �������� vector<string>���� �����ϴ°� ���� �� �ִ�.
vector<string> rotate(const vector<string>& arr) {
	// ret���͸� �̸� �����Ҵ� �޾Ƴ��� ������� �迭ó�� ����
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	// arr.size = �� ���� , arr[0].size = �� ����
	for (int i = 0; i < arr.size(); ++i) {
		for (int j = 0; j < arr[0].size(); j++) {
			// ��� ȸ�� ������
			ret[j][arr.size() - i - 1] = arr[i][j];
		}
	}
	return ret;
}

void generateRotations(vector<string>& block) {
	// vector<vector<int>> (4, ~) ���� �ʱ�ȭ ���.
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		// block���� ���� �� �� ����ĭ�� �������� �ϴ� �����ǥ ���� (�߿��� ���!!!) ��� ��ǥ ������ġ�� �̷������� ������ �ߺ� ���� ������.
		int originY = -1, originX = -1;
		for (int i = 0; i < block.size(); i++) {
			for (int j = 0; j < block[0].size(); j++) {
				if (block[i][j] == '#') {
					if (originY == -1) {
						originY = i;
						originX = j;
					}
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
			}
			
		}
		// 90�� ȸ��
		block = rotate(block);
	}

	//�ߺ����� ���!!
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());

	blockSize = rotations[0].size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (y,x)�� ���� ��ĭ���� �ؼ� �־��� ����� delta = 1�� �ϸ� ����, -1�̸� ���ش�.
// ����� ���� �� �̹� ���� ����̳� ���� ĭ�� ��ġ�� ������, �ƴϸ� ���� ��ȯ�Ѵ�.
bool set(int y, int x,const vector<pair<int,int>>& block, int delta) {
	vector<pair<int, int>> tmp = block;
	bool ok = true;

	while (!tmp.empty()) {
		pair<int, int> loc = tmp.back(); tmp.pop_back();
		int abs_y = y + loc.first, abs_x = x + loc.second;

		if (abs_y < 0 || abs_y >= boardH || abs_x < 0 || abs_x >= boardW) {
			ok = false;
		}
		else {
			if (covered[abs_y][abs_x] >= 1) {
				ok = false;
			}
			covered[abs_y][abs_x] += delta;
		}
	}
	return ok ;
}

// placed : ���ݱ��� ���� �� ��
void search(int nowY, int nowX, int placed) {
	// ����ġ��
	if ((total_blank / blockSize) + placed <= best) return;

	// ���� ä���� ���� �� ĭ �� ���� ���� ���� ĭ�� ã�´�.
	int y = -1, x = -1;
	for (int i = nowY; i < boardH; i++) {
		for (int j = 0; j < boardW; j++) {
			if (i == nowY && j < nowX) continue;

			if (covered[i][j] == 0) {
				y = i; x = j;
				break;
			}
		}
		if (y != -1) break;
	}
	// ���� ���: �������� ��� ó���� ���
	if (y == -1) {
		best = max(best, placed);
		return;
	}

	// �� ĭ�� ���´�. ���� ���� bool �Լ��� �����Ͽ� �� ���� ���� ������ ���� true�� �Ͽ�
	// �װ��� ���� �ݿ��ǵ����ϰ�, �߰��� �ȵ� ��� false�� ��ȯ�ϰ� �ǵ�����.
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1)) {
			total_blank -= blockSize;
			search(y,x,placed + 1);
			total_blank += blockSize;
		}
		set(y, x, rotations[i], -1);
		
	}
	// �� ĭ�� ���� �ʰ� ���Ƶд�.(�� ���� ���̽�)
	covered[y][x] = 1;
	total_blank -= 1;
	search(y,x,placed);
	total_blank += 1;
	covered[y][x] = 0;
}
void start() {
	cin >> boardH >> boardW;
	cin >> R >> C;
	board.clear();
	board.resize(boardH);
	for (int i = 0; i < boardH; i++) {
		board[i] = string(boardW, ' ');
	}
	block.clear();
	block.resize(R);
	for (int j = 0; j < R; j++) {
		block[j] = string(C, ' ');
	}
	best = 0;
	total_blank = 0;

	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++) {
			char ch;
			cin >> ch;
			board[i][j] = ch;
			if (ch == '.') {
				total_blank += 1;
			}
			covered[i][j] = (ch == '#') ? 1 : 0;
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			char ch;
			cin >> ch;
			block[i][j] = ch;
		}
	}
}
int main() {
	cin >> T;
	for (int epoch = 0; epoch < T; epoch++) {
		start();
		generateRotations(block);
		search(0,0,0);
		cout << best << endl;
	}
}