#include <iostream>
#include <algorithm>

using namespace std;
int n, k;
int weight[101], value[101], dp[101][100001];

void bag(){
    for(int j=1;j<=k;j++){
        for(int i=1;i<=n;i++){
            if(j < weight[i]){
                dp[i][j] = dp[i-1][j];
            }
            else {
                dp[i][j] = max(dp[i-1][j-weight[i]] + value[i], dp[i-1][j]);
            }
        }
    }
}

int main(){
    int w, v;
    // for(int i=0;i<=n;i++) dp[i][0] = 0;
    // for(int i=0;i<=k;i++) dp[0][i] = 0;
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> w >> v;
        weight[i] = w, value[i] = v; 
    }
    bag();
    cout << dp[n][k] << endl;
}