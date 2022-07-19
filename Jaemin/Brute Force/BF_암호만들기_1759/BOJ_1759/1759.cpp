#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int L, C;
vector<string> input;
int consonant_cnt = 0; // 자음 개수
int vowel_cnt = 0; // 모음 개수
string output = "";
vector<bool> isVowel;

void combination(int remain, int idx) {
	// base case
	if (remain == 0) {

		// 자음, 모음 조건 불만족(실패)
		if (consonant_cnt < 2) {
			return;
		}
		if (vowel_cnt < 1) {
			return;
		}
		cout << output << endl;
		return;
	}
	// base case 2: idx가 벗어남
	if (idx >= C ) {
		return;
	}

	for (int i = idx; i < C; i++) {
		if (isVowel[i]) {
			vowel_cnt += 1;
		}
		else {
			consonant_cnt += 1;
		}

		output += input[i];
		combination(remain - 1, i + 1);

		output = output.substr(0, output.size() - 1);
		if (isVowel[i]) {
			vowel_cnt += -1;
		}
		else {
			consonant_cnt += -1;
		}
	}
}
void make_input() {
	cin >> L;
	cin >> C;
	for (int i = 0; i < C; i++) {
		string str;
		cin >> str;
		input.push_back(str);
	}
}
void vowel() {
	for (int i = 0; i < C; i++) {
		string str = input[i];
		if (str == "i" || str == "a" || str == "e" || str == "o" || str == "u") {
			isVowel.push_back(true);
		}
		else {
			isVowel.push_back(false);
		}
	}
}
int main() {
	make_input();
	sort(input.begin(), input.end());
	vowel();
	combination(L, 0);
	
	return 0;
}