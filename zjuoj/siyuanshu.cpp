#include <iostream>
using namespace std;

/* 四元数
 * 计算满足 a^2 + b^2 + c^2 + d^2 = n 的四元数个数
 * 感觉有点像两数之和三数之和那种感觉
 * 但是这可是四个数字，直接枚举怕是不太行
 * 考虑用dfs记忆化搜索
*/
typedef long long ll ;
const int N = 10010;
ll dp[4][N]; // 四个状态，每个状态可能有N个值对应

// 记忆化搜索的模板
ll dfs(int order, ll res){
    // 1. 看看缓存了没，如果有直接返回
    if(dp[order][res] != -1) return dp[order][res];
    // 2. 看看base case:匹配到最后一个数
    if(order == 3){
        ll x = sqrt(res);
        if(x * x != res) return dp[order][res] = 0; // 一边返回一边记录
        else return dp[order][res] = x? 2:1; // 如果是0,只有一种，非零就有正负两种情况
    }
    // 3. 递归情况，遍历每种选择，添加到答案
    // 这里就是看第order个数选择谁
    ll cnt = 0;
    int lim = sqrt(res);
    for(ll i = 0; i <= lim; i++){
        cnt += (i? 2:1) * dfs(order+1, res - i * i);
    }

    // 4. 边记录边 返回
    return dp[order][res] = cnt;
}

int main(){
    ll m, n;
    memset(dp, -1, sizeof(dp));
    cin >> m;
    while(m--){
        cin >> n;
        cout << dfs(0, n) << endl;
    }
}