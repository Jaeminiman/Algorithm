/*
LIS 길이 출력하는 문제. 기존의 방식으로는 O(N^2)의 시간 복잡도였지만, 배열의 크기가 커서, O(NlogN)으로 길이를 구하고자 한다.
이 알고리즘은 LIS 길이를 적절히 구할 수는 있으나, 여기서 얻어진 배열이 실제 LIS 수열과는 일치하지 않음에 유의해야 한다.
기존의 점화식을 이용한 DP 풀이법과의 차이점은 앞에서 만들어 놓은 LIS의 길이를 본다는 점이다. 그것을 D[i]로 하여, 각 idx에서의 A[idx]를 넣을지 말지 선택할 때
기존에 만들어 놓은 D[i]에 붙였을 때 어느 정도의 길이를 갖게 만들 수 있는지를 계속 구해나갈 수 있다.
*/

/*
실수 포인트 1. Arr[1]을 Arr[2]와 동일 처리를 하기 위해 Arr[0]를 비워두고 시작하는 Tool을 이용하는데, Arr에 들어올 수 있는 값이 음수도 가능하여, A[0] = 0으로 임의로 박고
시작했을 때, 0이 무의미한 숫자가 아닌 경우가 있을 수 있어 오답이 나왔다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N;
int A[1000001];
vector<int> LIS;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;

    for(int i = 1; i <= N; i++){
        cin >> A[i];
    }

    for(int idx = 1; idx <= N ; idx++){
        // LIS에 원소가 없거나, LIS의 맨 뒤 값보다 넣으려는 A[idx]가 큰 경우에는 무조건 넣어버림.
        if(LIS.size() == 0 || LIS.back() < A[idx]) LIS.push_back(A[idx]);
        // A[idx]를 적절한 위치에 삽입한다고 생각함.
        else{
            auto it = lower_bound(LIS.begin(), LIS.end(), A[idx]);
            *it = A[idx];
        }
    }
    cout << LIS.size() << '\n';
    return 0;
}