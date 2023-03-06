/*
메모이제이션은 사용하지 않았다. 문제에서 유의해야할 점은 연산자 "-"기호가 전체에 대해 음으로 분배법칙이 성립하지 않는다는 점이다.
덩어리 지어서 생각해보면, n번째 세대 = (n-1) + (n-2) - (n-3) - (n-4) - ... -(0)
정의하기를 generation이 1일 때는, 기본적으로 FX + YF라고 생각하고 이를 따로 컨테이너에 보관해서 꺼내쓴다.
generation이 0일 때는, 약간의 예외처리처럼 1,2 idx는 정의되지만 그 이상 넘어가는 경우에는 무조건 -YF 부분인 것이므로 그것또한 0세대로 정의한다.
결국 이 두개 케이스를 기저사례로 삼아 재귀함수를 수행한다.

나의 풀이와 책의 풀이의 차이점은 나는 0부터해서 n번째까지 그 변화를 통해 n번째 점화식을 세운후,
찾고자하는 idx를 기준으로 n'th genetation에서 0번 혹은 1번 generation에 닿을 때까지 줄여나가는 식으로 수행했다.
그러나 첵은 반대로 Seed부터 만들어나가는 식으로 n번째까지 구성해서 답을 낸다.
*/
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
int C;
string baseStage[2] = {" FX+YF" , " FX-YF"};

char dragon(int stage, int start){
    // 기저사례 : stage = 0
    if(stage == 0){
        return baseStage[1][start];
    }
    // 기저사례 : stage = 1
    if(stage == 1){
        return baseStage[0][start];
    } 

    int tmp = stage - 1;
    long long next = start;
    int cnt = 0;
    while(3 * pow(2,tmp) - 1 < next && tmp != 0){
        next = next - (3 * pow(2,tmp) - 1);
        tmp--;
        cnt++;

        // 예외 처리. 중간에 걸치는 경우
        if(next != 1) next = next - 1;
        // '+' 나 '-' 위치에 걸친 경우
        else{
            return (cnt>=2) ? '-' : '+';
        }
    }

    return dragon(tmp, next);
}
int main(){
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){
        int n, p, l;
        cin >> n >> p >> l;
        vector<char> v;
        for(int idx = p ; idx < p + l; idx++){
            v.push_back(dragon(n,idx));
            cout << dragon(n,idx);
        }
        cout << '\n';
        
    }
    return 0;
}