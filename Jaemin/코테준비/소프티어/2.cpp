#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <string>
using namespace std;
int N;
int K;
vector<int> idx;
vector<string> output;
queue<int> stage_nodes;
string make_string(int num, int stage){
    string out = "1";
    for(int i = 1; i<= stage; i++){
        int digit = num/int(pow(K,stage-i));
        num %= int(pow(K,stage-i));
        out.push_back(digit + '0');
    }
    
    return out;
}
int main() {
	
    cin >> N;
	cin >> K;
    char x;
    for(int i = 1; i <= (int) pow(K,N-1) * 2 - 1; i++){
        cin >> x;
        if(x!=','){
            stage_nodes.push(x - '0');
        }        
        
    }
    vector<int> tmp;
    for(int stage = N-1; stage >= 1; stage--){
        
        for(int i = 1; i <= (int) pow(K,stage - 1); i++){
            int cnt = 0;
            tmp.clear();
            for(int j = 0; j <K; j++){                
                int x = stage_nodes.front();
                stage_nodes.pop();
                if(x == 1){
                    cnt += 1;
                }            
                else{
                    tmp.push_back((i-1)*K + j);
                }        
            }        
            if(cnt >= 1){
                for(int idx : tmp){                    
                    string out = make_string(idx,stage);
                    output.push_back(out);
                }
                stage_nodes.push(1);
            }
            else{
                stage_nodes.push(0);
            }
        } 
    }
    sort(output.begin(), output.end());
    for(int i = 0; i < output.size() ; i++){
        cout << output[i] << '\n';
    }    
    return 0;
}