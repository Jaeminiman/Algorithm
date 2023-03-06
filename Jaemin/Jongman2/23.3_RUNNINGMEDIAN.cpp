#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define MOD 20090711

// 난수 생성기 (선형 합동 난수 생성기)
struct RNG{
    int seed, a, b;
    RNG(int numA, int numB) : a(numA), b(numB), seed(1983) {}
    
    int next(){
        int ret = seed;
        seed = ((seed * (long long) a) + b)%MOD;
        return ret;
    }
};
void repair(priority_queue<int, vector<int>, greater<int>>& minheap, priority_queue<int>& maxheap){
    int a = minheap.top(), b = maxheap.top();
    if(a < b){
        minheap.pop(), maxheap.pop();
        minheap.push(b), maxheap.push(a);        
    }
}
int main(){
    int C;
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){
        int N, a, b;
        cin >> N >> a >> b;        
        priority_queue<int> maxheap;
        priority_queue<int,vector<int>, greater<int>> minheap;                
        
        RNG rng(a,b);
        int sum = 0;
        for(int i = 0; i < N; i++){                        
            if(i%2==1){
                minheap.push(rng.next());
            }
            else{
                maxheap.push(rng.next());
            }

            if(!minheap.empty() && !maxheap.empty()){
                repair(minheap, maxheap);
            }                        
            sum = (sum + maxheap.top())%MOD;            
        }
        cout << sum << '\n';
    }
}