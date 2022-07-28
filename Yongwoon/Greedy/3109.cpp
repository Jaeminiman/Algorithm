// Idea : 두 column씩 볼 때 놓일 수 있는 파이프의 최소 값이 정답
#include <iostream>
#include <algorithm>
using namespace std;
int R; int C;
int space[10002][502];
bool check[10002][502];
int res = 0;
int del_row[3] = {-1, 0, 1};

bool solve(int row, int col){
    check[row][col] = true;
    if (col == C){
        res++;
        return true;
    }

    for (int i = 0 ; i < 3; i++){
        int next_row = del_row[i] + row;
        int next_col = col + 1;

        if (check[next_row][next_col] || space[next_row][next_col] == 0){
            continue;
        }

        if(solve(next_row, next_col)) {return true;}
    }
    return false;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;
    char tmp;
    fill(&space[0][0], &space[10000][501], 0);
    fill(&check[0][0], &check[10000][501], false);

    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            cin >> tmp;
            if(tmp == '.'){
                space[i][j] = 1;
            }
        }
    }

    for(int i = 1; i <= R; i++){
        solve(i,1);
    }


    cout << res << endl;
    return 0;
}