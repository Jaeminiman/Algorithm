#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;
vector<vector<int>> adj;
// 각 정점의 컴포넌트 번호. 번호는 0부터 시작하며 같은 강결합컴포넌트(SCC)에 속한 정점들의 번호는 같다.
vector<int> sccId;
// 각 정점의 발견 순서
vector<int> discovered;
// 정점의 번호를 담는 스택
stack<int> st;
int sccCounter, vertexCounter;
int N;


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
bool disjoint(const pair<int,int>& a, const pair<int,int>& b){
    return a.second <= b.first || b.second <= a.first;
}
void makeGraph(const vector<pair<int,int>>& meetings){
    int vars = meetings.size(); //(2n개)
    // init
    adj.clear(); adj.resize(vars*2); //(4n size)
    for(int i = 0; i < vars; i+=2){
        // i는 주간, j는 월간 회의
        int j = i + 1;
        // (i || j) 절을 추가 <=> (!Ai -> Aj)&&(!Aj -> Ai)
        adj[i*2 + 1].push_back(j*2);
        adj[j*2 + 1].push_back(i*2);
    }
    for(int i = 0; i < vars ; i++){
        for(int j = 0; j < i; j++){
            // i번 회의와 j번 회의가 겹칠 경우 (!Ai||!Aj)
            if(!disjoint(meetings[i], meetings[j])){
                adj[i*2].push_back(j*2 + 1);
                adj[j*2].push_back(i*2 + 1);
            }
        }
    }
}
vector<int> solve2SAT(){
    int vars = 2 * N; // 변수의 수(2N)
    vector<int> label = tarjanSCC();

    // 이 SAT 문제를 푸는 것이 불가능한지 확인한다. 한 변수를 나타내는 두 정점이 같은 강결합 요소에 속해 있을 경우 답이 없다.
    for(int i =0 ; i < 2*vars; i+=2){
        // 그냥 node 랑 Not node가 같으면 안됨.
        if(label[i] == label[i+1]){
            return vector<int>();
        }
    }
    // SAT를 푸는 것이 가능하다. 답을 생성하자.
    vector<int> value(vars , -1);
    // tarjan 알고리즘에서 SCC 번호는 위상 정렬의 역순으로 배정된다.
    // SCC 번호의 역순으로 각 정점을 정렬하면 위상 정렬 순서가 된다.
    vector<pair<int,int>> order;
    for(int i = 0; i < 2*vars ; i++){
        order.push_back(make_pair(-label[i], i));
    }
    sort(order.begin(), order.end());
    // 각 정점에 값을 배정한다.
    for(int i = 0; i < 2 * vars; i++){
        int vertex = order[i].second;
        int variable = vertex/2, isTrue = vertex%2 == 0;
        if(value[variable] != -1) continue;
        // not A가 A보다 먼저 나왔으면 A는 참
        // A가 not A보다 먼저 나왔으면 A는 거짓
        value[variable] = !isTrue;
    }
    return value;
}

int main(){
    int C;
    cin >> C;
    while(C--){
        cin >> N;
        vector<pair<int,int>> meetings;
        
        for(int i = 0; i < N; i++){
            int a, b, c, d;
            cin >> a >> b >> c >> d;            
            meetings.push_back(make_pair(a,b));
            meetings.push_back(make_pair(c,d));
        }
        makeGraph(meetings);

        vector<int> ret = solve2SAT();
        vector<pair<int,int>> output;
        for(int i = 0; i < ret.size(); i += 2){
            if(ret[i] == 1 && ret[i+1] == 0){
                output.push_back(meetings[i]);
            }
            else if(ret[i] == 0 && ret[i+1] == 1){
                output.push_back(meetings[i+1]);
            }
            else if(ret[i]== 1 && ret[i+1] == 1){
                output.push_back(meetings[i]);
            }
            else{
                output.clear();
                break;
            }
        }

        if(!output.empty()){
            cout << "POSSIBLE" << "\n";
            for(int i = 0; i < output.size(); i++){
                cout<< output[i].first << " " << output[i].second << "\n";
            }
        }
        else{
            cout << "IMPOSSIBLE" << "\n";
        }

    }
}