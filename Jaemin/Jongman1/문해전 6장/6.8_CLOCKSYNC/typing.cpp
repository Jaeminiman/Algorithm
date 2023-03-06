코드 9.24 슬라이딩 윈도를 이용한 삼각형 위의 최대 경로 알고리즘
int n, triangle[10000][10000];
int cache[2][10000];
int iterative(){
    // 기저 사례를 계산한다. (맨 바닥)
    for(int x =0; x<n;++x){
        cache[(n-1)%2][x] = triangle[n-1][x];
    }
    // 다른 부분을 계산한다.
    for(int y = n-2; y >= 0 ; y--){
        for(int x=0; x <y+1; x++){
            cache[y % 2][x] = max(cache[(y+1)%2][x] , cache[(y+1)%2][x+1]) + triangle[y][x];
        }
    }
    return cache[0][0];
}