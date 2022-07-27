#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

multimap<int,int, greater<int>> jewels; //중복 가능한 multimap
multiset<int> bags; //중복 가능한 multiset
int N; int K;
long long answer = 0;

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    for(int i = 0; i < N; i++)
    {
        int weight; int value;
        cin >> weight >> value;
        jewels.insert(make_pair(value, weight));
    }

    for(int i = 0; i < K; i++)
    {
        int capacity;
        cin >> capacity;
        bags.insert(capacity);
    }

    for(auto i = jewels.begin(); i != jewels.end(); i++) //multimap begin 부터 end 까지
    {
        int weight = i->second; 
        int value  = i->first;

        auto lb = bags.lower_bound(weight); 
        if(*lb >= weight) //weight 가 arrange 밖이면
        {
            bags.erase(lb);
            answer += value;
        }
    }

    cout << answer << endl;
}
