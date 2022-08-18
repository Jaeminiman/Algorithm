/*
자료구조 : 세그먼트 트리(이진트리)
(2번요청)자료가 지속적으로 변하는 요청이 있는 상황에서 (1번요청)구간합을 지속적으로 구하는 문제의 경우 M의 요청이 있고 N크기의 배열이라면
O(NM)의 시간이 걸린다. 이를 세그먼트 트리로 관리하면 O(logN)의 시간으로 관리할 수 있게된다.

리프노드(자식이 없는 말단 노드)는 배열의 값 그 자체를, 그게 아닌 노드에는 해당 자식들의 합을 저장하는 형태를 이룬다.

크기가 N인 배열이 존재할 때
1. 트리의 높이 = ceil(log_2(N)) // ceil -> 올림함수
2. 세그먼트 트리의 크기(배열의 크기) = (1<<(트리의 높이 + 1))

참고 : https://yabmoons.tistory.com/431

- 시간 초과 이슈
입출력이 10만번 있는 예제이므로, 빠른 입출력이 필수적인 역할을 한다.
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
vector<int> segmentTree;
int N;
int candyBox[1000001];
#define END 1000000

// O(log(10^6)) = 20
int find_ByRank(int currNode, int start, int end, int rank){
    // 기저 사례
    if(start==end) return end;

    int mid = (start + end) / 2;

    // 경우 1. 앞 구간합보다(left sum) rank가 큰 경우 -> 뒷 구간에 존재하는데, leftSum을 더한 값과의 비교를 해야한다. 즉, rank에서 leftSum을 빼줘야함.
    if(segmentTree[currNode*2] < rank){
        return find_ByRank(currNode*2+1, mid+1, end, rank - segmentTree[currNode*2]);
    }

    // 경우 2. 앞 구간합 그 중간 어딘가에 있는 경우 -> 더 깊이 탐색해야함.
    else{
        return find_ByRank(currNode*2,start,mid,rank);
    }
}

// O(log(10^6)) = 20
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

// O(NlogN)
int main(void){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    // 세그먼트 트리 구조 생성
    int treeHeight = int(ceil(log2(END)));
    int treeSize = (1<<(treeHeight+1));
    segmentTree.resize(treeSize);

    int A, B, C;
    for(int epoch = 0; epoch < N; epoch++){
        cin >> A;
        if(A == 1){
            cin >> B;
            int index = find_ByRank(1,0,END,B);
            update_segmentTree(1,0,END,index,-1);
            candyBox[index]--;
            cout << index << '\n';
        }
        else{
            cin >> B >> C;
            update_segmentTree(1,0,END,B,C);
            candyBox[B] += C;
        }
    }
    
    return 0;
}