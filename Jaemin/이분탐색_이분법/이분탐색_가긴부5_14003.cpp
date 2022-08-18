/*
LIS 길이 출력하는 문제. 기존의 방식으로는 O(N^2)의 시간 복잡도였지만, 배열의 크기가 커서, O(NlogN)으로 길이를 구하고자 한다.
이 알고리즘은 LIS 길이를 적절히 구할 수는 있으나, 여기서 얻어진 배열이 실제 LIS 수열과는 일치하지 않음에 유의해야 한다.
기존의 점화식을 이용한 DP 풀이법과의 차이점은 앞에서 만들어 놓은 LIS의 길이를 본다는 점이다. 그것을 D[i]로 하여, 각 idx에서의 A[idx]를 넣을지 말지 선택할 때
기존에 만들어 놓은 D[i]에 붙였을 때 어느 정도의 길이를 갖게 만들 수 있는지를 계속 구해나갈 수 있다.
*/
/*
가긴부 3과의 차이점은 진짜 부분 수열까지 출력해야한다는 점.
D[i]를 도입하여, 기여할 수 있는 길이를 기록해 둠으로써, 나중에 역추적에 사용할 수 있다. 점화식 방법과는 방향성이 반대임을 알 수 있다. 내가 앞으로 선택할 것 vs 내가 추가되면 기존 것에 기여되는 것

참고 : https://yabmoons.tistory.com/561
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>


using namespace std;

int N;
int A[1000001];
// D[i]는 A[i]의 원소가 맨 뒤인 배열에서 가질 수 있는 LIS길이를 말한다. D[i]길이가 긴 순서대로 역추적하면, 배열을 얻어낼 수 있다.
int D[1000001]; 
vector<int> LIS;
vector<int> result;


// O(N)
void reconstruct(){
    int length = LIS.size();
    int idx = N;
    while(length != 0 && idx != 0){
        if(D[idx] == length){
            result.push_back(A[idx]);
            length--;
        }
        idx--;
    }
}
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
        if(LIS.size() == 0 || LIS.back() < A[idx]) {
            LIS.push_back(A[idx]); 
            D[idx] = LIS.size();
        }
        // A[idx]를 적절한 위치에 삽입한다고 생각함.
        else{
            auto it = lower_bound(LIS.begin(), LIS.end(), A[idx]);
            *it = A[idx];

            int length = it - LIS.begin() + 1;
            D[idx] = length;
        }
    }
    cout << LIS.size() << '\n';
    reconstruct();
    while(!result.empty()){
        cout << result.back() << " ";
        result.pop_back();
    }
    return 0;
}