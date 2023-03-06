#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
int N;
int longest;

struct TreeNode{    
    int x, y, r;    
    vector<TreeNode*> children;
    TreeNode(int x, int y, int r) : x(x), y(y), r(r){}
};
TreeNode* NIL(nullptr);

struct Comparator{
    bool operator() (TreeNode* a, TreeNode* b){
        return a->r > b->r;
    }
};

// 트리의 높이 계산(largest도 매 subtree마다 계산해서 최대를 찾아줘야해서 여기서 재귀적 관리)
int height(TreeNode* root){
    vector<int> subH;
    for(int i = 0; i<root->children.size(); i++){
        subH.push_back(height(root->children[i]));
    }    
    if(subH.empty()){
        return 0;
    }

    sort(subH.rbegin(), subH.rend());
    if(subH.size() >= 2){
        longest = max(longest,subH[0] + subH[1] + 2);
    }                    
    return subH[0] + 1;
}

bool contain(TreeNode* a, TreeNode* b){
    int d = (a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y);
    // d <= r2 - r1이면 두 원 사이에 포함관계가 성립한다.
    if(d <= (a->r - b->r) * (a->r - b->r)){
        return true;
    }
    return false;
}
bool insert(TreeNode* root, TreeNode* newNode){
    // base case
    if(root == NIL){
        return false;
    }

    bool success = false;
    if(contain(root,newNode)){
        for(int i = 0; i<root->children.size(); i++){
            if(insert(root->children[i], newNode)){
                success = true;
                break;
            }
        }
        if(!success){
            root->children.push_back(newNode);
            success = true;
        }
    }
    return success;
}
int main(){
    int C;
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){
        cin >> N;        
        int x, y, r;
        // 전역변수 초기화 중요 !
        longest = 0;
        cin >> x >> y >> r;
        TreeNode* root = new TreeNode(x, y, r);
        vector<TreeNode*> nodes;
        for(int i = 1; i < N; i++){                          
            cin >> x >> y >> r;  
            nodes.push_back(new TreeNode(x,y,r));            
            
        }
        sort(nodes.begin(), nodes.end(), Comparator());
        for(int i = 0; i < N - 1; i++){
            insert(root, nodes[i]);
        }
        // 가능한 케이스
        // 1. 중간 노드를 root로 하는 subtree에서 리프 -> 리프
        // 2. root ~ 리프
        cout << max(height(root), longest) << '\n';
    }
}