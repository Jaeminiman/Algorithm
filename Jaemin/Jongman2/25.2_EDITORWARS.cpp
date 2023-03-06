#include <iostream>
#include <vector>
#include <string>
#include <math.h>
int N, M;
using namespace std;

struct BipartiteUnionFind{
    vector<int> parent, rank, size, op;

    BipartiteUnionFind(int n) :parent(n),rank(n,1),size(n,1), op(n,-1){
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }        
    }
    int find(int u){
        if(u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    int merge(int u, int v){
        if(u==-1 || v==-1) return max(u,v);
        u = find(u); v = find(v);        
        if(u==v) return u;       
                
        // rank는 v가 항상 크거나 같으므로, u가 v에 들어간다.
        if(rank[u] > rank[v]) swap(u,v);
        parent[u] = v; size[v] += size[u];        
        if(rank[u] == rank[v]) rank[v]++; 
        return v;               
    }
    bool dis(int u, int v){
        u = find(u); v = find(v);
        if(u == v) return false;
        int a = merge(op[u], v);
        int b = merge(op[v], u);
        op[a] = b;
        op[b] = a;
        return true;
    }
    bool ack(int u, int v){
        u = find(u); v = find(v);        
        if(op[u] == v) return false;
        int a = merge(u,v);
        int b = merge(op[u],op[v]);
        op[a] = b; 
        // 적대집합이 없는 경우 b == -1
        if(b!= -1) op[b] = a;
        return true;
    }    
};
int maxParty(const BipartiteUnionFind& buf){
    int ret = 0;
    for(int node = 0; node < N; node++){
        // 루트인 경우
        if(buf.parent[node] == node){            
            int enemy = buf.op[node];
            if(node < enemy) continue;
            int mySize = buf.size[node];
            int enemySize = (enemy == -1) ? 0 : buf.size[enemy];
            ret += max(mySize, enemySize);
        }    
    }
    return ret;
}
void contradict(int n){
    cout << "CONTRADICTION AT " << n << '\n';
}

int main(){
    int C;
    cin >> C;
    while(C--){
        
        cin >> N >> M;
        BipartiteUnionFind set(N);
        bool correct = true;
        for(int i = 1; i<=M;i ++){
            int a, b;
            string s;
            cin >> s >> a >> b;
            if(!correct){
                continue;
            }
            if(s == "ACK"){
                if(!set.ack(a,b)){
                    contradict(i);
                    correct = false;                    
                }                
            }
            else{
                if(!set.dis(a,b)){
                    contradict(i);
                    correct = false;                    
                }                
            }        
            
        }
        if(correct){cout << "MAX PARTY SIZE IS " << maxParty(set) << '\n';}
                  
    }
}