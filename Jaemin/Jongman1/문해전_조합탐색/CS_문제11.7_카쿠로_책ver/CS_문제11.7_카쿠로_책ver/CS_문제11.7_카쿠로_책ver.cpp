#include <iostream>

using namespace std;

// 코드 11.11 비트마스크를 이용한 카쿠로의 후보 구하기

// 마스크에 속한 원소들의 개수를 반환한다.
int getSize(int mask);
// mask에 속한 원소들의 합을 반환한다.
int getSum(int mask);

// len칸의 합이 sum이고, 이 칸들에 이미 쓰인 수의 집합이 known일 때
// 나머지 칸에 들어갈 수 있는 숫자의 집합을 반환한다.
int getCandidates(int len, int sum, int known) {
	// 조건에 부합하는 집합들의 교집합
	int allSets = 0;
	// 1~9의 부분집합(즉, 모든 짝수)을 모두 생성하고, 그 중
	// known을 포함하고, 크기가 len이며, 합이 sum인 집합을 모두 찾는다.
	for (int set = 0; set < 1024; set += 2) {
		if ((set & known) == known && getSize(set) == len && getSum(set) == sum) {
			allSets |= set;
		}
	}
	// known에서 이미 known에 속한 것은 답의 목록에서 제거한다.
	return allSets & ~known;
}

// 코드 11.12 카쿠로에서 후보의 수를 미리 계산하는 알고리즘

// candidates[len][sum][known] = getCandidates(len,sum,known)
int candidates[10][46][1024];

// candidates[][][]를 미리 계산해 둔다.
void generateCandidates() {
	memset(candidates, 0, sizeof(candidates));
	// 1~9의 부분집합을 전부 생성한다.
	for (int set = 0; set < 1024; set += 2) {
		// 집합의 크기와 원소의 합을 계산해 둔다.
		int l = setSize(set), s = setSum(set);
		// set의 모든 부분 집합에 대해 candidates[][][]를 갱신한다.
		int subset = set;
		while (true) {
			//숫자 하나의 합이 s이고, 이미 subset 숫자가 쓰여있을 때
			//전체 숫자의 집합이 set이 되도록 나머지 숫자를 채워넣을 수 있다.
			candidates[l][s][subset] |= (set & ~subset);
			if (subset == 0) break;
			subset = (subset - 1) & set;
		}
			
	}
}

int main() {
	return 0;
}