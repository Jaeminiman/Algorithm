#include <iostream>
#include <algorithm>

using namespace std; 

int dp_min[100001][3], dp_max[100001][3]; // n번 째 줄, n번 째 숫자일 때 최댓값, 최솟값
int arr[100001][3];
int N;


int max(){
    for(int i=0;i<3;i++){
        dp_max[1][i] = arr[1][i];
    }
    for(int i=2;i<=N;i++){
        dp_max[i][0] = max(dp_max[i-1][0], dp_max[i-1][1]) + arr[i][0];
        dp_max[i][2] = max(dp_max[i-1][2], dp_max[i-1][1]) + arr[i][2];
        dp_max[i][1] = max(dp_max[i-1][0], dp_max[i-1][1]);
        dp_max[i][1] = max(dp_max[i][1], dp_max[i-1][2]) + arr[i][1]; 
    }
    int result = max(dp_max[N][0], dp_max[N][1]);
    return result = max(result, dp_max[N][2]);       
}

int min(){
    for(int i=0;i<3;i++){
        dp_min[1][i] = arr[1][i];
    }
    for(int i=2;i<=N;i++){
        dp_min[i][0] = min(dp_min[i-1][0], dp_min[i-1][1]) + arr[i][0];
        dp_min[i][2] = min(dp_min[i-1][2], dp_min[i-1][1]) + arr[i][2];
        dp_min[i][1] = min(dp_min[i-1][0], dp_min[i-1][1]);
        dp_min[i][1] = min(dp_min[i][1], dp_min[i-1][2]) + arr[i][1]; 
    }
    int result = min(dp_min[N][0], dp_min[N][1]);
    return result = min(result, dp_min[N][2]);
}

int main(){
    cin >> N;
    for(int i=1;i<=N;i++){
        for(int j=0;j<3;j++){
            cin >> arr[i][j];
        }
    }
    cout << max() << " " << min();
}