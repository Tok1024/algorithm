#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// dfs->记忆化搜索->dp的复习题
// 转移方程 dp[i] = max(happy[k] + dp[i-k])
// 参数带什么变量是一种考量：
// 可以带left，这个是必须的
// 也可以带当前的happy，可选，如果全局更新得话要带
// 但是记忆化搜索要带返回值，就不用传递这个参数了

// vector<int> path, best_path;
int best = 0;

const int N=10010, M = 105;
int happy[M];
int n, m;
int dp[N];

// v1 朴素的dfs，会超时
void dfs(int left, int h){
    if(left < 0) return;
    if(left == 0){
        if(h > best) {
            // best_path = path;
            best = h;
        }
        return;
    }
    for(int i = 1; i <= m; i++){
        // path.push_back(i);
        dfs(left-i, h+happy[i]);
        // path.pop_back();
    }
};

// 记忆化搜索，但是首先要返回int
int dfs_memo(int left){
    if(left == 0) return 0;
    if(dp[left] != -1) return dp[left];
    int ans = 0;
    for(int i = 1; i <= m && i <= left; i++){
        ans = max(ans, dfs_memo(left-i) + happy[i]);
    }
    return dp[left]=ans;
}

int real_dp(){
    memset(dp, 0, sizeof(dp));
    // 让我们来自底向上计算吧！
    // 外层：最多有x个苹果
    // 内层：每天选择投入几个
    for(int i = 1; i <= n; i++){
        dp[i] = 0; // 给一个初始值，然后你就去遍历吧
        for(int j = 1; j <= m && j <= i; j++){
            dp[i] = max(dp[i], happy[j] + dp[i-j]);
        }
    }
    return dp[n];
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> happy[i];
    }
    memset(dp, -1, sizeof(dp));
    // best = dfs_memo(n);
    best = real_dp();
    cout << best << endl;
    // for(int x: best_path) cout << x << ' ';
    cout << endl;
}