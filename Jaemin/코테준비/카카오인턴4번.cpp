#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <cstring>
#include<algorithm>
using namespace std;

const int INF = 98765432;
struct Walking
{
    int node;
    int cost;
    bool operator<(const Walking w) const
    {
        return this->cost > w.cost; // 오름차순
    }
};
map<int, vector<Walking>> adjacency;

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits)
{

    for (vector<int> path : paths)
    {
        adjacency[path[0]].push_back(Walking({path[1], path[2]}));
        adjacency[path[1]].push_back(Walking({path[0], path[2]}));
    }
    
    for (int summit : summits)
    {
        adjacency[summit].clear();
    }
    
    int dist[n + 1];
    for (int i = 0; i <= n; i++)
    {
        dist[i] = INF;
    }
    for (int gate : gates)
    {
        dist[gate] = 0;
    }
    priority_queue<Walking> qu;

    for (int gate : gates)
    {
        qu.push({gate, 0});
    }

    while (!qu.empty())
    {
        int cost = qu.top().cost; // 다음 방문할 점의 dist
        int here = qu.top().node;

        qu.pop();
        for (int i = 0; i < adjacency[here].size(); i++)
        {
            int next = adjacency[here][i].node;
            int nextcost = adjacency[here][i].cost;

            if (dist[next] > max(nextcost, dist[here]))
            {
                dist[next] = max(nextcost, dist[here]);
                qu.push({next, dist[next]});
            }
        }
    }
    sort(summits.begin(), summits.end());
    
    vector<int> answer = {0,INF};
    for(int sm : summits){
        if(dist[sm] < answer[1]){
            answer[0] = sm, answer[1] = dist[sm];
        }
    }
    return answer;
}
int main()
{
    int n = 6;
    vector<vector<int>> paths = {{1, 2, 3}, {2, 3, 5}, {2, 4, 2}, {2, 5, 4}, {3, 4, 4}, {4, 5, 3}, {4, 6, 1}, {5, 6, 1}};
    vector<int> gates = {1, 3};
    vector<int> summits = {5};
    vector<int> output = solution(n, paths, gates, summits);
    cout << output[0] << endl;
    cout << output[1] << endl;
}