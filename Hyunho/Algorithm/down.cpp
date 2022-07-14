#include <iostream>

using namespace std;

int map[500][500];
int dp[500][500];
int m, n;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int downward(int y, int x){
    if(y == m-1 && x == n-1) return dp[y][x] = 1;
    if(dp[y][x] != -1) return dp[y][x];

    for(int i=0;i<4;i++){
        if(map[y+dy[i]][x+dx[i]] < map[y][x] && y+dy[i] > -1 && x+dx[i] > -1 && y+dy[i] < m && x+dx[i] < n){
            dp[y][x] += downward(y+dy[i],x+dx[i]);
        }
    }

    if(dp[y][x] == -1) return dp[y][x] = 0;
    else return dp[y][x] += 1;
}

int main(){
    cin >> m >> n;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin >> map[i][j];
            dp[i][j] = -1; 
        }
    }
    cout << downward(0,0) << endl;
}