#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector <pair <int, int>> w;
int dp[101], wire;

int wiring(){
    int result = 0;
    for(int i=1;i<=wire;i++){ // lcs 구하는 문제와 동일해진다.
        for(int j=0;j<i;j++){
            if(w[i].second > w[j].second){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        result = max(dp[i], result);
    }
    return  wire-result;
}

int main(){
    cin >> wire;
    w.push_back({0,0});
    for(int i=0;i<wire;i++){
        int a, b;
        cin >> a >> b;
        w.push_back({a,b});
    }
    sort(w.begin(), w.end());
    cout << wiring() << endl;    
}