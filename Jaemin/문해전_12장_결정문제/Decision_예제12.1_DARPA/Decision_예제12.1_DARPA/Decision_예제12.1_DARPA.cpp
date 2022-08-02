
// �ڵ� 12.1 DARPA�� ���� ���� ���¸� �ذ��ϴ� Ž���� �˰���

// ���� ���� : ���ĵǾ� �ִ� Locations �� cameras�� ������ ��� ī�޶� �� ������ gap �̻��� �Ǵ� ����� �ִ��� ��ȯ

#include <vector>
#include <iostream>
using namespace std;
bool decision(const vector<double>& location, int cameras, double gap) {
	// ī�޶� ��ġ�� �� ���� ������ ��ġ�ϴ� Ž���� �˰���
	double limit = -1;
	int installed = 0;
	for (int i = 0; i < location.size(); i++) {
		if (limit <= location[i]) {
			++installed;
			// location[i] + gap ���Ĵ� �Ǿ�� ī�޶� ��ġ�� �� �ִ�.
			limit = location[i] + gap;
		}
	}

	// ��������� Ž�������� ��ġ�� ī�޶� ���� ����ġ���� ������ true
	return installed >= cameras;
}

// ����ȭ ���� : ���ĵǾ� �ִ� locations �� cameras�� ������ �ּ� ������ �ִ�ȭ �Ѵ�.
double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	// �ݺ��� �Һ���: decision(lo)&&!decision(hi)
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2.0;
		//������ mid �̻��� �ǵ��� �� �� ������ ���� [mid,hi]�� �ִ�.
		if (decision(location, cameras, mid))
			lo = mid;
		//������ mid �̻��� �ǵ��� �� �� ������ ���� [lo,mid]�� �ִ�.
		else {
			hi = mid;
		}
		return lo;
	}
}