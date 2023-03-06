/*
최적화  버전
그냥 input 받는 족족 처리하는 것이 합리적임
그리고, queue에서 가지고 있는 숫자들을 관리하자
*/ 
#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
int K, N;
const int maxN = 50000000;
const long long MOD = pow(2,32);

// 참고. 난수생성기 Random Number Generator(RNG)
// 용법 : init -> RNG rng; 하나씩 뽑기 -> rng.next();
struct RNG{
    unsigned seed;
    RNG() : seed(1983) {}
    unsigned next(){
        unsigned ret = seed;
        seed = ((seed * 214013u) + 2531011u);
        return ret % 10000 + 1;
    }
};

queue<int> q;
int main(){    
    int C;
    cin >> C;

    for(int epoch = 0 ; epoch < C; epoch++){
        cin >> K >> N;

        // initialize
        while(!q.empty()) q.pop();
        
        int cnt = 0;
        int num = 0;
        long long a0 = 1983;
        // 총 N번의 q.push() 발생 후 종료
        for (int i = 0 ; i < N; i++){
            int x = a0%10000 + 1;
            a0 = (a0*214013 + 2531011) % MOD;

            // 항상 num < K인 상황에서 다음 x를 받도록 설계
            num += x;
            q.push(x);
            while(true){                
                if(num < K){                
                    break;
                }
                else if(num == K){
                    cnt ++;
                    num -= q.front(); q.pop();
                }
                else{
                    num -= q.front(); q.pop();
                }
            }                        
        }
        

        cout << cnt << '\n';        
    }
}