#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
const int MAX_V = 501;
const int INF = 987654321;
int T[MAX_V];
vector<pair<int,int>> order;
int V, E;
int adj[MAX_V][MAX_V];
int via[MAX_V][MAX_V];
void floyd(){        
    // 1-hop 경로에 대한 최악의 상황 cost계산(initialize)
    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= V; j++){
            via[i][j] = 0;
        }
    }
    
    for(int k = 0; k < V; k++){
        for(int i = 1; i <= V; i++){
            for(int j = 1; j <= V; j++){
                int w = order[k].second;
                if(adj[i][j] + via[i][j] > adj[i][w] + adj[w][j] + T[w]){
                    adj[i][j] = adj[i][w] + adj[w][j];
                    via[i][j] = order[k].first;
                }                
            }
        }
    }
}

int main(){    
    cin >> V >> E;    
    for(int i = 1; i <= V; i++){
        cin >> T[i];   
        order.push_back(make_pair(T[i], i));
    }
    sort(order.begin(), order.end());

    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= V; j++){
            if(i!=j){
                adj[i][j] = INF;
            }
            else{
                adj[i][i] = 0;
            }            
        }
    }
    for(int i = 0; i < E; i++){
        int u, v, cost;
        cin >> u >> v >> cost;
        adj[u][v] = cost;
        adj[v][u] = cost;
    }
    floyd();
    int C;
    cin >> C;
    while(C--){
        int a, b;
        cin >> a >> b;
        cout << adj[a][b] + via[a][b] << '\n';
    }
}