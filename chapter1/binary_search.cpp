#include <algorithm>
#include <iostream>
using namespace std;

int n, t;
const int N = 1e5+10;
int q[N];

//there are two kinds of binary search
//first, search for the right bound

int binary_search1(int q[], int n, int target){
    int l = 0, r = n - 1;
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(q[mid] <= target) l = mid;
        else r = mid - 1;
    }
    return r;
}

//second, search for the left bound

int binary_search2(int q[], int n, int target){
    int l = 0, r = n - 1;
    while(l < r){
        int mid = (l + r) >> 1;
        if(q[mid] >= target) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main(){
    cin >> n >> t;

    for(int i = 0; i < n; i++) scanf("%d", &q[i]);

    cout << binary_search1(q, n, t) << endl;
    cout << binary_search2(q, n, t) << endl;
}