#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
const int MAX_N = 10;
int board[MAX_N+2][MAX_N+2]; // Zero padding
const int direction[4][2] ={
    {1,0},{-1,0},{0,1},{0,-1}
};
int DFS(int y, int x){
    if(board[y][x] == 0){
        return 0;
    }

    int result = 1;
    board[y][x] = 0;
    for(int d = 0; d < 4; d++){
        int nextY = direction[d][0] + y;
        int nextX = direction[d][1] + x;
        
        result += DFS(nextY,nextX);
    }
    return result;

}
int main() {
	
    cin >> N;
    
	for (int i = 0; i < N + 2; i++) {
		for (int j = 0; j < N + 2; j++) {            
            if(i == 0 || j ==0 || i == N+1 || j == N+1){
                board[i][j] = 0;
            }
            else{
                cin >> board[i][j];
            }
			
		}
	}
    vector<int> result;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            int output = DFS(i,j);
            if(output != 0){
                result.push_back(output);
            }      
        }
    }
    cout << result.size() << '\n';
    sort(result.begin(), result.end());
	for(int i : result){
        cout << i << ' ';
    }
    
	
	return 0;
}