#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int T, boardH, boardW, R, C;
vector<string> board;
vector<string> block;
// 게임판의 각 칸이 덮였는지를 나타낸다. 1이면 검은 칸이거나 이미 덮은 칸, 0이면 빈 칸
int covered[10][10];
int best;
int total_blank = 0;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Rotation기법 중요!!

vector<vector<pair<int, int>>> rotations;
int blockSize;

// 벡터안에 배열을 넣고 싶을때는 vector<string>으로 관리하는게 편할 수 있다.
vector<string> rotate(const vector<string>& arr) {
	// ret벡터를 미리 공간할당 받아놓는 기법으로 배열처럼 관리
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	// arr.size = 행 개수 , arr[0].size = 열 개수
	for (int i = 0; i < arr.size(); ++i) {
		for (int j = 0; j < arr[0].size(); j++) {
			// 행렬 회전 방정식
			ret[j][arr.size() - i - 1] = arr[i][j];
		}
	}
	return ret;
}

void generateRotations(vector<string>& block) {
	// vector<vector<int>> (4, ~) 형태 초기화 기법.
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		// block에서 가장 윗 줄 왼쪽칸을 원점으로 하는 상대좌표 결정 (중요한 기법!!!) 상대 좌표 원점위치를 이런식으로 잡으면 중복 제거 용이함.
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
		// 90도 회전
		block = rotate(block);
	}

	//중복제거 기법!!
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());

	blockSize = rotations[0].size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (y,x)를 왼쪽 위칸으로 해서 주어진 블록을 delta = 1로 하면 놓고, -1이면 없앤다.
// 블록을 놓을 때 이미 놓인 블록이나 검은 칸과 겹치면 거짓을, 아니면 참을 반환한다.
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

// placed : 지금까지 놓은 블럭 수
void search(int nowY, int nowX, int placed) {
	// 가지치기
	if ((total_blank / blockSize) + placed <= best) return;

	// 아직 채우지 못한 빈 칸 중 가장 윗줄 왼쪽 칸을 찾는다.
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
	// 기저 사례: 게임판을 모두 처리한 경우
	if (y == -1) {
		best = max(best, placed);
		return;
	}

	// 이 칸을 덮는다. 놓는 것을 bool 함수로 구현하여 다 놓는 것이 가능할 때만 true로 하여
	// 그것이 실제 반영되도록하고, 중간에 안될 경우 false로 반환하고 되돌린다.
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1)) {
			total_blank -= blockSize;
			search(y,x,placed + 1);
			total_blank += blockSize;
		}
		set(y, x, rotations[i], -1);
		
	}
	// 이 칸을 덮지 않고 막아둔다.(안 놓는 케이스)
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