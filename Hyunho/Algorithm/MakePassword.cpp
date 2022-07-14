#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int L, C;
vector <char> v;
bool used[15] = {0,};
string pwd;

bool pwdcheck(){
    int cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < L;i++){
        if(pwd[i] == 'a' || pwd[i] == 'e' || pwd[i] == 'i' || pwd[i] == 'o' || pwd[i] == 'u')
            cnt1 ++;
        else cnt2 ++;
    }
    if(cnt1 >= 1 && cnt2 >= 2) return true;
    else return false;
}

void password(int num){
    if(num == L){
        if(pwdcheck()) {
            for(int i=0;i<num;i++) cout << pwd[i];
            cout << endl;}
    }
    else {
        for(int i=0; i < C; i++){
            if(used[i] == false){
                if(pwd.empty() == false){
                    if(pwd.back() < v[i]) {
                        pwd.push_back(v[i]);
                        used[i] = true;
                        password(num + 1);
                        used[i] = false;
                        pwd.pop_back();}}
                else {
                    pwd.push_back(v[i]);
                    used[i] = true;
                    password(num + 1);
                    used[i] = false;
                    pwd.pop_back();
                }
            }
        }
    }
}


int main(){
    char letter;
    cin >> L >> C;
    for(int i=0; i < C; i++){
        cin >> letter; 
        v.push_back(letter); 
    }
    sort(v.begin(), v.end());
    password(0);
}
