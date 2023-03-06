#include <iostream>
#include <vector>
#include <math.h>
#include <cstring>
using namespace std;
#define MAX_N 100000
vector<int> child[MAX_N];
// 트리의 번호와 일련 번호 사이의 대응 관계
int no2serial[MAX_N], serial2no[MAX_N];
// 각 노드가 trip에 처음 등장하는 위치, 그리고 각 노드의 깊이
int locInTrip[MAX_N], depth[MAX_N];
// 다음 일련 번호
int nextSerial;



struct RMQ{
    int n;
    vector<int> rangeMin;
    RMQ(const vector<int>& array){
        n = array.size();
        rangeMin.resize(n * 4);        
        init(array, 1, 0, n-1);
    }
    int init(const vector<int>& array, int node, int left, int right){
        if(left == right) return rangeMin[node] = array[left];
        
        int mid = (left + right) / 2;
        return rangeMin[node] = min(init(array, node*2, left, mid), init(array, node*2 + 1, mid + 1, right));
    }
    int query(int node, int nodeLeft, int nodeRight, int left, int right){
        if(nodeLeft > right || nodeRight < left){
            return 987654321;
        }
        if(nodeLeft >= left && nodeRight <= right){
            return rangeMin[node];
        }
        else{
            int mid = (nodeLeft + nodeRight) / 2;
            return min(query(node*2, nodeLeft, mid, left, right), query(node*2+1, mid+1, nodeRight, left, right));
        }
    }
    int query(int left, int right){
        return query(1,0,n-1, left, right);
    }
};

void preorderTraverse(int node, int d, vector<int>& trip){    
    // traverse()가 처음 방문하자마자 일련번호를 부여한다.
    // 이렇게 하면 항상 부모는 자손보다 작은 일련번호를 가지게 된다.
    no2serial[node] = nextSerial;
    serial2no[nextSerial] = node;
    ++nextSerial;
    // 깊이 계산
    depth[node] = d;
    // trip에 현재 노드의 일련 번호를 추가한다.
    locInTrip[node] = trip.size();
    trip.push_back(no2serial[node]);
    // 모든 자식 노드를 방문    
    for(int i = 0; i < child[node].size() ; i++){        
        preorderTraverse(child[node][i], d+1, trip);
        // 자식 노드를 방문하고 현재 노드로 돌아올 때마다 다시 추가하기
        trip.push_back(no2serial[node]);
    }
}  
// 트리를 순회하며 각종 필요한 정보를 계산하고,
// RMQ 구간 트리를 만들어 반환한다.
RMQ* prepareRMQ(){
    nextSerial = 0;    
    // trip : 전위 순회 과정에서 만나는 각 노드들의 일련번호
    vector<int> trip;
    preorderTraverse(0,0,trip);
    return new RMQ(trip);
}


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);    
    int C;
    cin >> C;
    while(C--){
        nextSerial = 0;             
        for(int i = 0; i < MAX_N; i++){
            child[i].clear();
        }
        memset(locInTrip, 0, sizeof(locInTrip));
        memset(depth, 0, sizeof(depth));
        memset(no2serial, 0, sizeof(no2serial));
        memset(serial2no, 0, sizeof(serial2no));        

        int N, Q;
        cin >> N >> Q;
        // make a input tree
        for(int i = 1; i < N; i++){
            int x;
            cin >> x;
            child[x].push_back(i);
        }
        RMQ* rmq = prepareRMQ();        
        for(int i = 0; i < Q; i++){
            int a, b;
            cin >> a >> b;
            int minIdx = locInTrip[a];
            int maxIdx = locInTrip[b];
            if(minIdx > maxIdx) swap(minIdx, maxIdx);
            cout <<depth[a] + depth[b] - 2 * depth[serial2no[rmq->query(minIdx, maxIdx)]] << '\n';
        }
        
        


    }
}