#include <iostream>
using namespace std;

int n, q, k;
const int N = 1e6+10;
int a[N];

// 找到一个数在数组里面的 下界， 上界
// 可以转换成 1.找 <= target的右边界 2. >= target的左边界
void number_range(int a[], int n, int target){
    int l = 0, r = n - 1, mid;
    // 左边界

    while(l < r){
        mid = (l + r) >> 1;
        if(a[mid] >= target) r = mid;
        else l = mid + 1;
    }

    if(a[l] != target) {
        cout << "-1 -1" << endl;
        return;
    }

    cout << l << ' ';
    
    l = 0, r = n - 1;
    // 右边界
    while(l < r){
        mid = (l + r + 1) >> 1;
        if(a[mid] <= target) l = mid;
        else r = mid - 1;
    }
    cout << l << endl;;
}

int main(){
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
    while(q--){
        cin >> k;
        number_range(a, n, k);
    }
}