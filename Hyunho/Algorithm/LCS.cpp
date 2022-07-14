#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string A, B;
int dp[1001][1001];

void LCS(int A_size, int B_size){
    for(int i=1;i<=A_size;i++){
        for(int j=1;j<=B_size;j++){
            if(A[i-1] == B[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1; 
            }
            else if(A[i-1] != B[j-1]){
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
}

int main(){
    cin >> A >> B;
    int A_size = A.length();
    int B_size = B.length();
    LCS(A_size, B_size);
    cout << dp[A_size][B_size] << endl; 
}