#include <vector>
#include <iostream>

using namespace std;
vector<int> inorder(100000,0);
vector<int> postorder(100000,0);
vector<int> preorder;
int N;

// �����̶� �������� �� indexing����� �ٸ�. ������ �Ȱ�����, �������� idx�� 1 shift��.
// ������ ��: ���� left_cnt�� �� ��Ȳ�� �ؼ��ϰ��� �ߴµ�, post������ ����, ���� ���� ���ڷ� �ް�
// left_size�� right_size�� �� �� ����Ͽ� ���� indexing ���̸� �غ��� �� �� �ִ�.
void make_preorder(int r, int l, int left_cnt) {
	// base case 1: �迭�� ũ�Ⱑ 0
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