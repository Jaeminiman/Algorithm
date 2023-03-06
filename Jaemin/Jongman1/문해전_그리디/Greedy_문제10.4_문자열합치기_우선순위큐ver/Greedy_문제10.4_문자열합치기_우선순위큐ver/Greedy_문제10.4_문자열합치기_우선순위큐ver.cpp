#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int C, N;
// greater<int>를 사용하여 int가 작은 값이 우선한다.(min_heap)
// 큰 수부터 하려면 less<자료형>으로 한다.
// <자료형, 구현체, 비교연산자>로 선언
priority_queue<int, vector<int>, greater<int>> q;

int merge() {
	int cost = 0;
	while(q.size() > 1){
		// multiset을 활용하는데 있어서 idx접근이 어려웠다. 그래서 begin()만 접근할 수
		// 있는 단점을 이런식으로 극복할 수 있었다.
		// 다만 multiset의 장점으로는, 굳이 매번 정렬을 할 필요가 없었다는 것이다.
		// 그래서 이진검색트리를 이용해서 max, min 값을 갖고 놀 때는 Heap(우선순위 큐)를 사용하는 것이 이롭다.

		int min_1 = q.top(); q.pop();
		int min_2 = q.top(); q.pop();
		q.push(min_1 + min_2);
		cost += min_1 + min_2;
	}
	q.pop();
	return cost;
}
void start() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		q.push(x);
	}
}
int main() {
	cin >> C;

	for (int epoch = 0; epoch < C; epoch++) {
		start();
		int ret = merge();
		cout << ret << endl;
	}
	return 0;
}