#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Comparator{
    const vector<int>& group; // 이거에서 const & 안하고 그냥 vector<int> group으로 선언하면, 시간초과남. 그 이유는 Comparator 객체를 하나의 메모리공간에 저장 vs. 여러 메모리 참조를 거쳐서 저장 차이로, 아마 엄청난 overhead가 발생하는듯..?
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator() (int a, int b){
        // case1. 처음 t개 문자가 다른 경우
        if(group[a]!=group[b]) return group[a] < group[b];
        // case2. 처음 t개 문자가 같은 경우 -> 다음 t개로 비교
        return group[a+t] < group[b+t];
    }
};

// 접미사 배열 계산(맨버 알고리즘, 처음 t개로 grouping) -> O(nlog^2(n))
vector<int> getSuffixArray(const string& s){
    int n = s.size();    
    
    int t = 1;
    vector<int> group(n+1); // group[i] : s[i..]의 첫 t글자의 사전순 배열에서의 그룹 번호    
    for(int i = 0; i<n; i++){
        group[i] = s[i];
    }
    group[n] = -1; // 길이가 0인 접미사를 맨 앞으로 빼기 위함

    vector<int> perm(n);
    for(int i = 0; i < n; i++) perm[i] = i;
    
    while(t < n){
        Comparator compareUsing2T(group, t);        
        sort(perm.begin(), perm.end(), compareUsing2T);
        
        t *= 2;
        if(t >= n) break;
        // 첫 2t글자를 기준으로 배열한 새로운 group
        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i = 1; i < n; i++){
            if(compareUsing2T(perm[i-1], perm[i])){
                newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
            }
            else{
                newGroup[perm[i]] = newGroup[perm[i-1]];
            }
        }
        group = newGroup;
    }
    return perm;
}

// 접미사 배열 상 인접하는 두 접미사 s[i..]와 s[j..]의 공통 접두사(공통 부분문자열)의 최대길이 계산
int commonPrefix(const string& s,int i, int j){
    int cnt = 0;
    while(i < s.size() && j < s.size() && s[i] == s[j]){
        i++, j++, cnt++; 
    }
    return cnt;
}
/*
전체 시간 복잡도 : O(n^2) dominant in 88번줄 for문
*/
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int C;
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){
        string s; int K;
        cin >> K >> s;

        vector<int> a = getSuffixArray(s); // 시간 복잡도 : O(nlog^2(n))

        // 접미사 배열 a[]에서 인접한 접미사는 공통의 접두사를 포함한다(모든 부분문자열은 접미사의 접두사 임을 이용)
        // 즉, 공통의 부분문자열을 포함한다.                
        int ret = 0;
        for(int i = 0; i + K - 1< s.size(); i++){ // 반복수 : n
            int cp = commonPrefix(s, a[i + K -1], a[i]); // 시간 복잡도 : O(n)
            ret = max(ret, cp);
        }
        cout << ret << '\n';
    }
}