#include <iostream>
#include <vector>
#include <map>
#include <math.h>

using namespace std;
int n, hi, lo;
const int TM = 10000000;
int minFactor[TM+1]; // minFactor[i] = i의 가장 작은 소인수 ( i가 소수인 경우, 자기 자신임)
int minFactorPower[TM+1]; // i의 소인수분해에는 minFactor[i]의 몇 승이 포함되어있는가?
int factors[TM+1]; // factors[i] = i가 가진 약수의 수
struct Factor{
    int n, cnt; 
};

void getFactorsSmart(){
    factors[0] = 0;
    factors[1] = 1;
    for(int i = 2; i <= TM ; i++){
        // 소수인 경우
        if(minFactor[i] == i){
            minFactorPower[i] = 1;
            factors[i] = 2;
        }
        // 소수가 아닌 경우
        else{
            int p = minFactor[i]; // p는 i의 가장 작은 소인수
            int m = i / p;
            // p가 더 이상 소인수가 아님
            if(minFactor[m] != p){
                minFactorPower[i] = 1;
            }
            else{
                minFactorPower[i] = minFactorPower[m] + 1;
            }
            int a = minFactorPower[i];
            factors[i] = (factors[m] * (a + 1))/a;
        }
    }
}
// int factor(int n){
//     map<int,int> ret;
//     while(n > 1){
//         auto it = ret.find(minFactor[n]);
//         if( it == ret.end()){
//             ret.insert({minFactor[n], 1});
//         }
//         else{
//             it->second += 1;
//         }
//         n /= minFactor[n];
//     }
//     int num = 1;
//     for(auto it = ret.begin(); it!= ret.end(); it++){
//         int cnt = it->second;
//         num *= (cnt + 1);
//     }
//     return num;
// }
void eratostenes(){
    // 1은 예외처리
    minFactor[0] = minFactor[1] = -1;

    // 일단 소수로 모든 수 초기화 세팅
    for(int i = 2; i <= 10000000; i ++){
        minFactor[i] = i;
    }
    int sqrtn = int(sqrt(10000000));
    for(int i = 2; i < sqrtn; i++){
        // i가 소수이면
        if(minFactor[i] == i) {
            for(int j = i*i ; j <= 10000000; j = j + i){
                // j를 이전에 방문한 적이 없으면 i가 소인수 중 최소값
                if(minFactor[j] == j){
                    minFactor[j] = i;
                }
            }
        }
    }
}
int main(){
    int C;
    cin >> C;
    eratostenes();
    getFactorsSmart();
    for( int epoch = 0 ; epoch < C; epoch++){
        cin >> n >> lo >> hi;
        int cnt = 0;
        for(int it = lo; it <= hi; it++){
            if(factors[it] == n){
                cnt++;
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}

// 번외
// BruteForce하게 약수 개수 구하기
void getFactorsBrute(){
    memset(factors, 0, sizeof(factors));
    for(int div = 1; div <= TM; ++div){
        for(int multiple = div; multiple <= TM; multiple += div){
            factors[multiple]+=1;
        }
    }
}