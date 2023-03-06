#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

long long Psum[100001];
int n;
const double epsilon = 1e-6;
int solution(vector<int> box)
{
    n = box.size();
    Psum[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        Psum[i] = Psum[i - 1] + box[i - 1];
    }
    int minimum_height = 0;
    for (int i = 1; i <= n; i++)
    {
        minimum_height = max(minimum_height, (int)ceil((double)Psum[i] / i));
    }

    double average = (double) Psum[n] / n;

    for (int i = n; i >= 2; i--)
    {
        if (minimum_height <= average + epsilon)
        {
            if (Psum[i] - Psum[i - 1] >= average - epsilon)
            {
                long long overflow = (Psum[i] - Psum[i - 1]) - ceil(average);
                Psum[i - 1] += overflow;
            }
            else
            {
                average = max(average, (double) Psum[i - 1] / (i - 1));
            }
        }
        else
        {
            if (Psum[i] - Psum[i - 1] >= minimum_height)
            {
                long long overflow = (Psum[i] - Psum[i - 1]) - minimum_height;
                Psum[i - 1] += overflow;
            }
        }
    }
    
    return max((long long)ceil(average), Psum[1]);
}
int main()
{
    vector<int> box = {21, 26, 19};
    cout << solution(box) << endl;
}