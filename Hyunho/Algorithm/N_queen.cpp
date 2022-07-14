#include <iostream>
using namespace std;
#define MAX 15

int N, count1 = 0;
int queen_y[MAX];

bool queenFind(int x) {
    
    for(int i=0; i < x; i++){
        if(queen_y[i] == queen_y[x] || abs(queen_y[i]-queen_y[x]) == abs(i - x)){
            return false;
            
        }               
    }
    return true;    
}

void queen(int x){
    if(x==N){
        count1 ++;
    }
    else{
        for(int i=0; i < N; i++){
            queen_y[x] = i;
            if(queenFind(x)){    
                queen(x+1);
            }
        }
    }    
}

int main(){
    cin >> N;
    queen(0);
    cout << count1;
}
