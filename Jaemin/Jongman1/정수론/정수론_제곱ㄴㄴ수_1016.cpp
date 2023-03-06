/*
10^12의 숫자를 루트 씌어서 그냥 다 순회하면서 제곱수인지 확인한다고 했을 때, 10^6번 순회하는 로직이다. 매번 모든 숫자에 대해 제곱수인지 확인 절차를 거치기 어려우므로
Dynamic Programming으로 isSqaure[100001] = (false)로 선언하여 MIN ~ MAX 범위의 숫자들에 대해 제곱수인지를 판단해 준다.
그 방식은 에라토스테네스의 체 방식에 착안하여, 제곱수를 하나 놓고 그 배수에 해당되는 idx를 모두 true로 바꾸는 식으로 채워나간다.

주의 사항 : int형인 i * i를 하게되면 일단 int 형으로 저장하여 값을 입력하므로 정수 자료형을 
넘어설 경우 (long long)으로 타입 캐스팅을 해줘야 한다.

시간 개선 사항 : j = 2*2부터 시작할 경우, 시간 복잡도가 O(N^2)이 될 수 있다.
그러나, 이렇게 square * (MIN / square)로 초기값을 잡으면 MIN보다 작거나 같은 수 중 square의 배수의 최대값을 얻을 수 있다.
square로 나누어 떨어지는 수 중에 MIN과 가장 가까운 수를 얻어내는 기술이다.

*/

#include <iostream>
#include <math.h>
#include <cstring>
using namespace std;
long long MIN, MAX;
bool isSquare[1000001];

int main(){
    cin >> MIN >> MAX;
    memset(isSquare, false, sizeof(isSquare));
    int sqrtMIN = int(sqrt(MIN));
    int sqrtMAX = int(sqrt(MAX));
    for(int i = 2; i <= sqrtMAX; i++){
        // 주의 사항 : int형인 i * i를 하게되면 일단 int 형으로 저장하여 값을 입력하므로 정수 자료형을 넘어설 경우
        // (long long)으로 타입 캐스팅을 해줘야 한다.
        long long square = (long long) i * i;

        // 시간 개선 사항 : j = 2*2부터 시작할 경우, 시간 복잡도가 O(N^2)이 될 수 있다.
        // 그러나, 이렇게 square * (MIN / square)로 초기값을 잡으면 MIN보다 작거나 같은 수 중 square의 배수의 최대값을 얻을 수 있다.
        // square로 나누어 떨어지는 수 중에 MIN과 가장 가까운 수를 얻어내는 기술이다.
        for(long long j = square*(MIN/square) ; j <= MAX; j += square){
            if(j < MIN) continue;
            
            int idx = j - MIN;
            isSquare[idx] = true;
            
        }     
    }
    int cnt = 0;
    for(int i = 0; i <= (MAX - MIN); i++){
        if(!isSquare[i]){
            cnt++;
        }
    }

    cout << cnt << '\n';
    return 0;
}
