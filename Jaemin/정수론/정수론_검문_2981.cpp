/*
a % M = b % M = c % M = d % M <=> (b -a) % M = 0 ; (c-a) % M = 0 ; (d-a) % M = 0
즉, 모든 원소에서 가장 작은 원소를 뺀 숫자들의 최대공약수의 약수가 M이 될 수 있는 후보들이다.

시간초과 이유 : 마지막 GCD의 약수를 찾는 과정에서 GCD가 10^9일 수 있어, 여기서 시간초과 발생하는 듯 하다.
그래서 순회를 root(GCD)까지만 하도록 코드를 변경한다.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
int N;
vector<int> nums;
vector<int> D;

int gcd(int a, int b){
    if(b == 0) return a;
    // a가 더 크거나 같게 유지
    return gcd(b, a%b);
}
int main(){
    cin >> N;

    for(int i = 0; i< N; i++){
        int x;
        cin >> x;
        nums.push_back(x);
    }
    sort(nums.begin(), nums.end());
    int smallest = nums[0];
    nums.erase(nums.begin());
    for(int i = 0; i < nums.size() ; i++){
        nums[i] -= smallest;
    }

    // 모든 nums의 숫자의 GCD 구하기
    int GCD = nums[0];
    for(int i = 1; i < nums.size(); i++){
            GCD = gcd(GCD,nums[i]);
    }
    
    int sqrtGCD = int(sqrt(GCD));
    for(int div = 1; div <= sqrtGCD; div++){ 
        if(GCD%div == 0){
            D.push_back(div);
            if(div != GCD/div){
                D.push_back(GCD/div);
            } 
        }
    }
    sort(D.begin(), D.end());
    for(int i = 1; i < D.size(); i ++){
        cout << D[i] << " ";
    }
    cout<< '\n';
    return 0;
}