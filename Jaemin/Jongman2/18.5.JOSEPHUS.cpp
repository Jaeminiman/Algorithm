#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>
using namespace std;
int C, N, K;
int main(){
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){
        cin >> N >> K;
        list<int> l;
        for(int i = 1; i <= N; i++){
            l.push_back(i);
        }
        
        // O(N) 방지를 위하여 따로 관리
        int size = l.size();
        auto iter = l.begin();        
        while(size > 2){
            l.erase(iter);
            size--;
            if(iter == l.end()){
                iter = l.begin();
            }

            // list의 iter은 ++연산밖에 안되어서 이렇게 구현할수밖에..
            for(int i = 0; i < K; i++){
                iter++;
                if(iter == l.end()){
                    iter = l.begin();
                }
            }
        }        
        int maxi = max(* l.begin(), * (++l.begin()));
        int mini = min(*l.begin(), *(++l.begin()));
        cout << mini << " " << maxi << '\n';
    }
    


}