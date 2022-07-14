#include <iostream>

using namespace std;
int type, price;
int dp[10001], a[100]; // dp는 price를 만들 수 있는 경우의 수, a는 동전의 종류를 저장한 배열

void coin(){
    dp[0] = 1;
    for(int i=0;i<type;i++){
        for(int j=a[i];j<=price;j++){
            dp[j] += dp[j-a[i]];
        }
    }
}

int main(){
    cin >> type >> price;
    int value;
    for(int i = 0;i<type;i++){
        cin >> value;
        a[i] = value;
    }
    coin();
    cout << dp[price] << endl;
}