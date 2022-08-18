#include <iostream>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

vector<pair<int, int>> vec;

int Q(int x, int y, int z)
{
    int cnt = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        int index = vec[i].second;
        if(index <= y && index >= x) cnt++;
        if(cnt == z) return vec[i].first;
    }
    return -1;
}

int main()
{
    int N; int M;
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    {
        int x;
        cin >> x;
        vec.push_back(make_pair(x, i));
    }
    sort(vec.begin(), vec.end());

    for(int i = 0; i < M; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        cout << Q(x, y, z) << endl;
    }
}