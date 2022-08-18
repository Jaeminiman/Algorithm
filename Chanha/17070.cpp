#include <iostream>

using namespace std;

int N;
int answer = 0;
int home[18][18]{};
int state = 0; //0: 가로, 1: 세로 2: 대각선
int currrow = 1; int currcol = 2; //출발점 (1,2)

void Solution();

void moveright()
{
    currcol++;
    int currstate = state;
    if(state == 2) state = 0;
    Solution();
    state = currstate;
    currcol--;
}
void movedown()
{
    currrow++;
    int currstate = state;
    if(state == 2) state = 1;
    Solution();
    state = currstate;
    currrow--;
}
void moverd()
{
    currrow++; currcol++;
    int currstate = state;
    state = 2;
    Solution();
    state = currstate;
    currrow--; currcol--;
}

void Solution()
{
    if(currrow == N && currcol == N) 
    {
        answer++;
        return;
    }
    bool rempty = !home[currrow][currcol+1];    
    bool dempty = !home[currrow+1][currcol];    
    bool rdempty = !home[currrow+1][currcol+1]; 
    if(rempty && state != 1) moveright();       //오른쪽 비어있고, 세로모양 아닐 시
    if(dempty && state != 0) movedown();        //아래쪽 비어있고, 가로모양 아닐 시
    if(rempty && dempty && rdempty) moverd();   //세칸 모두 비어있을 시

    return;
}


int main()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            int n; 
            cin >> n;
            if(n == 1) home[i+1][j+1] = 1;
        }
    }
    for(int i = 0; i < N+2; i++)
    {
        for(int j = 0; j < N+2; j++)
        {
            if(i == 0 || j == 0 || i == N+1 || j == N+1) home[i][j] = 1;
        }
    }
    Solution();

    cout << answer << endl;
}