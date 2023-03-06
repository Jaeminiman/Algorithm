#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// 코드 24.1 배열의 구간 최소 쿼리(Range Minimum Query,  RMQ) 문제를 해결하는 구간 트리의 초기화
struct RMQ{
    // 배열의 길이
    int n;
    // 각 구간의 최소치
    vector<int> rangemin;
    RMQ(const vector<int>& array) {
        n = array.size();
        rangemin.resize(n*4); // 4n배 하면 어떻게든 모든 구간합을 담을 수 있음
        init(array, 0, n-1, 1);
    }
    // node 노드가 array[left..right] 배열을 표현할 때
    // node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다. (재귀적으로 수행)
    // 시간 복잡도 : O(n) -> 각 node별로 한번 씩 수행
    int init(const vector<int>& array, int left, int right, int node){                
        if(left == right){
            return rangemin[node] = array[left];
        }
        int mid = (left + right) / 2;
        int ret = min(init(array, left, mid, node*2), init(array, mid + 1, right, node*2 + 1));
        return rangemin[node] = ret;        
    }
    // node가 표현하는 범위 array[nodeLeft, nodeRight]가 주어질 때,
    // 이 범위와 array[left..right]의 교집합의 최소치를 구한다.
    int query(int left, int right,int node, int nodeLeft, int nodeRight){
        // 교집합 없는 경우
        if(right < nodeLeft || nodeRight < left){
            return 987654321;
        }
        // 구간이 완전 겹치는 경우
        else if(left <= nodeLeft && right >= nodeRight){
            return rangemin[node];
        }
        // 나머지 경우
        else{
            int nodeMid = (nodeLeft + nodeRight)/2; 
            return min(query(left,right, node*2, nodeLeft, nodeMid), query(left,right,node*2 + 1, nodeMid + 1, nodeRight));
        }
    }
    // query()를 외부에서 호출하기 위한 인터페이스
    int query(int left, int right){
        return query(left,right,1,0,n-1);
    }
    // array[index] = newValue로 바뀌었을 때, node를 루트로 하는 구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.(재귀적 Update)
    int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
        // index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
        if(index < nodeLeft || index > nodeRight){
            return rangemin[node];
        }
        // base case
        if(nodeLeft == nodeRight){
            return rangemin[node] = newValue;
        }
        int mid = (nodeLeft + nodeRight) / 2;
        return rangemin[node] = min(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node *2 + 1, mid + 1, nodeRight));
    }
    // update()를 외부에서 호출하기 위한 인터페이스
    int update(int index, int newValue){
        return update(index, newValue, 1, 0, n-1);
    }
};

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int C;
    cin >> C;
    while(C--){
        int N, Q;
        cin >> N >> Q;
        vector<int> array1;
        vector<int> array2;
        while(N--){
            int x;
            cin >> x;
            array1.push_back(x); 
            array2.push_back((-1) * x);
        }
        RMQ rmqMin(array1);
        RMQ rmqMax(array2);
        int ret = 0;
        while(Q--){
            int a, b;
            cin >> a >> b;
            ret = - rmqMin.query(a,b) - rmqMax.query(a, b);
            cout << ret << '\n';
        }
        
    }
}