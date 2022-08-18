#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std; 

int main(){
    int test;
    cin >> test;
    for(int j=0;j<test;j++){
        int time1[1010], dp[1010], deg[1010] = {0,}; // dp는 해당 건물이 지어지는 데 필요한 최소 시간, deg는 해당 건물이 지어지기 위해서 완성되어져야 하는 건물의 개수;
        int N, K, building; 
        vector <int> v[1010]; // 건물의 지어지는 규칙을 담은 vector
        cin >> N >> K;
        for(int i=1;i<=N;i++){
            cin >> time1[i];
        }
        for(int i=0;i<K;i++){
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            deg[b]++;
        }
        cin >> building;
        queue<int> q;
        for(int i=1;i<=N;i++){ // 해당 건물이 지어지는 데 필요한 건물의 개수가 0인 것에 먼저, 건물이 지어지는 시간인 time1[i]를 더해준다. 
            if(deg[i] == 0){
                q.push(i); // 건물이 지어지기 위해 필요한 건물의 개수가 0인 것을 기준으로 한개씩 탐색하여 그 이후의 건물들이 지어지는데 걸리는 시간을 구하기 위해서 큐에 저장
            }
            dp[i] = time1[i]; 
        }

        while(!q.empty()){ // 탐색이 끝나기 전까지 계속 지속
            int temp = q.front();
            q.pop();

            for(int i=0;i<v[temp].size();i++){ // temp 번호의 건물이 지어지고 난 후, 지을 수 있는 건물들의 소요시간을 저장하는 dp값을 저장하기 위해서 반복
                int next = v[temp][i];
                deg[next]--;
                dp[next] = max(dp[next], dp[temp] + time1[next]); // next 번호의 건물이 지어지기 위해서 지어져야 하는 건물들 중 소요시간이 가장 긴 것을 dp값에 저장

                if(deg[next] == 0) q.push(next); // deg가 0이 되면 해당 건물이 지어지는 데 걸리는 최소값을 찾았으므로 이를 기준으로 다시 탐색
            }
        }
        cout << dp[building] << endl;
    }
}