#include <iostream>

const int queenRange[3][2] = {
	{1,0},{1,1},{1,-1} // �Ʒ���, �밢�� 3���⸸ ���. ������ �ؿ��� ��ġ�� ���̱� ����.
};
// Tip : 8���� ��� -> 4���� ��� �ߴ��� N=11 ����ð� �������� �� 50 -> 20
// Tip : 4���� -> 3���� ��� �ߴ��� N=11 ����ð� 20 -> 10

// ���� ������ �� �ִ� ������ �ִ� chase���� ��� true,false�� �ٲ��ִ� �Լ�
int set_queen(int n, int y, int x, int (&chase)[15][15], bool sign) { 
	for (int i = 0; i < 3; i++) {
		int mul = 1;

		// �� �κ� �ڵ� ������..
		int nextY = y + mul * queenRange[i][0];
		int nextX = x + mul * queenRange[i][1];
		while (nextY < n && nextY >= 0 && nextX < n && nextX>= 0) {
			if (sign == true) {
				chase[nextY][nextX] += 1;
			}
			else {
				chase[nextY][nextX] += -1;
			}
			mul++;
			nextY = y + mul * queenRange[i][0];
			nextX = x + mul * queenRange[i][1];
		}
	}
	return 0;
}


int count_queen(int n, int remain, int y, int x, int (&chase)[15][15]) {
	// n : ��ü �� ����
	// remain : ���� �� ����
	// chase : chase�� database

	// base case
	if (remain == 0) {
		return 1;
	}
	//// ������ ���� �ߺ��� �����ϱ� ����
	//// ä�� �� �ִ� ĭ �� ���� ���� ���ʿ� �ִ� ĭ�� ã�´�.
	//int y = -1; int x = -1;
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		if (chase[i][j] == 0) {
	//			y = i;
	//			x = j;
	//				break;
	//			}
	//		}
	//		// 2�� for�� Ż�� ����
	//		if (y != -1) {
	//			break;
	//		}
	//	}

	//	// remain�� ������ �� ĭ�� ���� ��� (����)
	//	if (y == -1) {
	//		return 0;
	//	}

		// remain�� �ִ� ���
	int sum = 0;
		
	for(int i = y; i < n; i++){ // ������ �ؿ� �ٺ��� ���� ������ ���� ���̹Ƿ� i = y;
		for(int j = 0; j < n; j++){
			if (chase[i][j] == 0) {
				 chase[i][j] = 1; // ���⿡ �ڴ´ٴ� ��
				set_queen(n, i, j, chase,true); // [i][j]�ֺ� queen ���ݹ����� +1
				sum += count_queen(n, remain - 1, i + 1, j, chase); // remain�� 1 �پ���, ���� ��ġ�� y ��ġ�� ��� �ϳ� �Ʒ��� ���� ����.
				chase[i][j] = 0;
				set_queen(n, i, j, chase, false); // [i][j]�ֺ� queen �Ʊ� +1�ߴ� �κ� �ٽ� ȸ��	
			}
			
		}
	}


	return sum;
}

int main() {
	int n;
	std::cin >> n;
	int chase[15][15]{ 0 };
	bool queen[15] = { false };

	int result = count_queen(n, n, 0, 0, chase);
	
	std::cout << result << std::endl;
	
}