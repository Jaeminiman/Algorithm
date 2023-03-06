#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int MAX_V = 1001;
const int INF = 999999999;
vector<pair<int,int>> adj[MAX_V + 1];
vector<int> fire;
vector<int> station;
int V,E,n,m;

vector<int> Dijkstra(int src){
    vector<int> dist(V+2,INF);
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
                pq.push(make_pair(nextDist, there));
            }
        }
    }
    return dist;
}
int main(){
    int C;
    cin >> C;
    
    while(C--){ 
        for(int i = 0; i < MAX_V+1; i++){
            adj[i].clear();
        }
        fire.clear();
        station.clear();
        
        cin>> V >> E >> n >> m;
        for(int i = 0; i < E ; i++){
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back(make_pair(v,w));
            adj[v].push_back(make_pair(u,w));
        }
        for(int i = 0; i < n; i++){
            int f;
            cin >> f;
            fire.push_back(f);
        }
        for(int i = 0; i < m; i++){
            int s;
            cin >> s;
            station.push_back(s);
        }
        // the pseudo starting node in V+1'th node
        for(int i = 0 ; i < station.size(); i++){
            adj[V+1].push_back(make_pair(station[i],0));
        }
        vector<int> dist = Dijkstra(V+1);
        int sum = 0;
        for(int i = 0; i < fire.size(); i++){
            sum += dist[fire[i]];
        }
        cout << sum <<'\n';        
    }
}