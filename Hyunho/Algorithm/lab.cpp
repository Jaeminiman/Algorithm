#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
int v[8][8], temp[8][8];
vector<int> v2;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int maximum = 0;

void copy()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            temp[i][j] = v[i][j];
        }
    }
}

void maxcount()
{
    copy();
    queue<pair<int, int> > virus;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (temp[i][j] == 2)
                virus.push(make_pair(j, i));
        }
    }

    while (!virus.empty())
    {
        int x = virus.front().first;
        int y = virus.front().second;
        virus.pop();

        for (int i = 0; i < 4; i++)
        {
            int nextx = x + dx[i];
            int nexty = y + dy[i];
            if (nextx > -1 && nexty > -1 && nextx < M && nexty < N && temp[nexty][nextx] == 0)
            {
                virus.push(make_pair(nextx, nexty));
                temp[nexty][nextx] = 2;
            }
        }
    }

    //////
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (temp[i][j] == 0)
                cnt++;
        }
    }
    maximum = max(cnt, maximum);
}

void makeblock(int block, int y, int x)
{
    if (block == 3)
    {
        maxcount();
    }
    else
    {
        for (int i = y; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (v[i][j] == 0)
                {
                    if (j < x && i == y)
                        continue;
                    else
                    {
                        v[i][j] = 1;
                        int y1 = i, x1 = j;
                        makeblock(block + 1, y1, x1);
                        v[i][j] = 0;
                    }
                }
            }
        }
    }
}

int main()
{
    cin >> N >> M;
    int a;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> a;
            v[i][j] = a;
        }
    }

    makeblock(0, 0, 0);
    cout << maximum;
}