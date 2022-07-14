#include <iostream>

using namespace std;

long long int N, B;
long long int a[5][5], b[5][5],c[5][5];

void multiple(long long int B){
    if(B==1){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                b[i][j] = a[i][j] % 1000;
            }
        }
    }   
    else if(B%2==0){
        multiple(B/2);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                c[i][j] = 0;
                for(int k=0;k<N;k++){
                    c[i][j] += b[i][k]*b[k][j];
                }                            
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                b[i][j] = c[i][j]% 1000;
            }
        }
    }
    else if(B%2==1){
        multiple((B-1)/2);
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                c[i][j] = 0;
                for(int k=0;k<N;k++){
                    c[i][j] += b[i][k]*b[k][j];
                }               
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                b[i][j] = c[i][j]% 1000;
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                c[i][j] = 0;
                for(int k=0;k<N;k++){
                    c[i][j] += b[i][k]*a[k][j];
                }
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                b[i][j] = c[i][j]% 1000;
            }
        }
        
    }
}

int main(){
    cin >> N >> B;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> a[i][j];
        }
    }
    multiple(B);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    
}


