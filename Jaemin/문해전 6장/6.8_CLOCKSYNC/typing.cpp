코드 9.15 여행하는 외판원 문제를 해결하는 동적 계획법 알고리즘
int n, dist[MAX][MAX];
double cache[MAX][1<<MAX]; // -1로 초기화 해둔다. 1<<MAX == 2^MAX

//항상 0번 도시에서 시작한다고 가정한다.
double shortestPath2(int here, int visited){
    // 기저 사례 : 모든 도시를 다 방문했을 때는 0으로 돌아가고 종료한다.
    if(visited == (1<<n) - 1) return dist[here][0];

    // 메모이제이션
    double& ret = cache[here][visited];
    if(ret != -1) return ret;

    ret = INF; // 최소값을 구하는 것이므로 매우 큰 값 초기화
    // 다음 방문할 도시 모두 시도해 본다.
    for(int next = 0; next < n; next++){
        if(visited & (1<<next)) continue;

        double cand = dist[here][next] + shortestPath2(next, visited + (1 << next));
        ret = min(ret, cand);
    }
    return ret;
}

