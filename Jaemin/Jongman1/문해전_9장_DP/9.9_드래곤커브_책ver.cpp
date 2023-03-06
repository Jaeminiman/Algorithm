/*
- 동적 계획법이 쓰인 부분
p번째 글자를 출력하려면 앞에서부터 몇 번의 출력이 있었는지를 세야하는데 Seed가 한정적으로 주어진 상황에서
매 generation마다 개수를 세는 것은 시간 낭비가 크다. 그래서 이를 동적계획법으로 미리 계산하여 최적화한다.

length(n) = length(n-1) * 2 + 2; // 2배는 X, Y가 두개라서, +2는 {+, -}연산자와 한 개의 F 때문
*/
#include <iostream>
#include <math.h>
#include <cassert>

using namespace std;


// Tip : 2^50은 나타내기 어렵지만, 나올 수 있는 idx가 10^9 + 50까지 이므로
// MAX로서 이렇게 설정해놓고 넘어가는 것에 대해서는 그냥 MAX로 박아두면 longlong 쓰지 않아도 OK
const int MAX = 1000000000 + 51; 
int curveLength[51]; // 일종의 Length DP
int N,l,p;

// 정의 : seed를 generations세대 진화한 문자열에서 skip번째 문자 반환 함수
char curve(const string& seed, int generations, int skip){
    // 기저 사례 : generations = 0
    if(generations == 0){
        // Tip : assert를 통해 꼭 입력되어야하는 값에 대한 디버그 검증을 할 수 있다.
        assert(skip < seed.size());
        return seed[skip];
    }

    for(int i = 0; i <seed.size(); i++){
        if(seed[i] == 'X' || seed[i] == 'Y'){
            if(skip < curveLength[generations]){
                if(seed[i] == 'X'){
                    return curve("X+YF", generations - 1, skip);
                }
                else if(seed[i] == 'Y'){
                    return curve("FX-Y", generations - 1, skip);
                }
            }
            else{
                skip -= curveLength[generations];
            }      
        }
        else if(skip>0){
            skip -= 1;
        }
        else {
            return seed[i];
        } 
    }

    return '#';
}

// DP
void precalc(){
    curveLength[0] = 1;
    for(int i = 1; i < 51; i++){
        curveLength[i] = min(curveLength[i-1] * 2 + 2, MAX);
    }
}
int main(){
    int C;
    
    cin >> C;

    precalc();

    for(int epoch = 0; epoch < C; epoch++){
        cin >> N >> p >> l;
        for(int idx = p; idx < p + l; idx++){
            cout << curve("FX", N, idx - 1);
        }
        cout << '\n';
    }
    
    
    return 0;
}