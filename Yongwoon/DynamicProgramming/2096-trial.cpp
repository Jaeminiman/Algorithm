#include<iostream>
#include<algorithm>
using namespace std;
int N;
// 100001 X 3 -> 30KB. 메모리 초과
int input[100000][3];
int cache[100000][3];

int big_solve(int n, int m){
    if (n == 0){
        return input[0][m];
    }

    int &res = cache[n][m];
    if (res != -1){
        return res;
    }

    res = 0;
    if (m == 0){
        res = max(big_solve(n-1, 0), big_solve(n-1, 1));
        res += input[n][m];
    }
    else if(m == 1){
        res = max({big_solve(n-1,0), big_solve(n-1,1), big_solve(n-1,2)});
        res += input[n][m];
    }
    else if(m == 2){
        res = max(big_solve(n-1,1), big_solve(n-1,2));
        res += input[n][m];
    }

    return res;
}

int small_solve(int n, int m){
    if (n == 0){
        return input[0][m];
    }

    int &res = cache[n][m];
    if (res != -1){
        return res;
    }

    res = 0;
    if (m == 0){
        res = min(small_solve(n-1, 0), small_solve(n-1, 1));
        res += input[n][m];
    }
    else if(m == 1){
        res = min({small_solve(n-1,0), small_solve(n-1,1), small_solve(n-1,2)});
        res += input[n][m];
    }
    else if(m == 2){
        res = min(small_solve(n-1,1), small_solve(n-1,2));
        res += input[n][m];
    }

    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < 3; j++){
            int tmp;
            cin >> tmp;
            input[i][j] = tmp;
        }
    }
    fill(&cache[0][0], &cache[100000][2], -1);

    int max_res; int min_res;
    max_res = max({big_solve(N-1,0), big_solve(N-1,1), big_solve(N-1,2)});

    fill(&cache[0][0], &cache[100000][2], -1);

    min_res = min({small_solve(N-1,0), small_solve(N-1,1), small_solve(N-1,2)});

    cout << max_res << ' ' << min_res << endl;
    return 0;
}
