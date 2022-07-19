#include <iostream>

using namespace std;

// 전역변수 설정법 good!
int chase[15]{ -1 };
int N, total = 0;

bool check_okay(int y2) {
	int x2 = chase[y2];
	bool okay = true;
	int x1;
	
	for (int y1 = 0; y1 < y2; y1++) {
		x1 = chase[y1];
		
		//열 검사
		if (x2 == x1) {
			okay = false;
			break;
		}
		// y = x + b, y = -x + b 검사
		if ((y1 - x1 == y2 - x2) || (y1 + x1 == y2 + x2)) {
			okay = false;
			break;
		}
	}

	return okay;
}
void count_queen(int y) {
	//base case
	if (y == N) {
		total++;
	}

	// flow : 일단 박고 이게 되는지 확인하는 식.
	// 재귀호출을 통해 row를 건너뛰고, for문을 통해 각 column을 검사하는 방식
	else {
		for (int k = 0; k < N; k++) {
			chase[y] = k;
			if (check_okay(y)) {
				count_queen(y + 1);
			}
		}

	}

}
int main(void) {
	std::cin >> N;
	count_queen(0);

	std::cout << total << std::endl;

}