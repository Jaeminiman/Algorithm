/*
set으로 관리하면 편할 것 같지만, idx로 접근 해야할 때(순위로 접근하는 경우) iterator을 처음부터 돌려야 하는
문제가 있어 vector로 container을 관리한 후 로직으로 이분 탐색을 구현하여 보관을 빠르게 한다.

시간 초과 문제 : vector에서 erase는 맨 앞 제거시 및 추가시 O(N)의 시간이 소요된다. 왜냐하면 그것을 제거하고 인덱스를 땡기는 과정이 수반되기 때문이다.
그래서 삭제를 지속적으로 하기 위해서는 
1) list(doubly linked list)으로 관리하는게 유리하고, idx접근은 노드 연결만 바꿔주면 되어 O(1)이 된다.
다만 단점은 head나 tail만을 기억하기 때문에 idx로 접근시 O(N)이 수반될 수 있다. 그래서 불리한 선택이 됨.
2) deque(덱 : doubly ended queue)
idx 접근은 O(1)이고, 맨 앞에 원소 추가/제거 작업 또한 O(1)이다. 임의의 위치 원소를 제거/추가하는 작업은 벡터처럼 O(n)으로 수행가능하다. 다만 벡터보단 더 빠르다.
다만 단점은 연속적으로 메모리를 관리하지 않아서, vector에 비하여 메모리를 많이 희생한다. (약 8배)
덱의 구조는 앞 뒤로 공간을 비워두어 vector의 삽입 및 삭제의 단점을 보완한다.
뿐만 아니라 덱은 작은 크기의 Block으로 원소를 관리하여 할당된 메모리를 넘어설 경우 새롭게 Block을 할당받기만 하면 되는데 반해,
Vector은 기존의 원소를 모두 복사해야하는 작업이 필요하여 시간이 더 오래 걸린다.

컨테이너 선택 기준
- 일반적으로는 벡터를 사용
- 맨 끝이 아닌 중간에 원소들을 추가하거나 제거하는 일이 많고, 원소들을 순차적으로만 접근한다면 리스트 사용
- 맨 처음과 끝 모두에 원소들을 추가하는 작업을 많이하는 경우 덱을 사용.
*/
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int N;

deque<int> container;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int A, B, C;
    for(int epoch = 0; epoch < N; epoch++){
        cin >> A;
        if(A == 1){
            cin >> B;
            cout << container[B-1] << '\n';
            container.erase(container.begin() + B - 1);
        }
        else{
            cin >> B >> C;

            auto it = lower_bound(container.begin(),container.end(),B);
            if(C > 0){

                container.insert(it,C,B);
                
            }
            else if(C < 0){    
                container.erase(it,it-C); 
            }
            else{
                cout << "Error in Input" << '\n';
            }
        }
    }

    return 0;
}