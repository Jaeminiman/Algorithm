#include <string>
#include <vector>
#include <iostream>
#include <deque>
using namespace std;
deque<int> queueA;
deque<int> queueB;
long long summation(deque<int> queue)
{
    long long output = 0;
    for (int i = 0; i < queue.size(); i++)
    {
        output += queue[i];
    }
    return output;
}
int solution(vector<int> queue1, vector<int> queue2)
{   
    for(int i = 0; i < queue1.size(); i++){
         queueA.push_back(queue1[i]);
         queueB.push_back(queue2[i]);
    }

    
    int cnt = 0;
    int answer = -1;
    int size = queue1.size() * 3;
    long long queue1_sum = summation(queueA);
    long long queue2_sum = summation(queueB);
    while (cnt < size)
    {
        if (queue1_sum > queue2_sum)
        {
            int element = queueA.front();
            queueB.push_back(element);
            queueA.pop_front();
            queue1_sum -= element;
            queue2_sum += element;
            cnt++;
        }
        else if (queue1_sum < queue2_sum)
        {

            int element = queueB.front();
            queueA.push_back(element);
            queueB.pop_front();
            queue1_sum += element;
            queue2_sum -= element;
            cnt++;
        }
    
        else
        {
            answer = cnt;
            break;
        }
}

return answer;
}

int main()
{
    vector<int> queue1 = {1, 2, 1, 2};
    vector<int> queue2 = {1, 10, 1, 2};
    cout << solution(queue1, queue2) << endl;
}