/*
자료구조 : 세그먼트 트리(이진트리)
(2번요청)자료가 지속적으로 변하는 요청이 있는 상황에서 (1번요청)구간합을 지속적으로 구하는 문제의 경우 M의 요청이 있고 N크기의 배열이라면
O(NM)의 시간이 걸린다. 이를 세그먼트 트리로 관리하면 O(logN)의 시간으로 관리할 수 있게된다.

리프노드(자식이 없는 말단 노드)는 배열의 값 그 자체를, 그게 아닌 노드에는 해당 자식들의 합을 저장하는 형태를 이룬다.

크기가 N인 배열이 존재할 때
1. 트리의 높이 = ceil(log_2(N)) // ceil -> 올림함수
2. 세그먼트 트리의 크기(배열의 크기) = (1<<(트리의 높이 + 1))

참고 : https://yabmoons.tistory.com/431
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
vector<int> segmentTree;
int N;

// 1번 요청_구간합을 지속적으로 구하는 문제
// currnode = 노드번호, {start, end} : 해당 노드가 포함하고 있는 범위
// {left, right} : 우리가 구하고자 하는 범위
int make_sum(int currNode, int start, int end, int left, int right){
    // 경우 1. 완전히 벗어난 경우
    if(left > end || right < start) return 0;
    // 경우 2. 완전히 포함된 경우
    if(left <= start && right >= end) return segmentTree[currNode];
    // 경우 3. 일부만 걸친 경우
    int mid = (start + end) / 2;
    int leftResult = make_sum(currNode*2,start,mid,left,right);
    int rightResult = make_sum(currNode*2+1,mid+1,end,left,right); 
    return leftResult + rightResult;
}

// 2번 요청_자료가 지속적으로 변하는 요청이 있는 상황
// ex. 2번 Index의 값을 2에서 5로 바꾸세요. index = 2, diff = +3
void update_segmentTree(int currNode, int start, int end, int index, int diff){
    // 경우 1. 바꾸는 index가 보고 있는 구간합 범위에 포함되지 않을 경우 (그냥 넘어간다)
    if(index < start || index > end) return;
    // 경우 2. 바꾸는 index가 구간합 범위에 포함되는 경우 -> 바꿔주고 더 들어가면서 끝까지 수선해나간다.
    segmentTree[currNode] = segmentTree[currNode] + diff;
    if (start != end){
        int mid = (start + end) / 2;
        update_segmentTree(currNode*2,start,mid,index,diff);
        update_segmentTree(currNode*2+1,mid+1,end,index,diff);
    }
}

int make_segmentTree(int currNode, int start, int last){
    if(start == last) return segmentTree[currNode] = Arr[start];
    int mid = (start + last) / 2;
    int left = make_segmentTree(currNode*2,start,mid);
    int right = make_segmentTree(currNode*2 + 1, mid + 1, last);
    return segmentTree[currNode] = left + right;
}

int main(void){
    int treeHeight = int(ceil(log2(N)));
    int treeSize = (1<<(treeHeight+1));
    segmentTree.resize(treeSize);
    // Node에 1부터 하는 이유는, 그래야만 부모*2 = 왼자식, 부모*2+1 = 오른자식이 성립하기 때문
    make_segmentTree(1,0,N-1);
    return 0;
}