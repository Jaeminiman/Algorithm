#include <vector>
#include <iostream>
#include <queue>
#include <math.h>

using namespace std;
int m;
const int INF = 999999999;
const int START = 401;
vector<pair<int,int>> adj[402];
int vertex(int node){
    return node + 200;
}
vector<int> Dijkstra(int src){
    vector<int> dist(402,INF);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0,src));
    while(!pq.empty()){
        int here = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if(dist[here] < cost) continue;

        for(int i = 0; i < adj[here].size(); i++){
            int there = adj[here][i].first;
            int nextDist = adj[here][i].second + cost;
            if(nextDist < dist[there]){
                dist[there] = nextDist;
                pq.push(make_pair(dist[there], there));                    
            }
        }        
    }
    return dist;
}

int main(){
    int C;
    cin >> C;
    while(C--){
        cin >> m;
        for(int i =0 ; i < 402; i++){
            adj[i].clear();
        }
        int a[500], b[500];
        for(int i = 0; i < m; i++){            
            cin >> a[i] >> b[i];
        }

        // 시작점 세팅
        for(int i = 0; i < m ; i++){
            int dif = a[i] - b[i];
            adj[START].push_back(make_pair(vertex(dif), a[i]));
        }

        for(int i = 0; i < m ; i++){
            int dif = a[i] - b[i];
            // 그래프 생성
            for(int start = -200; start <= 200; start++){
                int next = start + dif;
                if(abs(next) > 200) continue;

                adj[vertex(start)].push_back(make_pair(vertex(next),a[i]));
            }
            
        }
        vector<int> dist = Dijkstra(START);
        if(dist[200] == INF){
            cout << "IMPOSSIBLE" << '\n';
        }
        else{
            cout << dist[200] << '\n';
        }
        
    }
}