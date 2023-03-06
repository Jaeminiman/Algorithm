#include <queue>
#include <vector>

using namespace std;

// 코드 30.1 다익스트라의 최단 거리 알고리즘의 구현
// 정점의 개수
int V;
const int MAX_V = 10;
const int INF = 987654321;
// 그래프의 인접 리스트(연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int,int>> adj[MAX_V];
vector<int> dijkstra(int src){
    vector<int> dist(V,INF);
    dist[src] = 0;
    // 작은것부터 올라가는 오름차순
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push(make_pair(0,src));
    while(!pq.empty()){
        int cost = pq.top().first;
        int here = pq.top().second;
        pq.pop();
        // 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
        if(dist[here] < cost) continue;

        // 인접한 정점들을 모두 검사한다.
        for(int i = 0; i < adj[here].size(); i++){
            int there = adj[here][i].first;            
            int nextDist = cost + adj[here][i].second;
            // 더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
            if(dist[there] > nextDist){
                pq.push(make_pair(nextDist, there));
            }
        }
    }
    return dist;
}

// 코드 30.2 우선순위 큐를 사용하지 않는 다익스트라 알고리즘의 구현(시간 복잡도 : O(V^2 + E))
vector<int> dijkstra2(int src){
    vector<int> dist(V,INF);
    // 각 정점을 방문했는지 여부 저장
    vector<int> visited(V,false);
    dist[src] = 0; visited[src] = true;
    while(true){
        // 아직 방문하지 않은 정점 중 가장 가까운 정점을 찾는다.
        int closest = INF, here;
        for(int i = 0; i < V; i++){
            if(closest > dist[i] && !visited[i]){
                here = i;
                closest = dist[i];
            }            
        }
        if(closest == INF) break;

        visited[here] = true;
        for(int i=0 ; i < adj[here].size(); i++){
            int there = adj[here][i].first;
            if(visited[there]) continue;
            
            int nextDist = closest + adj[here][i].second;
            dist[there] = min(dist[there], nextDist);                            
        }
    }
    return dist;
}

// 코드 30.4 벨만-포드 알고리즘의 구현
 
// 정점의 개수
int V;
vector<pair<int,int>> adj[MAX_V];
vector<int> bellmanFord(int src){
    vector<int> upper(V, INF);
    upper[src] = 0;
    bool updated;
    for(int it = 0; it < V; it++){
        updated = false;
        for(int here = 0; here < V; here++){
            for(int i = 0; i < adj[here].size(); i++){
                int there = adj[here][i].first;
                int cost = adj[here][i].second;
                if(upper[there] > upper[here] + cost){
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        }
        if(!updated) break;
    }
    // 음수 사이클 존재
    if(updated) upper.clear();
    return upper;

}

// 코드 30.6 플로이드 알고리즘의 프로토타입 구현
int V;
int adj[MAX_V][MAX_V];
int C[MAX_V][MAX_V][MAX_V];
void allPairShortestPath1(){
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(i!=j){
                C[0][i][j] = min(adj[i][j], adj[i][0] + adj[0][j]);
            }
            else{
                C[0][i][j] = 0;
            }           
        }
    }
    for(int k = 1; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                C[k][i][j] = min(C[k-1][i][j], C[k-1][i][k] + C[k-1][k][j]);
            }
        }
                
    }
            
}

// 코드 30.7 플로이드 알고리즘의 구현
int V;
int adj[MAX_V][MAX_V];
void floyd(){
    for(int i = 0; i < V; i++) {
        adj[i][i] = 0;
    }

    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}

// 코드 30.8 플로이드 알고리즘에서 실제 최단 경로 계산하기
int V;
int adj[MAX_V][MAX_V];
// via[u][v] = u에서 v로 가는 최단 경로가 경유하는 점 중 가장 번호가 큰 정점 (즉, 가장 늦게 update된 것)
int via[MAX_V][MAX_V];
void floyd2(){
    for (int i = 0; i < V; i++){
        adj[i][i] = 0;
    }

    memset(via, -1, sizeof(via));
    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                if(adj[i][j] > adj[i][k] + adj[k][j]){
                    via[i][j] = k;
                    adj[i][j] = adj[i][k] + adj[k][j];
                }
            }
        }
    }
}
void reconstruct(int u, int v, vector<int>& path){
    if(via[u][v] == -1){
        path.push_back(u);
        if(u!=v) path.push_back(v);
    }
    else{
        int w = via[u][v];
        reconstruct(u,w,path);
        path.pop_back(); // w중복 방지
        reconstruct(w,v,path);
    }
}