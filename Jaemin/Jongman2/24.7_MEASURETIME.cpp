#include <iostream>
#include <vector>

using namespace std;
const int MAX_A =  1000001;

struct FenwickTree{
    vector<int> tree;    
    
    FenwickTree(){
        tree.resize(MAX_A);
    }

    int sum(int pos){
        int ret = 0;        
        // pos++; (pos 위치를 포함하지 않아야함.)
        while(pos > 0){
            ret += tree[pos];
            pos = pos & (pos - 1);
        }
        return ret;
    }
    // A[pos]에 val을 더한다.
    void add(int pos, int val){        
        pos++;
        while(pos <= tree.size()){            
            tree[pos] += val;
            pos = pos + (pos & -pos);
        }
    }
};

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int C;
    cin >> C;
    while(C--){
        int N;
        cin >> N;

        FenwickTree* fwTree = new FenwickTree();

        int ret = 0;
        for(int i = 0; i < N; i++){
            int a;
            cin >> a;
            // 부분합을 적절히 활용하기 위해 position 정의를 뒤집음. 0<=a <= 1,000,000 ==> 0<=pos <= 1,000,000
            int pos = MAX_A - a;
            fwTree->add(pos,1);            
            ret += fwTree->sum(pos);            
        }
        delete fwTree;
        cout << ret << '\n';
    }
}