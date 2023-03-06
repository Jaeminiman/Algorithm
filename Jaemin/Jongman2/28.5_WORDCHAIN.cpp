#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int N;
vector<vector<int>> adj;
vector<int> order;
vector<int> inbound;
vector<int> outbound;
vector<string> word[26][26];

void getEulerCircuit(int here){
    for(int there = 0; there < 26; there++){
        while(adj[here][there]>0){
            adj[here][there]--;
            getEulerCircuit(there);
        }
    }
    order.push_back(here);
}
// Euler Circuit or Trail인지 check
bool checkEuler(){            
    int u = 0, v = 0;
    for(int i = 0; i < 26;i++){
        int delta = inbound[i] - outbound[i];        
        if(abs(delta) >= 2){
            return false;
        }
        if(delta==1){
            v++;
        }
        if(delta==-1){
            u++;
        }
    }        
    return (v==1 && u==1) || (v==0 && u==0);        
}
// 오일러 있는 상태에서의 u 구하기
int getFirstU(){
    for(int i = 0; i < 26; i++){
        if(outbound[i] - inbound[i] == 1){
            return i;
        }
    }
    for(int i = 0; i < 26; i++){
        if(outbound[i]>0){
            return i;
        }
    }
}

void edgeSetting(const vector<string>& s){
    for(int i = 0; i < N; i++){
        int u = s[i].at(0) - 'a';
        int v = s[i].at(s[i].size()-1) - 'a';
        word[u][v].push_back(s[i]);
        outbound[u]++;
        inbound[v]++;
        adj[u][v]++;
    }      
}
void init(){
    adj = vector<vector<int>>(26, vector<int>(26,0));        
    order.clear();        
    inbound = vector<int>(26, 0);
    outbound = vector<int>(26, 0);
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            word[i][j].clear();
        }
    }
}
int main(){
    int C;
    cin >> C;
    while(C--){
        cin >> N;
        init();
        
        // input string
        vector<string> s;
        for(int i = 0; i < N; i++){
            string x;
            cin >> x;
            s.push_back(x);
        }

        edgeSetting(s);                          
        
        // 오일러 서킷이나 트레일이 존재하는 경우
        if(checkEuler()){      
            int firstU = getFirstU();  

            getEulerCircuit(firstU);
            reverse(order.begin(), order.end());

            for(int i = 0; i < order.size() - 1; i++){
                int u = order[i]; int v = order[i+1];
                cout << word[u][v].back() << ' ';
                word[u][v].pop_back();
            }            
            cout << '\n';        
        }
        
        else{
            cout << "IMPOSSIBLE" << '\n';
        }

    }
}