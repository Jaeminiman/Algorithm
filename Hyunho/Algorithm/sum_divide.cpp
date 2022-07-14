#include <iostream>

using namespace std;

int N, K;
long long int dp[201][201]; //dp 앞: 개수 뒤: 합

void sum(){
    for(int i=0;i<=K;i++){
        dp[i][0] = 1;
    }

    for(int i=1;i<=K;i++){
        for(int j=1;j<=N;j++){
            for(int k=0;k<=j;k++){
                dp[i][j] += dp[i-1][k];
            }
            dp[i][j]%=1000000000;
        }
    }
}

int main(){
    cin >> N >> K;
    sum();
    cout << dp[K][N] << endl;
}