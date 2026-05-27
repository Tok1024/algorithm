#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

const int N = 2e5+5;
vector<int> adj[N]; // 邻接表
int a[N], par[N], depth[N];

int n, m;

void dfs_build(int idx, int p, int d){
    // 简单，但是栈消耗有点大，不如试试bfs？
    par[idx] = p;
    depth[idx] = d;
    for(int x: adj[idx]){
        if(x==p) continue; // 防止无限循环
        dfs_build(x, idx, d+1);
    }
}

void bfs_build(){
    // 记忆一下，bfs需要的是visited， queue
    queue<int> q;
    vector<bool> visited(n+1, 0);
    depth[1] = 0;
    q.push(1);
    visited[1] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v: adj[u]){
            if(visited[v]) continue;
            par[v] = u;
            depth[v] = depth[u] + 1;
            q.push(v);
            visited[v] = 1;
        }
    }
}

vector<int> get_path(int a, int b){
    vector<int> path_a, path_b;
    while(a != b){
        if(depth[a] >= depth[b]){
            path_a.push_back(a);
            a = par[a];
        }
        else{
            path_b.push_back(b);
            b = par[b];
        }
    }
    path_a.push_back(a);
    for(int x: path_b) path_a.push_back(x);
    // for(int x: path_a) cout << x << ' ';
    return path_a;
}

int calc_mex(vector<int>& path){
    unordered_set<int> set;
    for(int x: path) set.insert(a[x]);
    int m = 0;
    while(set.count(m)) m++;
    return m;
}

int main(){
    cin >> n >> m;
    // 先dfs构建depth和parent
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    // dfs_build(1, -1, 0);
    bfs_build();
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        auto path = get_path(x, y);
        cout << calc_mex(path) << endl;
    }
}