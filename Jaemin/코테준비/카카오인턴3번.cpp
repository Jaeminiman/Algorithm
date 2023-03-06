#include <string>
#include <vector>
#include<algorithm>
#include<cstring>
#include<iostream>
using namespace std;



class Problem{
    public:
        int alp_req;
        int cop_req;
        int alp_rwd;
        int cop_rwd;
        int cost;
        Problem(int alp_req, int cop_req, int alp_rwd, int cop_rwd, int cost){
            this-> alp_req = alp_req;
            this-> cop_req = cop_req;
            this-> alp_rwd = alp_rwd;
            this-> cop_rwd = cop_rwd;
            this-> cost = cost;
        }
};
int targetAlp, targetCop;
const int INF = 123456789;
vector<Problem> problem_list;
int DP[151][151];
int costEstimation(int alp, int cop){
    if(alp >= targetAlp && cop >= targetCop){
        return 0;
    }

    if(alp > targetAlp) alp = targetAlp;
    if(cop > targetCop) cop = targetCop;

    int& ret = DP[alp][cop];
    if(ret != -1) return ret;

    ret = INF;
    for(Problem problem : problem_list){
        if(problem.alp_req <= alp && problem.cop_req <= cop){
            ret = min(ret, costEstimation(alp+problem.alp_rwd, cop + problem.cop_rwd) + problem.cost);
        }
    }
    return ret;
}
int solution(int alp, int cop, vector<vector<int>> problems) {
    
    // 목표 alp, 목표 cop이 있다.
    targetAlp = 0; targetCop = 0;
    problem_list.push_back(Problem(0,0,1,0,1));
    problem_list.push_back(Problem(0,0,0,1,1));
    for (vector<int> problem : problems){
        problem_list.push_back(Problem({problem[0], problem[1], problem[2],problem[3], problem[4]}));
        targetAlp = max(targetAlp, problem[0]);
        targetCop = max(targetCop, problem[1]);
    }
    memset(DP, -1, sizeof(DP));
    int answer = costEstimation(alp,cop);
    return answer;
}

int main(){
    int alp = 10;
    int cop = 10;
    vector<int> a = {10,15,2,1,2};
    vector<int> b = {20,20,3,4,4};
    vector<vector<int>> ab = {a,b};
    cout << solution(alp,cop,ab) << '\n';
}