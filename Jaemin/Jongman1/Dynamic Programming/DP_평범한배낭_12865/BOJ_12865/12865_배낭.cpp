#include <iostream>
#include <vector>
#include <algorithm>
#include<cstring> // memset �ʱ�ȭ�� ���� �������

using namespace std;
int N, K;
const int NEGINF = -123456789;
vector<pair<int, int>> database;
int cache[100001][100]; // Weight ������ 0���� K�����̹Ƿ� K+1 ���� �Ҵ��� �ʿ���.

int bag(int weight, int idx) {
	// �� base case ���� �κ��� �ణ ��򸮴µ�, ret ����(��ȭ��)�� ���� ������ ���踦 �ؾ���
	// ��ȭ�Ŀ��� ���� idx��ġ�� item�� �ְ� �����Ÿ� ���� �ȳְ� �����Ÿ� ���� �����Ѵ�.
	// ���� �ִ´ٴ� ������ �ϴ� ��쿡�� ���� �� ������ bag()�Լ��� ȣ��Ǵµ�, �̶���
	// ���԰� �ʰ��Ǵ� ��� ���� ���̽� ����� ���� ���ϵ��� �����ؾ� �Ѵ�. 
	// �׸� ���� NEGINF�� ��ȯ�ϵ��� �ϰ�, ���� �����ִ� idx�� �迭 ������ �� �ôٸ�
	// �׸� input���� �ϴ� bag()ȣ�� ���� ���þ��ϰ� �����ϴ� ���� �±� ������ 0�� ��ȯ�Ѵ�.
	// �׷��� �Ǹ� ���� �������� ������ �ϰ� �� ��쿡�� ���� idx��ġ�� value����
	// ���� ä�� �����ϰ� �ȴ�.
	
	// base case : ���Ը� �ʰ��� ���(����)
	if (weight > K) return NEGINF;
	// base case : idx ���� �� �� ���(����)
	if (idx == N) return 0;

	int& ret = cache[weight][idx];
	if (ret != -1) return ret;
	
	ret = max(bag(weight + database[idx].first, idx + 1) + database[idx].second,
		bag(weight, idx + 1));
	
	return ret;
}
void start() {
	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		int w, v;
		cin >> w >> v;
		database.push_back(make_pair(w, v));
	}
	// -1�� �ʱ�ȭ �ϱ����� �ڵ�
	memset(cache, -1, sizeof(cache));
}
int main() {
	start();
	int ret = bag(0, 0);
	cout << ret << endl;
	return 0;
}