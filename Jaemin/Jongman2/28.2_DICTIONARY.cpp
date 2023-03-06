#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> order;

void errorController(){
    cout << "INVALID HYPOTHESIS" << '\n';    
}

void dfs(int here){        
    visited[here] = true;
    for(int there = 0; there < adj[here].size(); there++){                
        if(!visited[there] && adj[here][there] == 1){
            dfs(there);
        }
    }                    
    order.push_back(here);    
}

void dfsAll(){    
    for(int i = adj.size() - 1; i>=0; i--){
        if(!visited[i]){            
            dfs(i);
        }        
    }    
}
int toNumber(char ch){
    return ch - 'a';
}
char toChar(int num){
    return num + 'a';
}
void makeDAG(int n){
string prev, here;
    // 알파벳 DAG 형성
    for(int i = 0; i < n; i++){            
        cin >> here;
        if(i == 0){
            prev = here; continue;
        }
        int k = 0;
        while(k < prev.size() && k < here.size()){
            char a = prev[k]; char b = here[k];
            if(a != b){
                adj[toNumber(a)][toNumber(b)] = 1;
                break;
            }                
            k++;
        }               
        prev = here;     
    }
}
bool cycleCheck(){
    for(int i = 0; i < order.size(); i++){
        for(int j = i + 1 ; j < order.size(); j++){
            if(adj[order[j]][order[i]]){
                errorController();
                return false;
            }            
        }
    }
    return true;
}
int main(){
    int C;
    cin >> C;    
    while(C--){
        adj = vector<vector<int>>(26, vector<int>(26,0));
        visited = vector<bool>(26, 0); 
        order.clear();         

        int n;
        cin >> n;

        makeDAG(n);

        // 위상 정렬                            
        dfsAll();
        reverse(order.begin(), order.end());
        if(cycleCheck()){            
            for(int i = 0; i < order.size(); i++){
                cout << toChar(order[i]);                        
            } 
        }        
        
        
        cout << "\n";
    }
}