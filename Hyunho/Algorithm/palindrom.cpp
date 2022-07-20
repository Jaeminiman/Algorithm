#include <iostream>

using namespace std;

bool dp[2001][2001] = {false,};
int arr[2001];
int N, M;

void pal(){
    for(int i=1;i<=N;i++){
        dp[i][i] = true; // 확인하려는 개수가 홀수 일 때
        if(arr[i] == arr[i+1] && i != 2000){
            dp[i][i+1] = true;
        } // 확인하려는 개수가 짝수 일 때
    } // 차이가 1나는 것 모두 계산 완료

    for(int i=N-2;i>=1;i--){ // 차이가 2~N-1나는 것 계산
        for(int j=i+2;j<=N;j++){
            if(arr[i] == arr[j] && dp[i+1][j-1] == true) dp[i][j] = true;
        }
    }
}

int main(){
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
    cin >> N;
    for(int i=1;i<=N;i++){
        cin >> arr[i];
    }
    pal();
    cin >> M;
    for(int i=0;i<M;i++){
        int S, E;
        cin >> S >> E;
        cout << dp[S][E] << '\n';
    }
}