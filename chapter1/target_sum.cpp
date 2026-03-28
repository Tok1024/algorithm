#include <iostream>
using namespace std;

const int N = 1e5+10;
int a[N], b[N], c[2*N];
int n, m, x;

int main(){
    cin >> n >> m >> x;
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < m; i++) scanf("%d", &b[i]);

    for(int i = 0, j = m - 1; i < n && j < m;){
        int sum = a[i] + b[j];
        if(sum == x) {
            cout << i << " " << j << endl;
            break;
        }
        else if(sum > x) j--;
        else i++;
    }
}
