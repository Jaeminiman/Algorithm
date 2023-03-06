/*
입력을 배열로 받아서 같은 것을 포함한 순열 개수 만큼의 부분문제를 만들 수 있다.
가능한 모든 조합에 대해서 다 해보려면 최대 14!의 경우를 다 따져봐야해 시간초과다.
아니지.. [0,9]입력으로 제한되니까 O(14!/(2! 2! 2! 2!))정도면 다 돌아볼 수 있겠다.
대략 O(10^10) => Time over.

int toVisit[10] 배열로 [0,9]에 받아야 할 개수를 센다.
int visited[10] 배열로 지금까지 쓴 숫자들을 기록한다.

위의 방식으로 했을 때는 부분 문제가 겹치는 바가 없어서 메모이제이션이 불가능했다.
부분 문제 수를 최대한 줄이기 위해 visited를 살펴보면, visited를 사용하는 경우는
크게 다음과 같이 3가지 경우였다. 사실 cnt 또한 visited를 통해 유추할 수 있던거라 무시한다.
1) 기저 사례로 종료 조건(다 만들었는지)를 판단할 때
2) stirng e보다 작은 수 인지 판단할 때
3) 다 만들고 나서 m의 배수인지 판단할 때

1)은 사실 toVisit현황만 보면 해결할 수 있는 문제이고 cnt로 관리할 수 있다.

2)는 앞에서부터 한 문자씩 비교로 부분 문제로 바꿀 수 있는데 다음과 같다.
case 1. 같은 경우 : 다음 선택에 있어서 작거나 같은 것을 골라야 한다.
case 2. 작은 경우 : 다음 선택에 있어서 고려할 것이 없다.
따라서 이것을 bool less로 정의한다.

3)는 나눗셈을 하는 과정을 떠올렸을 때 앞의 숫자 구성을 m으로 나눈 나머지만 알면 m의 배수인지 판단하는데 무리가 없다.
따라서 앞의 숫자들을 m으로 나눈 나머지를 누적합해서 m으로 나눈 값을 반환한다. 이는 [0, m-1]범위의 숫자로 현 입력에서 보았을 때 최대 20가지다.
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
string e, sorted; 
int m;
const int P = 1000000007;
long long cache[2][20][1<<14];
// cnt만 넘기면 안되는게 내부에서 toVisit[]을 판단에 이용하기 때문에 이 또한 인자로 생각해줘야 했다.
// 따라서 taken[14]를 따로 두면, 순서는 중요치 않으니 2^15= 16 * 10^3이라 cover가능한 수준이다.
// mod와 string e와의 비교 계산을 위해 순서가 필요했던 것을 다른 식으로 해소했기에, 순서에 대한 고려가 없어져 부분문제가 확 줄었다.
long long combinations(int cnt, bool less, int div, int taken){
    // 기저 사례 : 모든 숫자를 다 썼을 때
    if(cnt == e.size()){
        // 성공
        if(div == 0 && less){
            return 1;
        }
        else{
            return 0;
        }
    }

    // cnt는 taken과의 중복된 정보이므로 cache구성에 넣지 않음
    long long& ret = cache[less][div][taken];
    if(ret != -1) return ret;


    ret = 0;
    for(int next = 0; next < e.size(); next++){
        // 이미 선택 되었던 경우
        if((taken & 1<<next) != 0) continue;
        
        if(next == 0 || sorted[next - 1] != sorted[next] || (taken & (1 << (next -1))) != 0){
            bool nextLess = true;
            int nextDiv = (div * 10 + sorted[next] - '0') % m;
            int nextTaken = taken + (1 << next);
            
            // 작거나 같은 수를 뽑아야하는 경우(0~cnt까지 e와 내가만든 수가 같은 경우) 
            if(!less){
                if(e[cnt] < sorted[next]) continue;
                else if(e[cnt] == sorted[next]) nextLess = false;
            }
            ret += combinations(cnt+1, nextLess, nextDiv, nextTaken);
            ret %= P;
        }
    
    }
    return ret;
}
void start(){
    memset(cache,-1,sizeof(cache));
    cin >> e >> m;
    sorted = e;
    sort(sorted.begin(), sorted.end());
}
int main(){
    int C;
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){
        start();
        cout << combinations(0,false,0,0) << '\n';
    }
    return 0;
}