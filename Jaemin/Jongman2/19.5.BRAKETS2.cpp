#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
/*
입력이 몇글자 올지 모르기 때문에, 줄 입력을 받는 것이 타당하다.

*/
using namespace std;
int C;
stack<char> st;
map<char, char> braketMap; 
const string lBraket("({[");

int main(){
    braketMap.insert(pair<char, char> ('(', ')'));
    braketMap.insert(pair<char, char> ('{', '}'));
    braketMap.insert(pair<char, char> ('[', ']'));

    cin>>C;
    string line;    
    getline(cin, line);

    for(int epoch = 0; epoch < C; epoch++){
        // initialize
        while(!st.empty()) st.pop();

        getline(cin, line);                                                
        string output = "YES";
        for(char x : line){            
            // 새로 들어온 x가 ( { [ 중 하나인 경우
            if(lBraket.find(x) != -1){                
                st.push(x);                
            }
            // 새로 들어온 x가 ) } ] 중 하나인 경우
            else{
                if(!st.empty()){
                    char last = st.top();
                    if(braketMap[last] == x){
                    st.pop();
                    }                                
                    else{
                        output = "No";
                        break;
                    }
                }
                // 예외. 앞에 아무것도 없는 경우
                else{
                    output = "NO";
                    break;
                }
                
                
            }            
        }
        // 개행이 다 안닫힌채로 끝난 경우 fail
        if(!st.empty()){
            output = "NO";
        }
        cout << output << '\n';        
    }
}