#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int dp[100001];
vector <int> a;
int n, k;

void coin(){
    for(int i=0;i<a.size();i++){
        dp[a[i]] = 1;
    }
    for(int i=0;i<=k;i++){
        for(int j=0;j<a.size();j++){
            if(i-a[j] <= 0) break;
            else if(dp[i-a[j]] == 10001) continue;
            else {
                dp[i] = min(dp[i], dp[i-a[j]] + 1);
            }
        }
    }
    return;
}

int main(){
    cin >> n >> k;
    for(int i=0;i<=k;i++){
        dp[i] = 10001;
    }
    int value;
    for(int i=0;i<n;i++){
        cin >> value;
        a.push_back(value);
        for(int j=0;j<a.size()-1;j++){
            if(value != a[j]) continue;
            else if(value == a[j]) {
                a.pop_back();
                break;
            }
        }
    }
    sort(a.begin(), a.end()); 
    coin();
    for(int i=0;i<=k;i++) {
        if(dp[i] == 10001) dp[i] = -1;
    }
    cout << dp[k] << endl;
}