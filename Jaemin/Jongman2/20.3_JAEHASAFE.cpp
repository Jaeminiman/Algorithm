#include <iostream>
#include <string>
#include <vector>
using namespace std;
int N;

vector<int> getPartialMatchKMP(const string& N){
    int m = N.size();
    vector<int> pi(m,0);

    int matched = 0, begin = 1;
    while(begin + matched < m){
        if(N[begin+matched] == N[matched]){
            matched++;
            pi[begin+matched-1] = matched;                
        }
        else{
            if(matched == 0){
                begin++;
                continue;
            }
            begin += matched - pi[matched - 1];
            matched = pi[matched - 1];
        }
    }

    return pi;
}
vector<int> kmpSearch(const string& H, const string& N){
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getPartialMatchKMP(N);

    int matched = 0, begin = 0;
    while(begin + m <= n){
        if(matched < m && H[begin + matched] == N[matched]){
            matched++;
            if(matched == m){
                ret.push_back(begin);                
            }
        }
        else{
            if(matched == 0){
                begin++;
                continue;                
            }
            begin += matched - pi[matched -1];
            matched = pi[matched - 1];
        }
    }
    return ret;
}

// a : 전체 문자열, b : 패턴
int shift(const string& a, const string& b){
    return kmpSearch(a + a,b)[0];
}

int main(){
    int C;
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){
        cin >> N;
        string x1;
        cin >> x1;
        
        int sum = 0;
        for(int i = 0; i < N; i++){
            string x2;
            cin >> x2;
            
            // 시계 방향
            if(i%2 == 0){
                sum += shift(x2,x1);
            }
            // 반시계 방향
            else{
                sum += shift(x1,x2);
            }            
            x1 = x2;
        }
        cout << sum << '\n';
    }
    
}