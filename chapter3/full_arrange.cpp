#include <iostream>
using namespace std;

// 求n个数字的全排列
const int N = 10;

int n;
int path[N];
bool st[N]; // 记录每个数字是否用过

void dfs(int u){
    // base case
    if(u == n){
        for(int i = 0; i < n; i++) printf("%d ", path[i]);
        puts("");
        return;
    }

    // 在这一层中做选择
    for(int i = 1; i <= n; i++){
        if(!st[i]){
            st[i] = true;
            path[u] = i;
            dfs(u+1);
            st[i] = false;
        }
    }
}

int main(){
    cin >> n;
    dfs(0);
}