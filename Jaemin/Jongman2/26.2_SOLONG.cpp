#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
int N, M;
const int ALPHABETS = 26;

int toNumber(char ch){
    return ch - 'A';
}
struct TrieNode{
    TrieNode* children[ALPHABETS];
    // 이 노드에서 종료하는 문자열의 번호. 없으면 -1
    int terminal;
    int rec;
    TrieNode():terminal(-1), rec(-1){
        memset(children, 0, sizeof(children));
    }
    void insert(const char* key, int keyID){
        // 사전순배열을 구현하는게 복잡해.. 그냥 입력이 정렬되어있다고 하자
        if(rec==-1){
            rec = keyID;
        }
        if(*key == 0){
            terminal = keyID;
            return;
        }        
        int next = toNumber(*key);
        
        if(children[next] == NULL){
            children[next] = new TrieNode();
        }
        children[next]->insert(key+1, keyID);
    }
    TrieNode* find(const char * key){
        if(*key == 0) return this;
        int next = toNumber(*key);
        if(children[next] == NULL) return NULL;
        return children[next]->find(key+1);
    }
    // key 찾기까지 걸리는 최소 횟수
    int type(const char* key, int keyID){
        if(*key==0){            
            return 0;
        }        
        if(rec == keyID){
            return 1;
        }
        int next = toNumber(*key);                                                
        
        return 1 + children[next]->type(key+1, keyID);
    }
};
// 사전을 나타내는 트라이가 주어질 때, 단어 word를 타이핑하는데
// 몇 번이나 키를 눌러야 하느니 계산한다.
int countKeys(TrieNode* trie, const char* word){
    // 이 문자열이 사전에 있는지 확인하고, 있다면 번호를 구한다.
    TrieNode* node = trie->find(word);
    // leaf 노드의 중간과정에 잇으면 NULL이 아니다. 그때는 terminal로 구분!
    if(node == NULL || node->terminal == -1){
        return strlen(word);
    }
    else{
        return trie->type(word, node->terminal);
    }
}

// 입력에 주어지는 단어들을 정렬해서 트라이로 변환한다.
TrieNode* readInput(int words){
    // 단어들을 출현 빈도의 내림차순,, 단어의 오름차순으로 정렬한다.
    vector<pair<int,string>> input;
    for(int i = 0; i< words; i++){
        string x;
        int f;
        cin >> x >> f;
        input.push_back({-f, x});        
    }
    sort(input.begin(), input.end());
    TrieNode* trie = new TrieNode();
    for(int i = 0; i < words; i++){
        trie->insert(input[i].second.c_str(), i);
    }

    trie->rec = -1;
    return trie;
}

int main(){
    int C;
    cin >> C;
    while(C--){
        cin >> N >> M;        
        TrieNode* trie = readInput(N);
        int cnt = 0;
        for(int i = 0; i < M; i++){
            string x;
            cin >> x;
            cnt += countKeys(trie,x.c_str()) + 1;
        }
        cout << cnt-1 << '\n';
    }
}