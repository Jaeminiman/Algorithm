using namespace std;
#include <vector>
#include <string>

// 예제 20.1 그냥 문자열 searching
vector<int> naiveSearch(const string& H, const string& N){
    vector<int> ret;

    for(int begin = 0; begin + N.size() <= H.size(); ++begin){
        bool matched = true;
        for(int i = 0; i < N.size(); i++){
            if(H[begin] != N[i]){
                matched = false;
                break;
            }
        }
        if(matched) ret.push_back(begin);
    }
    return ret;
}

// 예제 20.2 KMP 알고리즘
vector<int> getPartialMatch(const string& N){

}
vector<int> kmpSearch(const string& H, const string& N){
    int n = H.size(), m = N.size();
    vector<int> ret;

    // pi[i] : N[..i]의 접미사도 되고, 접두사도 되는 문자열의 최대 길이 (부분 일치 테이블)
    vector<int> pi = getPartialMatch(N);

    // begin = matched = 0에서 부터 시작하자
    int begin = 0, matched = 0;
    while(begin + m <= n){
        if(matched < m && H[begin + matched] == N[matched]){
            ++matched;
            if(matched == m) ret.push_back(begin);
        }
        else{
            // 예외 처리. 하나도 matching이 없는 경우
            if(matched == 0){
                ++begin;
                continue;
            }
            
            begin = begin + (matched - pi[matched-1]);
            // begin을 옮기고 이미 matching된 부분은 최적화를 위해 건너뛰고 진행한다.
            matched = pi[matched-1];
        }

    }
    return ret;
}

// 코드 20.3 단순한 문자열 알고리즘 이용해 부분 일치 테이블 계산하기
vector<int> getPartialMatchNaive(const string& N){
    int m = N.size();
    vector<int> pi(m, 0);

    for(int begin = 1; begin < m; begin ++){
        for(int i = 0; i + begin < m; i++){
            if(N[begin + i] == N[i]){
                pi[begin + i] = max(i + 1, pi[begin + i]);
            }
            else{
                break;
            }
        }
    }
    return pi;
}

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
                continue;
            }
            
            begin += matched - pi[matched - 1];
            matched = pi[matched - 1];
            

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

// 코드 20.6 팰린드롬 만들기 문제를 해결하는 KMP 알고리즘의 변형
int maxOverlap(const string& a, const string& b){
    int n = a.size(), m = b.size();
    vector<int> pi = getPartialMatch(b);
    int begin = 0, matched = 0;
    while(begin < n){
        if(matched < m && a[begin+matched] == b[matched]){
            matched++;
            if(matched + begin == n){
                return matched;
            }
        }
        else{     
            if(matched == 0) ++begin;
            else{
                begin += matched - pi[matched - 1];
                matched = pi[matched-1];
            }       
            
        }
    }
    return 0;
}

// 코드 20.7 KMP 알고리즘의 '전통적인' 버전
vector<int> kmpSearch2(const string& H, const string& N){
    int n = H.size(), m = N.size();
    vector<int> ret;
    vector<int> pi = getPartialMatch(N);
    int matched = 0;
    for(int i = 0; i < n; i++){
        while(matched >0 && H[i] != N[matched]){
            matched = pi[matched - 1];
        }
        // 글자가 대응될 경우
        if(H[i] == N[matched]){
            ++matched;
            if(matched == m){
                ret.push_back(i - m + 1);
                matched = pi[matched - 1];
            }
        }
    }
}

#include <cstring>
// 코드 20.8 접미사 배열을 계산하는 단순 알고리즘 (시간 복잡도 : O(n^2log(n)))
// 두 접미사의 시작위치 i,j가 주어질 때, 두 접미사 중 어느 쪽이 앞에 와야할지 비교한다.
struct SuffixComparator{
    const string& s;
    
    SuffixComparator(const string& _s) : s(_s){}
    bool operator() (int i, int j){
        return strcmp(s.c_str() + i, s.c_str() + j) < 0;
    }
};
// s의 접미사 배열을 계산한다.
vector<int> getSuffixArrayNaive(const string& s){
    vector<int> perm;
    for(int i = 0; i < s.size(); i++){
        perm.push_back(i);
    }
    sort(perm.begin(), perm.end(), SuffixComparator(s));
    return perm;
}

// 코드 20.9. 첫 t글자로 묶인 그룹 정보를 이용해 첫 2t 글자를 비교하는 비교자의 구현

//각 접미사들의 첫 t글자를 기준으로 한 group[]이 주어질 때
//주어진 두 접미사를 첫 2*t글자를 기준으로 비교한다.
//group[]은 길이가 0인 접미사도 포함한다.
struct Comparator{
    const vector<int>& group;
    int t;
    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t){}
    bool operator() (int a, int b){
        // case 1. 첫 t글자가 다르면 이들을 이용해 비교
        if(group[a] != group[b]) return group[a] < group[b];
        // case 2. 첫 t글자가 같으면 t글자 이후의 t글자로 비교
        else return group[a+t] < group[b+t];
    }
};

// 코드 20.10 접미사 배열을 계산하는 맨버와 마이어스의 알고리즘
// string s의 접미사 배열을 계산
vector<int> getSuffixArray(const string& s){
    int n = s.size();
    //group[i] : 접미사들을 첫 t글자를 기준으로 정렬했을 때, 접미사 s[i..]가 들어가는 그룹 번호
    //t=1일 때는 정렬할 것도 없이 suffix s[i..]의 첫 글자로 그룹번호를 정해줄 수 있다.
    int t = 1;
    vector<int> group(n+1);
    for(int i = 0; i < n; i++) group[i] = s[i];
    group[n] = -1; // 길이가 0인 접미사도 포함하는데, 이를 맨 앞에 빼둔다
    // perm[] : 결과적으로 접미사 배열이 될 반환 값, 이 배열을 log(n)번 정렬한다.
    vector<int> perm;
    for(int i = 0; i < n; i++) perm.push_back(i);
    while(t < n){
        // group[]은 첫 t글자를 기준으로 계산되어 있는 상태
        // 첫 2t글자를 기준으로 perm을 다시 정렬한다.
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);

        // 2t글자가 n을 넘는다면 새로운 group을 만들 필요도 없이 그냥 종료
        t *= 2;
        if(t >= n) break;
        // 2t글자를 기준으로 한 group[]을 만든다.
        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i = 0; i < n - 1; i++){
            if(compareUsing2T(perm[i], perm[i+1])){
                newGroup[perm[i+1]] = newGroup[perm[i]] + 1;                
            }
            else{
                newGroup[perm[i+1]] = newGroup[perm[i]];
            }
        }
        group = newGroup;
    }
    return perm;
}

// 코드 20.12 접미사 배열을 이용해 다른 부분 문자열의 수를 세는 알고리즘
//s[i..]와 s[j..]의 공통 접두사의 최대 길이를 계산(부분 문자열이 중복되는 길이)
int commonPrefix(const string& s, int i, int j){
    int cnt = 0;
    while(i < s.size() && j < s.size() && s[i]==s[j]){
        cnt++;
        i++, j++;
    }
    return cnt;
}
// s의 서로 다른 부분 문자열의 수를 계산
int countSubstrings(const string& s){
    vector<int> a = getSuffixArray(s);
    int n = s.size();
    int cnt = 0;
    for(int i = 0; i<a.size() ; i++){
        int cp = 0;
        if(i > 0) cp = commonPrefix(s,i-1,i);
        // a[i]의 n-a[i]개의 접두사들 중에서 cp개는 중복이다.
        cnt += n - a[i] - cp;
    }
    return cnt;
    

}