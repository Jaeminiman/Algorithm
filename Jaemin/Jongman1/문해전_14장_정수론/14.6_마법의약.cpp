#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
vector<int> r, p, m;

int gcd(int p, int q){
    if(q==0) return p;
    return gcd(q, p % q);
}
int gcdController(const vector<int>& v){
    int ret = gcd(v[0], v[1]);
    for(int i = 2; i < v.size(); i++){
        ret = gcd(ret,v[i]);
    }
    return ret;
}
int main(){
    int C;
    cin >> C;
    for(int epoch = 0; epoch < C; epoch++){
        r.clear(); p.clear(); m.clear();
        cin >> n;
        for(int i = 0; i < n; i++){
            int x;
            cin >> x;
            r.push_back(x);
        }
        for(int i = 0; i < n; i++){
            int x;
            cin >> x;
            p.push_back(x);
        }
        int GCD = gcdController(r);
        double max_ratio = 0;
        for(int i = 0; i < n; i ++){
            max_ratio = max(max_ratio,p[i]/(double)r[i]);
        }
        int N = 1;
        double C = N / (double)GCD;
        while(C < max(1.0,max_ratio)){
            C += 1/(double)GCD;
        }
        
        for(int i = 0; i < n; i++){
            m.push_back((C * r[i]) - p[i]);
        }
        for(int i = 0; i < n; i++){
            cout << m[i] << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}