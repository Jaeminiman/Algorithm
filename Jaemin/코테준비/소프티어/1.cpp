#include <iostream>
#include <string>
#include <vector>
using namespace std;
int board[64][64];
int N;
string compress(int y, int x, int size){
    int nextSize = size/2;
    int cnt_1 = 0;    
    
    for(int i = 0; i <size; i++){
        for(int j = 0; j < size; j++){
            if(board[i][j] == 1){
                cnt_1++;
            }                        
        }
    }
    if(cnt_1 == size*size){
        return "1";
    }
    else if(cnt_1 == 0){
        return "0";
    }
    
    vector<string> output;
    output.push_back("(");
    output.push_back(compress(y, x, nextSize));
    output.push_back(compress(y+nextSize, x, nextSize));
    output.push_back(compress(y, x+nextSize, nextSize));
    output.push_back(compress(y+nextSize, x+nextSize, nextSize));
    output.push_back(")");    
}
int main() {
	cin >> N;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			cin >> board[i][j];
		}		
	}
	
    string out = compress(0,0,N);
    
	
	return 1;
}