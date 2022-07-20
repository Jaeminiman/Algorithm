#include <iostream>

using namespace std;


int main()
{
    int min[500][500]{};
    int sum[500][500]{};
    int T;
    cin >> T;
    while(T--)
    {
        int K;
        cin >> K;
        for(int k = 0; k < K; k++)
        {   
            cin >> sum[k][k];
        }

        for(int k = 1; k < K; k++)
        {
            for(int i = 0; i < K - k; i++)
            {
                sum[i][i+k] = sum[i][i+k-1] + sum[i+k][i+k];
                int res = 99999999;
                for(int j = 0; j < k; j++)
                {
                    int com = min[i][i+j] + min[i+1+j][i+k];
                    if(res > com) res = com;
                }
                min[i][i+k] = res + sum[i][i+k];
            }
        }
        cout <<  min[0][K-1] << endl;
    }
}