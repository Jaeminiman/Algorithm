#include <iostream>

using namespace std;

int dp[31];  
int N;

void tile_number(){
    dp[0] = 1, dp[2] = 3;
    for(int i=0;i<=N;i++){
        if(i % 2 == 1) dp[i] = 0;
    }
    for(int i=4;i<=N;i+=2){
        dp[i] = dp[i-2] * dp[2];
        for(int j=0;j<=i-4;j+=2){
            dp[i] += 2 * dp[j];
        }
    } 
}

int main(){
    cin >> N;
    tile_number();
    cout << dp[N] << endl; 
}