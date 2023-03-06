#include <vector>
#include <algorithm>
using namespace std;

// 코드 22.3 트립의 노드를 표현하는 객체의 구현
typedef int KeyType;

// 트립의 한 노드를 저장한다.
struct Node{
    //노드에 저장된 원소
    KeyType key;
    //이 노드의 우선순위
    //이 노드를 루트로하는 서브트리의 크기
    int priority, size;
    //두 자식 노드의 포인터
    Node* left; Node* right;
    // 생성자에서 난수 우선순위를 생성하고, size와 left/right를 초기화한다.
    Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL){}    
    void setLeft(Node* newLeft){left = newLeft; calcSize();}
    void setRight(Node* newRight){right = newRight; calcSize();}
    //size 멤버를 갱신한다.
    void calcSize(){
        size = 1;
        if(left) size += left->size;
        if(right) size += right->size;
    }
};

// 코드 22.4 트립에서의 노드 추가와 트립 쪼개기 연산의 구현
typedef pair<Node*, Node*> NodePair;
//root를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는 두 개의 트립으로 분리한다.
NodePair split(Node* root, KeyType key){
    if(root == NULL) return NodePair(NULL, NULL);
    //루트가 key 미만이면 오른쪽 서브트리를 재귀적으로 쪼갠다.
    if(root->key < key){
        NodePair rs = split(root->right, key);
        root->setRight(rs.first);
        return NodePair(root, rs.second);
    }
    // 루트가 key 이상이면 왼쪽 서브트리를 재귀적으로 쪼갠다.
    else{
        NodePair ls = split(root->left, key);
        root->setLeft(ls.second);
        return NodePair(root, ls.first);
    }
}
//root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과트립의 루트를 반환한다.
Node* insert(Node* root, Node* node){
    if(root==NULL) return node;
    //node가 루트를 대체해야한다. 해당 서브트리를 반으로 잘라 각각 자손으로 한다.
    if(root->priority < node->priority){
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
        
    }
    else if (node-> key < root->key){
        root->setLeft(insert(root->left, node));
    }
    else{
        root->setRight(insert(root->right, node));
    }
    return root;
}
