#include <iostream>

using namespace std;

// �ڵ� 11.11 ��Ʈ����ũ�� �̿��� ī����� �ĺ� ���ϱ�

// ����ũ�� ���� ���ҵ��� ������ ��ȯ�Ѵ�.
int getSize(int mask);
// mask�� ���� ���ҵ��� ���� ��ȯ�Ѵ�.
int getSum(int mask);

// lenĭ�� ���� sum�̰�, �� ĭ�鿡 �̹� ���� ���� ������ known�� ��
// ������ ĭ�� �� �� �ִ� ������ ������ ��ȯ�Ѵ�.
int getCandidates(int len, int sum, int known) {
	// ���ǿ� �����ϴ� ���յ��� ������
	int allSets = 0;
	// 1~9�� �κ�����(��, ��� ¦��)�� ��� �����ϰ�, �� ��
	// known�� �����ϰ�, ũ�Ⱑ len�̸�, ���� sum�� ������ ��� ã�´�.
	for (int set = 0; set < 1024; set += 2) {
		if ((set & known) == known && getSize(set) == len && getSum(set) == sum) {
			allSets |= set;
		}
	}
	// known���� �̹� known�� ���� ���� ���� ��Ͽ��� �����Ѵ�.
	return allSets & ~known;
}

// �ڵ� 11.12 ī��ο��� �ĺ��� ���� �̸� ����ϴ� �˰���

// candidates[len][sum][known] = getCandidates(len,sum,known)
int candidates[10][46][1024];

// candidates[][][]�� �̸� ����� �д�.
void generateCandidates() {
	memset(candidates, 0, sizeof(candidates));
	// 1~9�� �κ������� ���� �����Ѵ�.
	for (int set = 0; set < 1024; set += 2) {
		// ������ ũ��� ������ ���� ����� �д�.
		int l = setSize(set), s = setSum(set);
		// set�� ��� �κ� ���տ� ���� candidates[][][]�� �����Ѵ�.
		int subset = set;
		while (true) {
			//���� �ϳ��� ���� s�̰�, �̹� subset ���ڰ� �������� ��
			//��ü ������ ������ set�� �ǵ��� ������ ���ڸ� ä������ �� �ִ�.
			candidates[l][s][subset] |= (set & ~subset);
			if (subset == 0) break;
			subset = (subset - 1) & set;
		}
			
	}
}

int main() {
	return 0;
}