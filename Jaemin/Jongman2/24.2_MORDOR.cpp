#include <vector>
#include <iostream>
#include <math.h>
const int MAX = 987654321;
const int MIN = -1;
using namespace std;
struct Node{
    int maxValue, minValue;
};
// RangeQuery
struct RQ{
    int n;
    vector<Node> rangeValue;    
    RQ(const vector<int>& array){
        n = array.size();
        rangeValue.resize(4 * n);        
        init(array, 1, 0, n-1);
    }
    Node merge(const Node& a, const Node& b){
        Node ret;
        ret.maxValue = max(a.maxValue, b.maxValue);
        ret.minValue = min(a.minValue, b.minValue);
        return ret;
    }
    Node init(const vector<int>& array, int node, int left, int right){        
        if(left == right){            
            Node ret;
            ret.maxValue = array[right];
            ret.minValue = array[right];            
            return rangeValue[node] = ret;
        }
        int mid = (left + right) / 2;
        return rangeValue[node] = merge(init(array, node*2, left, mid), init(array,node*2 + 1, mid + 1, right));
    }
    Node difficulty(int node, int nodeLeft, int nodeRight, int left, int right){
        Node ret;
        // 범위 벗어난 경우
        if(nodeLeft > right || nodeRight < left){
            ret.maxValue = MIN;
            ret.minValue = MAX;
            return ret;
        }
        // 범위에 완전 포함된 경우
        if(nodeRight <= right && nodeLeft >= left){
            return rangeValue[node];
        }
        // 그 밖의 경우        
        int mid = (nodeLeft + nodeRight) / 2;
        ret = merge(difficulty(node*2, nodeLeft, mid, left, right), difficulty(node*2 + 1, mid + 1, nodeRight, left,right));
        return ret;
    }
    int difficulty(int left, int right){
        return difficulty(1,0,n-1,left,right).maxValue - difficulty(1,0,n-1,left,right).minValue;
    }
};


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int C;
    cin >> C;
    while(C--){
        int N, Q;
        cin >> N >> Q;
        vector<int> array;
        while(N--){
            int x;
            cin >> x;
            array.push_back(x); 
        }
        RQ rq(array);
        int ret = 0;
        while(Q--){
            int a, b;
            cin >> a >> b;
            ret = rq.difficulty(a, b);
            cout << ret << '\n';
        }
        
    }
}