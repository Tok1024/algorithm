#include <iostream>
using namespace std;

// 找出数组中逆序对的个数
int n;
const int N = 1e6+10;
int q[N];
int tmp[N];

void merge_sort(int q[], int l, int r){
    if(l >= r) return;

    int mid = (l + r) >> 1;

    merge_sort(q, l, mid);
    merge_sort(q, mid+1, r);

    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r){
        if(q[i] < q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    while(i <= mid) tmp[k++] = q[i++];
    while(j <= r) tmp[k++] = q[j++];

    for(int i = 0; i < k; i++) q[l+i] = tmp[i];
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", &q[i]);
    merge_sort(q, 0, n-1);
    for(int i = 0; i < n; i++) printf("%d", q[i]);
}