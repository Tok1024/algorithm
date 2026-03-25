#include <iostream>
using namespace std;

// 找出数组中逆序对的个数
int n;
const int N = 1e6+10;
int q[N];
int tmp[N];

// version1 : 直接分治，但是遍历两侧的数组需要o(n^2)
// int merge_sort(int q[], int l, int r){
//     if(l >= r) return 0;

//     int mid = (l + r) >> 1;
//     int ans = merge_sort(q, l, mid) + merge_sort(q, mid+1, r);

//     for(int i = l; i <= mid; i++){
//         for(int j = mid+1; j <= r; j++){
//             if(q[i] > q[j]) ans++;
//         }
//     }
//     return ans;
// }

// version2: 其实当统计完两侧的数组后，内部的顺序就不重要了，可以直接排序
// 这样比较两边的话，就可以直接利用有序性
int merge_sort(int q[], int l, int r){
    if(l >= r) return 0;

    int mid = (l + r) >> 1;
    int ans = merge_sort(q, l, mid) + merge_sort(q, mid+1, r);

    int i = l, j = mid + 1, k = 0;
    while(i <= mid && j <= r){
        if(q[i] <= q[j]) tmp[k++] = q[i++];
        else {
            tmp[k++] = q[j++];
            ans += mid - i + 1;
        }
    }
    while(i <= mid) tmp[k++] = q[i++];
    while(j <= r) tmp[k++] = q[j++];

    for(int i = 0; i < k; i++) q[l+i] = tmp[i];
    return ans;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++) scanf("%d", &q[i]);

    cout << merge_sort(q, 0, n-1) << endl;
}