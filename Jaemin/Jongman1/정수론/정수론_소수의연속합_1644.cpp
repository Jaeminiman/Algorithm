// 다른 사람의 풀이
// 부분합으로 정의되는 p_sum 배열을 할당하여 미리 부분합을 계산해둔다.
// 각 구간의 합은 p_sum[a] - p_sum[b]로 하여, b ~ a 구간의 부분합을 구한다.
// pointer 두 개를 운용하여 부분합을 구하는 알고리즘 구현할 수 있다.

#include <iostream>
#include <cstring>
#include <math.h>
#include <vector>
using namespace std;
int N;
bool isPrime[4000001];
int cnt = 0;
vector<int> prime;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    memset(isPrime,true,sizeof(isPrime));
    // 예외 처리
    isPrime[0] = isPrime[1] = false;

    // 에라토스테네스의 체
    int sqrtn = int(sqrt(N));
    for(int j = 2; j <= sqrtn; j++){
        if(isPrime[j]){
            for(int i = j * j ; i <= N; i = i + j){
                isPrime[i] = false;
            }
        }
    }
    for(int j = 2; j <= N; j++){
        if(isPrime[j]){
            prime.push_back(j);
        }
    }

    // 초기 Block 세팅
    int sum = 0;
    int startPointer = 0;
    int endPointer = prime.size();
    for(int i = 0; i < prime.size(); i ++){
        sum += prime[i];
        if(sum > N){
            // N을 넘기면 넘기기 바로 직전으로 돌아가 밑에서 상황에 일관되게 적용하게 한다.
            sum -= prime[i];
            endPointer = i;
            break;
        } 
    }

    // startPointer : Block의 맨 앞 원소
    // endPointer : Block의 맨 뒤 원소의 하나 뒤
    // pointer가 두 개 처음부터 끝까지 이동하는 것이므로 시간 복잡도 : O(N)
    while(true){
        if(sum == N){
            cnt++;
        }
        // 기저 사례 : endPointer가 Null을 가리킴(종료)
        if(endPointer == prime.size()){
            break;
        }

        sum += prime[endPointer++];

        while(true){
            // 기저 사례 : Sum이 N보다 작거나 같은 경우(startPointer 이동 종료)
            if(sum <= N){
                break;
            }
            sum -= prime[startPointer++];
        }
    }
    

    cout << cnt << '\n';
    return 0;
}