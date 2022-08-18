#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define mod 1000000007

long long answer = 0;
vector<long long> food;
long long pow[300001]{1,};

int main()
{
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;  
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        long long input;
        cin >> input;
        food.push_back(input);
    }
    sort(food.begin(), food.end()); //정렬

    
    for(int i = 1; i < N; i++)
    {
        pow[i] = (pow[i-1]*2)%mod; //거듭제곱 배열
    }

    for(int i = 0; i < N; i++)
    {
        //음식 하나 고르고, 그 음식이 최대일때 경우의수 - 최소일때 경우의수
        answer += (food[i]*(pow[i] - pow[N-1-i] +mod ))%mod; // mod 분배
        answer %= mod;
    }
    cout << answer << '\n';
}