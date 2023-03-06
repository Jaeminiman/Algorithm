#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 코드 28.1 그래프의 깊이 우선탐색(DFS)
// 그래프의 인접 리스트 표현
vector<vector<int>> adj;
// 각 정점을 방문했는지 여부를 확인
vector<bool> visited;
// 깊이 우선 탐색을 구현
void dfs(int here){
    cout << "DFS visits" << here << '\n';
    visited[here] = true;
    for(int i = 0; i < adj[here].size(); i++){
        int there = adj[here][i];
        if(!visited[there]){
            dfs(there);
        }        
    }    
}

// 모든 정점을 방문하는 구현
void dfsAll(){
    visited = vector<bool>(adj.size(), false);
    for(int here = 0; here < adj.size(); here++){
        if(!visited[here]){
            dfs(here);
        }        
    }
}

// 코드 28.4 깊이 우선 탐색을 이용한 오일러 서킷 찾기
// 그래프의 인접행렬 표현. adj[i][j] = i와 j 사이의 간선수
vector<vector<int>> adj;
// 무향 그래프의 인접 행렬 adj가 주어질 때 오일러 서킷을 계산한다.
// 결과로 주어지는 curcuit을 뒤집으면 오일러 서킷이 된다.
void getEulerCircuit(int here, vector<int>& circuit){
    for(int there = 0; there < adj[here].size(); there++){
        while(adj[here][there]> 0){
            adj[here][there]--;
            adj[there][here]--;
            getEulerCircuit(there, circuit);
        }         
    }
    circuit.push_back(here);
}

// 코드 28.8 간선을 구분하는 깊이 우선 탐색의 구현
vector<vector<int>> adj;
// discoverd[i] = i번 정점의 발견 순서
// finished[i] = dfs(i)가 종료했으면 1, 아니면 0
vector<int> discovered, finished;
// 지금까지 발견한 정점 수
int counter;
void dfs2(int here){
    discovered[here] = counter++;
    for(int i = 0; i < adj[here].size(); i++){
        int there = adj[here][i];
        if(discovered[there] == -1){
            dfs2(there);
        }
        else if(discovered[here] < discovered[there]){
            cout << "forward edge" << '\n';
        }
        else if(finished[there] == 1){
            cout << "cross edge" << '\n';
        }
        else{
            cout << "back edge" << '\n';
        }
    }
    finished[here] = 1;
}

// 코드 28.9 무향 그래프에서(교차 간선이 없다) 절단점을 찾는 알고리즘
vector<vector<int>> adj;
vector<int> discovered;
// 각 정점이 절단점인지 여부
vector<bool> isCutVertex;
int counter = 0;
int findCutVertex(int here, bool isRoot){
    discovered[here] = counter++;
    int ret = discovered[here];
    // 루트인 경우 절단점의 판정을 위해 자손 서브트리의 개수를 센다.
    int children = 0;
    for(int i = 0; i < adj[here].size(); i++){
        int there = adj[here][i];
        if(discovered[there] == -1){
            ++children;
            // 서브트리(there)에서 갈 수 있는 가장 높은 정점번호
            int subtree = findCutVertex(there, false);
            // 그 노드가 자기 자신 이하에 있다면 현재 위치는 절단점
            if(!isRoot && subtree >= discovered[here]){
                isCutVertex[here] = true;
                ret = min(ret, subtree);
            }
            else{
                ret = min(ret, discovered[there]);
            }
            
        }
        // 루트인 경우 졀댠졈 판정은 서브트리의 개수로 한다.
        if(isRoot){
            isCutVertex[here] = (children >= 2);
        }
        return ret;
    }
}

#include <stack>
// 코드 28.10 타잔의 강결합 컴포넌트 분리 알고리즘의 구현
vector<vector<int>> adj;
// 각 정점의 컴포넌트 번호. 번호는 0부터 시작하며 같은 강결합컴포넌트(SCC)에 속한 정점들의 번호는 같다.
vector<int> sccId;
// 각 정점의 발견 순서
vector<int> discovered;
// 정점의 번호를 담는 스택
stack<int> st;
int sccCounter, vertexCounter;
// here을 루트로 하는 서브트리에서 역방향 간선이나 교차 간선을 통해 갈 수 있는 정점 중 최소 발견 순서를 반환한다.
// 단, 이미 SCC로 묶인 정점으로 연결된 교차간선은 무시한다.
int scc(int here){
    int ret = discovered[here] = vertexCounter++;
    // 스택에 here을 넣는다. here의 후손들은 모두 스택에서 here 후에 들어간다.
    st.push(here);
    for(int i = 0; i < adj[here].size(); i++){
        int there = adj[here][i];
        // (here, there)은 트리 간선
        if(discovered[there] == -1){
            ret = min(ret, scc(there));
        }
        // there가 무시해야하는 교차 간선이 아니라면
        else if(sccId[there] == -1){
            ret = min(ret, discovered[there]);
        }
    }
    // here에서 부모로 올라가는 간선을 끊어야 할지 확인한다.
    if(ret == discovered[here]){
        // here을 루트로 하는 서브트리에 남아 있는 정점들을 전부 하나의 컴포넌트로 묶는다.
        while(true){
            int t = st.top();
            sccId[t] = sccCounter;
            st.pop();
            if(t==here) break;
        }
        ++sccCounter;
    }
    return ret;
}
// tarjan의 SCC 알고리즘
vector<int> tarjanSCC(){
    // 배열들을 전부 초기화
    sccId = discovered = vector<int>(adj.size(), - 1);
    // 카운터 초기화
    sccCounter = vertexCounter = 0;
    // 모든 정점에 대해 scc() 호출
    for(int i = 0; i < adj.size(); i++){
        if(discovered[i] == -1){
            scc(i);
        }        
    }
    return sccId;
}