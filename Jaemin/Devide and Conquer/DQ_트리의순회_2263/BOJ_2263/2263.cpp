#include <vector>
#include <iostream>

using namespace std;
vector<int> inorder(100000,0);
vector<int> postorder(100000,0);
vector<int> preorder;
int N;

// 왼쪽이랑 오른쪽일 때 indexing방식이 다름. 왼쪽은 똑같으나, 오른쪽은 idx가 1 shift됨.
// 개선할 점: 나는 left_cnt로 이 상황을 해소하고자 했는데, post에서의 시작, 끝을 따로 인자로 받고
// left_size와 right_size를 매 번 계산하여 둘의 indexing 차이를 극복할 수 도 있다.
void make_preorder(int r, int l, int left_cnt) {
	// base case 1: 배열의 크기가 0
	if (l - r < 0) {
		return;
	}

	int root = postorder[l];
	preorder.push_back(root);

	int idx = r; 
	for (int i = 0; i < N; i++) {
		if (inorder[i] == root) {
			idx = i - left_cnt;
			break;
		}
	}
	
	int mid = idx;
	make_preorder(r, mid - 1,left_cnt);
	make_preorder(mid, l-1, left_cnt + 1);
	
}
void start() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> inorder[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> postorder[i];
	}
}
void print() {
	for (int i = 0; i < preorder.size(); i++) {
		cout << preorder[i];
		cout << " ";
	}
}
int main() {
	start();
	make_preorder(0, N - 1,0);
	print();

	return 0;
}