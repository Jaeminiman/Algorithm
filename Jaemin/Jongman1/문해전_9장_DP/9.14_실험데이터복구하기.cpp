/*
reconstruct함수의 정의에 대해서..
here을 기준으로 here을 포함한 단어를 반환한다. vs. here 부분을 완전히 제외한 나머지 문자열 반환
정의하기 나름이었다. 앞에서 overlap[][]계산을 잘못했던 것임.
*/
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
int k;
vector<string> S;
int DP[1 << 15][15];
const int INF = 987654321;
int overlap[15][15];
vector<int> eraseIdx;

// here과 next가 겹치는 길이를 메모이제이션
// 매번 호출하면 시간낭비. Cache에 한번에 저장해두고 씀
// 어차피 완전히 겹치는 경우는 앞에서 제거됐으므로 맨 뒤에 붙는 경우만 고려해준다.
void overlapCalc()
{
    for (int here = 0; here < S.size(); here++)
    {
        for (int next = 0; next < S.size(); next++)
        {
            string left = S[here];
            string right = S[next];
            int lo = 0, hi = 0;
            int nextLo = 1;
            int overlapCnt = 0;
            while(lo != left.size() && hi != right.size()){
                if(left[lo] == right[hi]){
                    if(hi == 0){
                        nextLo = lo + 1;
                    }
                    overlapCnt++;
                    hi++;
                    lo++;
                }
                else{
                    overlapCnt = 0;
                    lo = nextLo++;
                    hi = 0;
                }
            }

            overlap[here][next] = overlapCnt;
        }
    }
}
void removeOverlap()
{
    eraseIdx.clear();

    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            int here = i, next = j;

            if (S[here].size() < S[next].size())
                swap(here, next);
            string longer = S[here];
            string shorter = S[next];
            for (int i = 0; i <= longer.size() - shorter.size(); i++)
            {
                if (shorter.compare(longer.substr(i, shorter.size())) == 0)
                {
                    eraseIdx.push_back(next);
                }
            }
        }
    }
    // idx뒤부터 지우면 idx가 바뀌는 일이 없어짐.
    if(!eraseIdx.empty()){
        sort(eraseIdx.begin(), eraseIdx.end());
        // 중복제거
        eraseIdx.erase(unique(eraseIdx.begin(), eraseIdx.end()), eraseIdx.end());
        for(int i = eraseIdx.size() - 1; i >= 0 ; i--){
            S.erase(S.begin() + eraseIdx[i]);
        }
    }
}

string reconstruct(int used, int here)
{
    // 기저 사례
    if (used == (1 << S.size()) - 1)
        return S[here];

    // 다음에 올 문자열 조각을 찾는다.
    for (int next = 0; next < S.size(); next++)
    {
        // used가 사용되었으면 제외
        if (((used & (1 << next)) != 0))
            continue;

        // next를 사용했을 경우의 답이 최적해와 같다면 next를 사용한다.
        int nextUsed = used + (1 << next);
        if (DP[used][here] == DP[nextUsed][next] + S[here].size() - overlap[here][next])
        {
            string s = S[here].substr(0, S[here].size() - overlap[here][next]);
            return s + reconstruct(nextUsed, next);
        }
    }
}

// taken을 사용한 상태에서, here을 맨 앞으로 하여 남은 문자열로 만들 수 있는 최소의 길이 반환
int restore(int taken, int here)
{
    int &ret = DP[taken][here];
    if (ret != -1)
        return ret;

    // 기저 사례: 모든 문자열을 다 사용하여 조합을 완성한 경우
    // cnt가 없어도 비트마스크 기저사례 체킹 가능
    if (taken == (1 << S.size()) - 1)
    {
        return ret = S[here].size();
    }

    ret = INF;
    int minNext;
    for (int next = 0; next < S.size(); next++)
    {
        // 이미 전에 선택된 경우 -> 넘어감
        if ((taken & (1 << next)) != 0)
            continue;

        int nextTaken = taken + (1 << next);
        
        int cand = restore(nextTaken, next) + S[here].size() - overlap[here][next];
        
        if (ret > cand)
        {
            ret = cand;
            minNext = next;
        }
    }

    return ret;
}
void solve(){
    int min = INF;
        int minStart = -1;
        for (int start = 0; start < S.size(); start++)
        {
            int cand = restore((1 << start), start);
            if (cand < min)
            {
                minStart = start;
                min = cand;
            }
        }
        string output = reconstruct((1 << minStart), minStart);
        cout << output << '\n';
}

void input(){
    memset(DP, -1, sizeof(DP));
    memset(overlap, 0, sizeof(overlap));
    cin >> k;
    S.clear();
    S.resize(k);
    for (int i = 0; i < k; i++)
    {
        cin >> S[i];
    }
}
int main()
{
    int C;
    cin >> C;
    for (int epoch = 0; epoch < C; epoch++)
    {
        // 입력 받기 및 전 epoch에 대한 것 초기화
        input();
        // 중복 제거
        removeOverlap();
        // 겹치는 길이 메모이제이션 전처리
        overlapCalc();
        // 문제풀이 로직
        solve(); 
    }
}