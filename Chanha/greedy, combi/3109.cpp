#include <iostream>
#include <vector>

using namespace std;

int R; int C;
int gridT[10002][501]{}; //0: empty, 1: wall, 2: pipe
int gridB[10002][501]{};
int fromtop = 0;
int frombot = 0;

void input()
{
    cin >> R >> C;
    for(int i = 0; i <= R+1; i++)
    {
        for(int j = 0; j <= C; j++)
        {
            if(i == 0 || j == 0 || i == R+1) 
            {
                gridT[i][j] = 1;
                gridB[i][j] = 1;
            }
            else
            {
                char x; 
                cin >> x;
                if(x == '.') {gridT[i][j] = 0; gridB[i][j] = 0;}
                if(x == 'x') {gridT[i][j] = 1; gridB[i][j] = 1;}
            }
        }
    }
}
bool nextT(int curry, int currx)
{
    gridT[curry][currx] = 2;
    if(currx == C) return true;
    for(int j = -1; j <= 1; j++)
    {
        if(gridT[curry+j][currx+1] == 0)
        {
            if(nextT(curry+j, currx+1)) return true;
        }
    }
    //gridT[curry][currx] = 0;
    return false;
}
bool nextB(int curry, int currx)
{
    gridB[curry][currx] = 2;
    if(currx == C) return true;
    for(int j = -1; j <= 1; j++)
    {
        if(gridB[curry+j][currx+1] == 0)
        {
            if(nextT(curry+j, currx+1)) return true;
        }
    }
    //gridB[curry][currx] = 0;
    return false;
}
void Solution()
{
    for(int i = 1; i <= R; i++) 
    { 
        if(nextT(i, 1)) fromtop++;
        
    }
    for(int i = R; i >= 1; i--) 
    {

        if(nextB(i, 1)) frombot++;
    }
    cout << max(fromtop, frombot) << endl;
}

int main()
{
    input();
    Solution();
}