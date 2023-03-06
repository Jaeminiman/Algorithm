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
            return min(query(left,right, node*2, nodeLeft, nodeMid), query(left,right,node*2 + 1, nodeMid, nodeRight));
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

// 예제 : 정렬된 수열의 특정 구간에서 최대 출현 빈도 계산
// 코드 24.4 숫자의 최대 출현 횟수 문제의 두개의 답을 합치기
// 부분 구간의 계산결과
struct RangeResult{
    int size;
    int rightNumber, rightCnt;
    int leftNumber, leftCnt;
    int mostFreqCnt;
};
// 왼쪽 부분 구간의 계산 결과 a, 오른쪽 부분 구간의 계산 결과 b를 합친다.
RangeResult merge(const RangeResult& a, const RangeResult& b){
    RangeResult ret;
    int mergedSum = 0;
    
    ret.mostFreqCnt = max(a.mostFreqCnt, b.mostFreqCnt);
    ret.mostFreqCnt = max(ret.mostFreqCnt, mergedSum);
    ret.size = a.size + b.size;
    ret.leftNumber = a.leftNumber;
    ret.rightNumber = b.rightNumber;
    // cnt의 경우 [1,1,1,1] , [1,2,2,2]를 합치는 경우 달라질 수 있음.
    ret.leftCnt = a.leftCnt;
    ret.rightCnt = b.rightCnt;
    if(a.rightNumber == b.leftNumber){
        mergedSum = a.rightCnt + b.leftCnt;
        if(a.leftCnt == a.size){
            ret.leftCnt += b.leftCnt;
        }    
        if(b.rightCnt == b.size){
            ret.rightCnt += a.rightCnt;
        }   
    }
    return ret; 
}

// 코드 24.7 팬윅 트리의 구현
// 팬윅 트리의 구현. 가상의 배열 A[]의 부분 합을
// 빠르게 구현할 수 있도록 한다. 초기화 시에는 A[]의
// 원소가 전부 0이라고 생각한다.
struct FenwickTree{
    vector<int> tree;
    FenwickTree(int n) : tree(n+1){}
    // A[0..pos]의 부분합을 구한다.
    int sum(int pos){
        // 팬윅 트리 내부에서는 인덱스가 1부터 시작된다고 생각
        ++pos;
        int ret = 0;
        while(pos > 0){
            ret += tree[pos];
            // 다음 구간을 찾기 위해 마지막 남은 비트를 지운다.
            pos = pos & (pos -1);
        }
        return ret;
    }
    // A[pos]에 val을 더한다.
    void add(int pos, int val){
        ++pos;        
        while(pos < tree.size()){
            tree[pos] += val;
            pos = pos + (pos & -pos);
        }        
    }
};