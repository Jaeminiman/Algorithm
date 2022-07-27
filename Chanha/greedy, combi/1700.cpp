#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>

using namespace std;

int N; int K;
vector<queue<int>> elec(101);
vector<int> schedule;
set<int> currtab;
int answer = 0;

int main()
{
    cin >> N >> K;
    //스케줄 채움, 각 제품별 순서 채움
    for(int i = 0; i < K; i++)
    {
        int n; 
        cin >> n;
        schedule.push_back(n);
        elec[n].push(i);
    }

    for(int i = 0; i < schedule.size(); i++)
    {
        if(currtab.size() > N) return 0;
        if(currtab.size() < N)
        {
            currtab.insert(schedule[i]);
        }
        else if(currtab.find(schedule[i]) == currtab.end()) //멀티탭을 빼야함
        {
            vector<pair<int, int>> m; //<멀티탭에 있는 제품 가까운 순서, 그 제품의 멀티탭에서의 위치> 
            for(auto j = currtab.begin(); j != currtab.end(); j++)
            {
                if(elec[*j].empty()) elec[*j].push(200);
                m.push_back(make_pair(elec[*j].front(), *j));
            }
            sort(m.begin(), m.end());
            auto out = m.back().second;
            currtab.erase(out);
            currtab.insert(schedule[i]);
            answer++;
        }
        elec[schedule[i]].pop();
    }
    cout << answer << endl;
}