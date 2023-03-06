#include <iostream>
#include <string>

using namespace std;
int N;
int maxDP[3] = { 0,0,0 }, minDP[3] = { 0,0,0 };

int main() {
	int input[3];
	int tmp[3];
	cin >> N;
	cin >> maxDP[0] >> maxDP[1] >> maxDP[2];
	minDP[0] = maxDP[0]; minDP[1] = maxDP[1]; minDP[2] = maxDP[2];
	for (int i = 1; i < N; i++) {
		cin >> input[0] >> input[1] >> input[2];
		
		tmp[0] = maxDP[0]; tmp[1] = maxDP[1]; tmp[2] = maxDP[2];
		maxDP[0] = max(tmp[0], tmp[1]) + input[0];
		maxDP[1] = max(max(tmp[0], tmp[1]), tmp[2]) + input[1];
		maxDP[2] = max(tmp[1], tmp[2]) + input[2];

		tmp[0] = minDP[0]; tmp[1] = minDP[1]; tmp[2] = minDP[2];
		minDP[0] = min(tmp[0], tmp[1]) + input[0];
		minDP[1] = min(min(tmp[0], tmp[1]), tmp[2]) + input[1];
		minDP[2] = min(tmp[1], tmp[2]) + input[2];
	}
	int result_max = max(max(maxDP[0], maxDP[1]), maxDP[2]);
	int result_min = min(min(minDP[0], minDP[1]), minDP[2]);
	cout << to_string(result_max) + " " + to_string(result_min) << endl;
	return 0;
}