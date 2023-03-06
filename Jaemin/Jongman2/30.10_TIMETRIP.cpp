#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int maxV = 100;
const int INF = 999999999;
int V, E;
bool UNREACHABLE;
struct Edge{
    int a, b, c;
    Edge(int a, int b, int c) : a(a), b(b), c(c) {}
};
vector<Edge> edge;
vector<Edge> reverse_edge;
vector<int> BellmanFord(int src, const vector<Edge>& edges){
    vector<int> upper(V, INF);
    upper[src] = 0;
    
    bool visited;
    for(int i = 0; i < V; i++){
        visited = false;
        for(int j = 0; j < E; j++){
            int a = edges[j].a;
            int b = edges[j].b;
            int cost = edges[j].c;
            if(upper[b] > upper[a] + cost){
                upper[b] = upper[a] + cost;
                visited = true;
            }
        }
        if(!visited) break;
    }

    if(upper[1] >= INF - 1000*E){        
        UNREACHABLE = true;                
    }
    if(visited) {        
        upper.clear();        
    }

    
    return upper;
}

int main(){
    int C;
    cin >> C;
    while(C--){        
        cin >> V >> E;
        edge.clear();
        reverse_edge.clear();
        UNREACHABLE = false;

        for(int i = 0; i < E; i++){
            int a, b, c;
            cin >> a >> b >> c;
            edge.push_back(Edge(a, b, c));
            reverse_edge.push_back(Edge(a,b,-c));
        }

        vector<int> min_dist = BellmanFord(0, edge);
        vector<int> max_dist = BellmanFord(0, reverse_edge);

        if(UNREACHABLE){
            cout << "UNREACHABLE" << '\n';            
        }
        else{                            
            if(min_dist.empty()){
                cout << "INFINITY ";
            }            
            else{
                cout << min_dist[1] << " ";
            }     

            if(max_dist.empty()) cout << "INFINITY" << '\n';
            else{            
                cout << -1 * max_dist[1] << "\n";            
            }
        }

                
    }
}