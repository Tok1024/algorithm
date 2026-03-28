#include <iostream>
using namespace std;

const int N = 1e5+10;
int a[N], b[N];
int n, m;

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < m; i++) scanf("%d", &b[i]);
    // 笨笨的写法
    // int flag = 1;

    // for(int i = 0, j = 0; i < n; i++){

    //     while(j < m && b[j] != a[i]) j++;

    //     if(b[j] != a[i] || j == m) {
    //         cout << "No" << endl;
    //         flag = 0;
    //         break;
    //     }

    //     j++;
    // }

    // if(flag)cout << "Yes" << endl;
    int i = 0, j = 0;
    while(i < n && j < m){
        if(a[i] == b[j]) i++;
        j++;
    }

    if(i == n) cout << "Yes" << endl;
    else cout << "No" << endl;

}