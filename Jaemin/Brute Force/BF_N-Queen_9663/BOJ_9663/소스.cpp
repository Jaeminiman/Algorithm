#include <iostream>

const int queenRange[3][2] = {
	{1,0},{1,1},{1,-1} // 아래쪽, 대각선 3방향만 고려. 어차피 밑에만 배치할 것이기 때문.
};
// Tip : 8방향 고려 -> 4방향 고려 했더니 N=11 수행시간 절반으로 줆 50 -> 20
// Tip : 4방향 -> 3방향 고려 했더니 N=11 수행시간 20 -> 10

// 퀸이 공격할 수 있는 범위에 있는 chase판을 모두 true,false로 바꿔주는 함수
int set_queen(int n, int y, int x, int (&chase)[15][15], bool sign) { 
	for (int i = 0; i < 3; i++) {
		int mul = 1;

		// 이 부분 코드 난잡함..
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
	// n : 전체 퀸 개수
	// remain : 남은 퀸 개수
	// chase : chase판 database

	// base case
	if (remain == 0) {
		return 1;
	}
	//// 순서에 따른 중복을 방지하기 위해
	//// 채울 수 있는 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다.
	//int y = -1; int x = -1;
	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < n; j++) {
	//		if (chase[i][j] == 0) {
	//			y = i;
	//			x = j;
	//				break;
	//			}
	//		}
	//		// 2중 for문 탈출 조건
	//		if (y != -1) {
	//			break;
	//		}
	//	}

	//	// remain은 있으나 들어갈 칸이 없는 경우 (실패)
	//	if (y == -1) {
	//		return 0;
	//	}

		// remain이 있는 경우
	int sum = 0;
		
	for(int i = y; i < n; i++){ // 어차피 밑에 줄부터 놓을 공간이 있을 것이므로 i = y;
		for(int j = 0; j < n; j++){
			if (chase[i][j] == 0) {
				 chase[i][j] = 1; // 여기에 박는다는 뜻
				set_queen(n, i, j, chase,true); // [i][j]주변 queen 공격범위에 +1
				sum += count_queen(n, remain - 1, i + 1, j, chase); // remain은 1 줄어들고, 다음 위치는 y 위치가 적어도 하나 아래에 있을 것임.
				chase[i][j] = 0;
				set_queen(n, i, j, chase, false); // [i][j]주변 queen 아까 +1했던 부분 다시 회수	
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