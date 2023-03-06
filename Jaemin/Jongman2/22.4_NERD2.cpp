#include <iostream>
#include <map>

using namespace std;
int n;
map<int, int> nerd;
void insertNERD(int p, int q){
    
    auto it = nerd.lower_bound(p);
    // 새로운 점(p,q)보다 왼쪽에 있는 점이 없는 경우, 삭제할 nerd가 없다.
    if(it != nerd.begin()) {
        it--;
        // 삭제 작업
        // 기존 nerd가 새로운 점(p,q)에 의해 지배당하는 경우
        // 새로운 점보다 p가 작은거나 같은 녀석 중 q값이 작거나 같은 경우
        while(true){
            // 더이상 삭제할 필요가 없는 경우, 종료
            if(it->second > q) break;

            // 삭제될 후보 node가 하나만 남은 경우, 삭제하고 종료            
            if(it == nerd.begin()){
                nerd.erase(it);
                break;
            }

            map<int,int>::iterator jt = it;
            jt--;
            nerd.erase(it);
            it = jt;            
        }
    }                
    nerd.insert({p,q});    
    
    return;
}

// 의외로 얘가 시간을 지배하는 것 O(log(n))
bool checkNERD(int p, int q){
    auto it =  nerd.lower_bound(p);
    if(it!= nerd.end()){
        return q > it->second;
    }    
    return true;
    
    
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int C;
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){        
        cin >> n;
        int sum = 0;
        nerd.clear();

        for(int i = 0; i < n; i++){
            int p, q;
            cin >> p >> q;            
            if(checkNERD(p, q)){                
                insertNERD(p,q);
            }            
            sum += nerd.size();
            
        }
        cout << sum << '\n';
    }

}