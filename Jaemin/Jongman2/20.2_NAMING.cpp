#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 코드 20.4 KMP 알고리즘을 이용해 부분 일치 테이블 계산
vector<int> getPartialMatchKMP(const string& N){
    int m = N.size();
    vector<int> pi(m, 0);

    int begin = 1, matched = 0;    
    while(begin + matched < m){
        if(N[begin + matched] == N[matched]){
            matched++;
            // pi[i] : 0..i번째까지 matching 되었을 때, 접두사 = 접미사인 부분 문자열 최대 길이
            pi[begin + matched - 1] = matched;
                        
        }
        else{
            if(matched == 0){
                begin++;            
            }
            else{
                begin += matched - pi[matched - 1];
                matched = pi[matched - 1];
            }
        }
    }
    return pi;
}

// 코드 20.5 S의 접두사도 되고 접미사도 되는 모든 문자열의 길이를 계산하기
vector<int> getPrefixSuffix(const string& s){
    vector<int> ret, pi = getPartialMatchKMP(s);
    int k = s.size();
    while(k > 0){
        ret.push_back(k);
        k = pi[k-1];
    }
    return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string line1, line2;
     
    cin >> line1 >> line2;
    string s = line1 + line2;
    vector<int> outputs = getPrefixSuffix(s);
        
    for(auto it = outputs.rbegin() ; it != outputs.rend(); it++){        
        cout << *it << " ";
    }        
}