#include <iostream>
#include <cmath>
#include <memory.h>

using namespace std;

bool isnono[1000001];

int main()
{
    long long min, max;
    cin >> min >> max;
    long long maxsq = (long long)sqrt(max);
    memset(isnono, 1, sizeof(isnono));

    for(long long i = 2; i <= maxsq; i++)
    { 
        long long cube = i*i;
        long long j = (min % cube == 0) ? 0 : ((min/cube + 1)*cube - min);
        for(long long k = j; j <= max-min; j += cube)
        {
            if(isnono[j]) isnono[j] = false;
        }        
    }
    
    long long answer = 0;
    for(long long i = 0; i <= max-min; i++)
    {
        if(isnono[i])
        {
            answer++;
        }
    }
    cout << answer << endl;
}