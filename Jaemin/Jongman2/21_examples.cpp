#include <vector>
#include <string>
#include <iostream>
using namespace std;

// 코드 21.1 트리의 노드를 표현하는 객체의 구현
struct TreeNode{
    string label; // 저장할 자료(문자열일 필요 없다)
    TreeNode* parent; // 부모 노드를 가리키는 포인터
    vector<TreeNode*> children; // 자손 노드를 가리키는 포인터 배열
};

// 코드 21.2 트리를 순회하며 모든 노드에 포함된 값 출력하기(재귀)
void printLabels(TreeNode* root){
    cout << root->label << endl;
    // 각 자손들을 루트로 하는 서브트리에 포함된 값들을 재귀적으로 호출한다.
    for(int i = 0; i < root->children.size(); i++){
        printLabels(root->children[i]);
    }
}

// 코드 21.3 순회를 이용해 트리의 높이를 계산하기
// root를 루트로 하는 트리의 높이를 구한다(재귀)
int height(TreeNode* root){
    int h = 0;
    for(int i = 0; root->children.size(); i++){
        h = max(h, height(root->children[i]));
    }
    return h;
}
