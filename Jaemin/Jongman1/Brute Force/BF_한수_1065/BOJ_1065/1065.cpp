#include <iostream>
#include <string>
using namespace std;

int main() {
	int n;
	int result = 0;
	std::cin >> n;
	for (int num = 1; num <= n; num++) {
		if (num < 100) {
			result++;
			continue;
		}

		string number = to_string(num);
		bool hansoo = true;
		int dist = number[0] - number[1];
		for (int i = 1; i < number.size() - 1; i++) {
			int dist_2 = number[i] - number[i + 1];
			if (dist != dist_2) {
				hansoo = false;
				break;
			}
		}
		if (hansoo) {
			result++;
		}

	}

	std::cout << result << std::endl;
}