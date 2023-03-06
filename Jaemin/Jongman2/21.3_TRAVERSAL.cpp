#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;

struct TreeNode{
    int num;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int num) : num(num){}
};

TreeNode* NIL(nullptr);

void printPostOrder(TreeNode* root){
    if(root == NIL){
        return;
    }
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->num << " ";
}
TreeNode* getTree(const vector<int> pre, const vector<int> in){                
    if(pre.size() == 0){
        return NIL;
    }
    
    TreeNode* root = new TreeNode(pre[0]);
    auto idx = find(in.begin(), in.end(), root->num);
    vector<int> subIn1 = vector<int>(in.begin(), idx);
    vector<int> subIn2 = vector<int>(idx + 1, in.end());
    vector<int> subPre1 = vector<int>(pre.begin() + 1, pre.begin() + 1 + subIn1.size());
    vector<int> subPre2 = vector<int>(pre.begin() + subPre1.size() + 1, pre.end());

    root->left = getTree(subPre1, subIn1);
    root->right = getTree(subPre2, subIn2);
    return root;
}
int main(){
    int C;
    cin >> C;
    for(int epoch = 0 ; epoch < C; epoch ++){        
        cin >> N;
        vector<int> pre;
        vector<int> in;
        for(int i = 0; i < N; i++){
            int x;            
            cin >> x;
            pre.push_back(x);
        }

        for(int i = 0; i < N; i++){
            int x;            
            cin >> x;
            in.push_back(x);
        }

        TreeNode* root = getTree(pre, in);
        printPostOrder(root);        
    }
}