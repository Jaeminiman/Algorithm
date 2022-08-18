#include <iostream>

using namespace std;

int a[500001], tmp[500001];
int N;
long long swaping = 0;

void merge(int start, int end){
    int mid = (start + end) / 2;
    int i = start;
    int j = mid + 1;
    int k = start;
    long long int cnt = 0;

    while(i<=mid && j<=end){
        if(a[i] <= a[j]){
            tmp[k++] = a[i++];
            swaping += cnt;
        }
        else{
            tmp[k++] = a[j++];
            cnt++;
        }
    }

    if(i > mid){
        while(j<=end){
            tmp[k++] = a[j++];
            cnt ++;
        }
    }
    else if(j > end){
        while(i<=mid){
            tmp[k++] = a[i++];
            swaping += cnt;
        }
    }
    for(int i=start;i<=end;i++){
        a[i] = tmp[i];
    }
}

void mergesort(int start, int end){
    if(start<end){
        int mid = (start + end)/2;
        mergesort(start, mid);
        mergesort(mid+1, end);
        merge(start, end);
    }    
}

int main(){
    cin >> N;
    for(int i=0;i<N;i++){
        cin >> a[i];
    }
    mergesort(0,N-1);
    cout << swaping << endl;
}