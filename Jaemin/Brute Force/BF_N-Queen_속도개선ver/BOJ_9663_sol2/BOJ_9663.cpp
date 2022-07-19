#include <iostream>

using namespace std;

// �������� ������ good!
int chase[15]{ -1 };
int N, total = 0;

bool check_okay(int y2) {
	int x2 = chase[y2];
	bool okay = true;
	int x1;
	
	for (int y1 = 0; y1 < y2; y1++) {
		x1 = chase[y1];
		
		//�� �˻�
		if (x2 == x1) {
			okay = false;
			break;
		}
		// y = x + b, y = -x + b �˻�
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

	// flow : �ϴ� �ڰ� �̰� �Ǵ��� Ȯ���ϴ� ��.
	// ���ȣ���� ���� row�� �ǳʶٰ�, for���� ���� �� column�� �˻��ϴ� ���
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