/*
현재 board판 상태를 나타내는 인자는 정수형으로 바꾸게 되면 2^25이다. 이는 너무 큰 숫자이다. 90도 돌리는 과정 4번, 위아래 2번, 오른쪽위 2번, 대각선 2번으로 총합 2^5을 줄일 수 있을 것이다. 그럼 2^20 = 2MB이니까 할만하지 않을까?
이거 비트마스크로 받으면 사실 정수형 하나에 해당되는 메모리밖에 안된다. 가능함!

ㄱ자 4개, ㅣ자 2개의 경우를 왼쪽위부터 넣어보는 식으로하면, 매 호출마다 6 * 25이다. 시간 복잡도는 어느정도 된다쳐도 메모리가 부족할 것이 예상된다.

*/

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> moves;
char cache[1<<25];

// 짧은 코드의 경우 컴파일러가 해당 함수가 호출된 부분의 내용을 그대로 처리하는 코드로 바꿔버린다.
// 현대 컴파일러는 함수를 자동으로 인라인화하여 성능을 향상시키는 tool을 적용하므로, 대부분의 경우 이를 명시할 필요는 없다.
// 비트마스크에 접근하는 idx 반환
inline int cell(int y, int x){
    return 1 << (y*5 + x);
}

// 현재 게임판 상태가 board일 때 현재 차례인 사람이 승리할지 여부를 반환한다.
// (y,x)칸에 블록이 있다. <=> y * 5 + x번 비트가 켜져있다.
char play(int board){
    char& ret = cache[board];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = 0; i < moves.size(); i++){
        // board에 moves에서 뽑은 블록을 놓을 수 있는 경우
        if((board & moves[i]) == 0){
            // 다음 것이 0이라면 <=> 다음 것에 놓을 수 있는게 없다면 (현재의 내가 승리)
            // 무조건 승리하는 경우가 하나 이상 있기 때문에 더 볼것도 없이 승리.
            if(!play(board | moves[i])){
                ret = 1;
                break;
            }
        }
    }
    return ret;
}
int boardSetting(){
    int board = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j< 5; j++){
            char ch;
            cin >> ch;
            if(ch == '#'){
                board += cell(i,j);
            }
        }
    }
    return board;
}


// 게임판에 놓을 수 있는 블록들의 위치를 미리 계산한다.
void precalc(){
    // 세 칸짜리 L자 모양 블록들을 계산한다.
    for(int y = 0; y < 4; y++){
        for(int x=0; x < 4; x++){
            vector<int> cells;
            for(int dy = 0; dy < 2; dy++){
                for(int dx = 0; dx < 2; dx++){
                    cells.push_back(cell(y + dy, x+dx));
                }
            }
            int square = cells[0] + cells[1] + cells[2] + cells[3];
            for(int i = 0; i <4; i++){
                moves.push_back(square - cells[i]);
            }
        }
    }
    // 두 칸짜리 블록들을 계산한다.
    // Tip. cell 함수에 범위를 벗어난 경우 -INF 값을 반환하게 하여 예외처리 할 수도 있겠지만
    // i, j 위치를 바꿔서 이런식으로 연산할 수도 있다.
    for(int i = 0; i < 5; i++){
        for(int j =0; j < 4; j++){
            moves.push_back(cell(i,j) + cell(i,j+1));
            moves.push_back(cell(j,i) + cell(j+1,i));
        }
    }
}
int main(){
    int C;
    cin >> C;
    memset(cache,-1,sizeof(cache));
    precalc();

    for(int epoch = 0; epoch < C; epoch++){
        
        int board = boardSetting();
        if(play(board)){
            cout << "WINNING" << '\n';
        }
        else{
            cout << "LOSING" << '\n';
        }

    }

}

