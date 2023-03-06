/*
최적화 이전 버전 -> 이렇게 해서는 Memory가 A[]받는데만 400MB 소모.
그냥 input 받는 족족 처리하는 것이 합리적임
*/
#include <iostream>
#include <math.h>
using namespace std;
int K, N;
const int maxN = 50000000;
const long long MOD = pow(2,32);

long long A[maxN + 1];

int main(){
    
    // cf) A[maxN]은 필요없는 값
    A[0] = 1983;
    for(int i = 1; i <= maxN; i++){
        A[i] = (A[i-1]*214013 + 2531011) % MOD;
        A[i-1] = A[i-1]%10000 + 1;
    }    
     
    int C;
    cin >> C;
    for(int epoch = 0 ; epoch < C; epoch++){
        cin >> K >> N;

        int cnt = 0;
        int num = 0;
        int lo = -1, hi = -1;
        while(hi != N){
            if(num < K){                
                num += A[++hi];
            }
            else if(num == K){
                cnt++;
                num -= A[++lo];                
            }
            else{
                num -= A[++lo];
            }            
        }
        cout << cnt << '\n';
    }
}