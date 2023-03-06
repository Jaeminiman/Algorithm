#include<iostream>
#include<cmath>
#include<vector>
using namespace std;



/*
 * Complete the 'solution' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY cost
 *  2. INTEGER x
 */
const int INF = pow(10,9) + 7;
int power(int n, int cnt){
    int output = 1;
    long long tmp = n;
    while(cnt!=0){
        if(cnt%2 == 0){
            tmp = (tmp * tmp) %INF;
            cnt /= 2;
        }
        else{
            output = (output * tmp)%INF;
            cnt -= 1;
        }
    }
    return output;
}
int solution(vector<int> cost, int x) {
    int output = 0;
    
    // Greedy
    for(int i = cost.size() - 1; i >= 0; i--){
        if(cost[i] <= x){
            x = x - cost[i];
            output = (output + power(2,i))%INF;
        }
    } 
    return output;


}

int main(){
    vector<int> cost = {2,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // 1 18개 // 2^20
    cout << solution(cost,18) << endl;
    cout << power(2,1000) << endl;
    cout << ceil(201L/20) << '\n';
    cout << 201L/20 << '\n';
    
}
