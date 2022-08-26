코드 9.20 틱택토를 해결하는 동적 계획법 알고리즘
//turn이 한 줄을 만들었는지를 반환한다.
bool isFinished(const vector<string>& board, char turn);
//틱택토 게임판이 주어질 때 [0,19682] 범위의 정수로 변환한다.
int bijection(const vector<string>& board){
    int ret = 0;
    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            ret = ret*3;
            if(board[y][x] == 'o') ++ret;
            else if(board[y][x] == 'x') ret+=2;
        }
    }
}
// cache[]는 -2로 초기화한다. 3^9 = 19863
int cache[19863];
// 내가 이길 수 있으면 1을, 비길 수 있으면 0을, 지면 -1을 리턴한다.
int canWin(vector<string>& board, char turn){
    // 기저 사례 : 마지막에 상대가 둬서 한 줄이 만들어진 경우
    if(isFinished(board, 'o' + 'x' - turn)) return -1;
    int& ret = cache[bijection(board)];
    if (ret != -2) return ret;
    // 모든 반환 값의 min을 취하자.
    int minValue = 2;
    for(int y= 0; y<3; y++){
        for(int x=0; x<3; x++){
            if(board[y][x] == '.'){
                board[y][x] = turn;
                minValue = min(minValue,canWin(board,'o' + 'x' - turn));
                board[y][x] = '.';
            }
        }
    }
    // 더 이상 둘데가 없거나, 어떻게 해도 비기는 것이 최선인 경우
    if(minValue == 2 || minValue == 0) return ret = 0;
    // 최선이 상대가 이기는 거면 난 무조건 지고, 상대가 지는 거라면 나는 이긴다.
    return ret = -minValue;
}