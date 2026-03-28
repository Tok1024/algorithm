#include <iostream>
using namespace std;

int n, m;
const int N = 1e5+10;
int a[N], b[N];

//给b数组的[l,r]处添加c， 也可以用于添加单个元素
void insert(int l, int r, int c){
    b[l] += c;
    b[r+1] -= c;
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        insert(i, i, a[i]);
    }

    int l, r, c;
    while(m --){
        cin >> l >> r >> c;
        insert(l, r, c);
    }

    for(int i = 1; i <= n; i++) {
        b[i] += b[i-1];
        cout << b[i] << ' ';
    }
    cout << endl;
}