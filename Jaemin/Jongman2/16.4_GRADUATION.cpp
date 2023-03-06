#include <iostream>
#include <math.h>
#include <string>
#include <cstring>
using namespace std;
int M, N, K, L;
int C;
int require[12];
int openCourse[10];
int DP[(1<<12)][10];
const int INF = 123456789;
/*
주의할 점
Greedy하게 그냥 무조건 수강할 수 있으면 하는게 이득이라고 생각햇는데, 안들으면 학기수 + 1을 안하기 때문에
들을 수 있어도 아예 안듣는 선택을 하는게 이득일 수 도 있다 => canTake == 0 만이 넘어가는 기준이 되지 못하므로, 그냥 전체 순회하는게 편할 것임
*/
// bitmask의 집합의 원소 수 세는 함수
int bitmaskLength(int mask){
    if(mask == 0){
        return 0;
    }
    else{        
        return mask%2 + bitmaskLength(mask / 2);
    }
}

// stage는 0부터 시작한다. 즉, 지금까지 경험한 학기 수로 정의됨
// sugang : 지금까지 수강한 수업 (in bitmask 집합)
int sugangCheck(int sugang, int stage){
    // base case1 (성공)
    if(bitmaskLength(sugang) >= K){
        return 0;
    }
    // base case2 (실패)
    if(stage == M){
        return INF;
    }
    int& ret = DP[sugang][stage];
    if(ret != -1) return ret;
    
    
    ret = INF;    
    int canTake = 0;
    for(int i = 0; i < N; i++){        
        // (요건이 채워짐 -> 이게 문제였는듯..)&&(수강 안했던 것임)&&(이번 학기에 열림)
        if(((sugang | require[i]) == ((1<<N) - 1)) && ((sugang & (1<<i)) == 0) && ((openCourse[stage] & (1<<i)) != 0)){
            canTake |= (1<<i);
        }
    }
    // int canTake = (openCourse[stage] & ~sugang);
    // for(int i =0; i<N;i++){
    //     if((canTake & (1<<i)) != 0){
    //         if((require[i] & sugang) != require[i]){
    //             canTake &= ~(1<<i);
    //         }
    //     }
    // }

    // subset == 공집합 일때는 코드 수행 x, 즉 하나도 수강안하는 경우는 고려되지 않음
    for(int subset = canTake ; subset; subset = ((subset - 1) & canTake)){
        if(bitmaskLength(subset) <= L){                
            ret = min(ret, sugangCheck(sugang | subset, stage + 1) + 1);
        }
    }        
    
    // 공집합에 대한 고려
    ret = min(ret, sugangCheck(sugang,stage + 1));
    
    return ret;



}
int main(){

    cin >> C;
    for(int epoch = 0 ; epoch < C; epoch++){
        cin >> N >> K >> M >> L;
        memset(DP, -1, sizeof(DP));
        for(int course = 0; course < N; course++){
            int p;
            cin >> p;
            require[course] = (1 << N) - 1;
            
            for(int i = 0; i < p; i++){
                int x;
                cin >> x;
                require[course] &= ~(1<<x);
            }            
        }
        for(int semester = 0; semester < M; semester++){
            int p;
            cin >> p;
            openCourse[semester] = 0;

            for(int i = 0; i < p; i++){
                int x;
                cin >> x;
                openCourse[semester] |= (1<<x);
            }
        }
        string result;
        int output = sugangCheck(0,0);
        if(output >= INF){
            result = "IMPOSSIBLE";
        }
        else{
            result = to_string(output);
        }         

        cout << result << '\n';        
    }
}
