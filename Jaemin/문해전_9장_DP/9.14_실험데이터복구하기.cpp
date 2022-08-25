#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
int k;
vector<string> S;
int DP[1<<15][16];
const int INF = 987654321;
string output;

// here과 next를 합치는 문자열 반환하고, 실제 return은 here이 next를 포함여부 반환
bool overlapCalc(int here, int next, string& str){

    string left = S[here];
    string right = S[next];
    bool overlap = true;

    int l = 0; int r = 0;
    while(r != right.size() && l != left.size()){
        str.push_back(left[l]);
        
        if(left[l] == right[r]){
            l++; r++;
        }
        else{
            l++; r = 0;
        }
    }
    // l이 다 찬 경우 : 포함 관계가 아님
    while(r != right.size()){
        overlap = false;
        str.push_back(right[r++]);
    }

    // r이 다 찬 경우 : 포함 관계임
    while(l != left.size()){
        str.push_back(left[l++]);
    }

    return overlap;
}
// taken을 사용한 상태에서, here을 맨 앞으로 하여 남은 문자열로 만들 수 있는 here길이를 제외한 최소의 길이 반환
int restore(int cnt, int taken, int here){
    // 기저 사례: 모든 문자열을 다 사용하여 조합을 완성한 경우
    if(cnt == k){
        return 0;
    }

 
    int& ret = DP[taken][here];
    if(ret != -1) return ret;

    int minCand = INF;
    for(int next = 1; next <= k; next++){
        // 이미 전에 선택된 경우 -> 넘어감
        if((taken & (1<<(next - 1))) != 0) continue;

        int nextTaken = taken + (1<<(next - 1));

        int cand; string str;
        bool overlap = true;
        
        // here이 next를 포함하는 경우
        if(overlapCalc(here,next,str)){
             cand = restore(cnt + 1, nextTaken, here);
        }
        else{
            cand = str.size() - S[here].size() + restore(cnt + 1, nextTaken, next);
            overlap = false;
        }
       
        if(cand < minCand){
            minCand = cand;
            // here에 겹치지 않는 next부분 반환
            if(!overlap){
                for(int i = str.size() - 1; i >= S[here].size() ; i--){
                    output.push_back(str[i]);
                }                
            }   
        }
    }
    return ret = minCand;
}
int main(){
    int C;
    cin >> C;
    for(int epoch = 0 ; epoch < C; epoch++){
        memset(DP, -1, sizeof(DP));
        cin >> k;
        S.clear(); S.resize(k);
        output.clear();
        // 시작 처리를 위해 idx 0을 공란으로 처리.
        S[0] = "";
        for(int i = 1; i <= k; i++){
            cin >> S[i];
        }
        restore(0,0,0);
        cout << output << '\n';
    }
}