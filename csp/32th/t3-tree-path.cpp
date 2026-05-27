#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int N = 2010, M =105;
typedef long long ll ;
int n, m;
int w[N], par[N];
vector<int> sons[N];
bool alive[N];
int tin[N], tout[N];

// 这是一个边删边查的树问题！
// ll dfs_sum_without(int i, int k){
//     ll res = 0;
//     if(alive[i]) res += w[i];
//     for(int x: sons[i]){
//         if(x == k) continue;
//         res += dfs_sum_without(x, k);
//     }
//     return res;
// }

// 计算dfs的时间戳，用于方便的判断子树
int timer = 0;
void dfs_order(int u){
    tin[u] = ++timer;
    for(int v: sons[u]){
        dfs_order(v);
    }
    tout[u] = timer;
}

ll calc_subtree_sum(int i){
    ll res = alive[i]? w[i] : 0;
    for(int x: sons[i]) {
        if(!alive[x]) continue;
        res += calc_subtree_sum(x);
    }
    return res;
}

// bool is_ancestor(int i, int k) {
//     // 判断i是不是k的祖先（或者i==k）,即k是否属于i
//     while(k != -1){
//         if(k == i) return true;
//         k = par[k];
//     }
//     return false;
// }

bool is_ancestor(int i, int k){
    return tin[k] >= tin[i] && tin[k] <= tout[i];
}

void query(int k){
    memset(alive, 1, sizeof(alive));
    int cnt = n; // 活着的节点数量
    while(cnt > 1){
        int min_w = INT_MAX, best;
        ll total = 0;
        for(int i = 1; i <= n; i++){
            if(!alive[i]) continue;
            total += w[i];
        }
        for(int i = 1; i <= n; i++){
            if(!alive[i]) continue;
            ll inside = calc_subtree_sum(i);
            ll outside = total - inside;
            ll delta_w = llabs(inside - outside);
            if(delta_w < min_w){
                best = i;
                min_w = delta_w;
            }
        }
        // cout << "best:"<<best << " min_w" << min_w << endl;
        if(is_ancestor(best, k)){
            for(int i = 1; i <= n; i ++){
                if(alive[i] && !is_ancestor(best, i)) {
                    alive[i] = false; cnt--;
                }
            }
        }
        // 否则删除子树
        else{
            for(int i = 1; i <= n; i ++){
                if(alive[i] && is_ancestor(best, i)) {
                    alive[i] = false; cnt--;
                }
            }
        }
        cout << best << ' ';
    }
    cout << endl;
}

int main(){
    ios::sync_with_stdio();
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> w[i];
    }
    par[1] = -1;
    for(int i = 2; i <= n; i++){
        cin >> par[i];
        sons[par[i]].push_back(i);
    }
    dfs_order(1);
    int t;
    for(int i = 0; i < m; i++){
        cin >> t;
        query(t);
    }

}

// 总结
// 1. dfs：par，sons，alive
// 2. 可以递归遍历树，也可以直接for循环遍历所有节点