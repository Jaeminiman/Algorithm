/*
질문1. 시간복잡도 O(N + K)
질문2. 시간복잡도 O(N^2) -> 개선 여지? nextIdx를 구하는 작업(O(n)을 상수시간에 가능..?
기존 : 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int C;
int N, K;
const int MAX_N = 100000, MAX_K = 100000;
const int p = 20091101;
int psum[MAX_N + 1];
int prv[MAX_K]; // prv[k] : 나머지가 k인 바로 직전의 상자 번호
int DP[MAX_N + 1];

// 2번째 질문을 위한 재귀함수
// Bottom-UP으로 바꾸고 -> 전체 시간복잡도 : O(N)
int order(){    
    prv[0] = 0;
    DP[0] = 0;
    for(int idx = 1; idx <= N; idx++){
        // idx을 넣지 않은 경우
        DP[idx] = DP[idx - 1];
        
        // 이전에 본게 있으면 넣을 수 있음
        if(prv[psum[idx]] != -1){
            DP[idx] = max(DP[prv[psum[idx]]] + 1 , DP[idx - 1]);        
        }
        prv[psum[idx]] = idx;        
    }        

    return DP[N];
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){        
        cin >> N >> K;
        memset(DP, 0, sizeof(DP));        
        memset(prv, -1, sizeof(prv));
        // Trick : psum[0]는 아무것도 포함 안한 것으로 시작하면 편리하다 (idx를 1부터 N까지 부여한다)
        // O(N)
        psum[0] = 0;
        for(int i = 1; i <=N; i++){
            int x;
            cin >> x;                                                
            psum[i] = (psum[i-1] + x)%K;                            
        }                

        // O(N)
        // fj : K로 나눈 나머지가 j인 박스의 빈도수        
        vector<long long> fj(K, 0);
        for(int i = 0; i <= N; i++){            
            fj[psum[i]]++;            
        }

        // O(K)
        int sum = 0;
        for(int j=0; j<K; j++){
            sum = (sum + (fj[j] * (fj[j] - 1) / 2))%p;
        }

        
        int result = order();
        cout << sum << " " << result << "\n";
    }
    
}