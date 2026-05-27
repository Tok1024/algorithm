#include <iostream>
#include <set>
#include <vector>
#include <queue>
using namespace std;

const int N = 1e5+10;
int n, m, x;
vector<int> adj[N];
set<pair<int, int>> repaired;
set<int> station;
vector<pair<int,int>> plans;

int par[N], depth[N];

void bfs_build(int root){
    vector<bool> visited(N, false);
    queue<int> q;
    visited[root] = true; q.push(root);
    depth[root] = 0; par[1] = -1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v: adj[u]){
            if(visited[v]) continue;
            par[v] = u;
            depth[v] = depth[u] + 1;
            q.push(v);
            visited[v] = true;
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
    for(auto it = path_b.rbegin(); it != path_b.rend(); ++it){
        path_a.push_back(*it);
    }
    return path_a;
}

int check(){
    int cnt = 0;
    for(auto p: plans){
        auto path = get_path(p.first, p.second);
        // cout << "plan:" << p.first << "->" << p.second << endl;
        // cout << "path:";
        // for(int x : path){
        //     cout << x << "->";
        // }
        // 模拟补胎
        int remain = 1, last = path.front(), flag = 1;
        for(int i = 1; i < path.size(); i++){
            if(!repaired.count({last, path[i]})) remain -= 1;
            if(remain < 0) {
                flag = 0;
                break;
            }
            if(station.count(path[i])) remain = 1;
            last = path[i];
        }
        if(flag) cnt++;
    }
    return cnt;
}

int main(){
    cin >> n >> x;
    int u, v, k, lastans = 0;
    for(int i = 0; i < n-1; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bfs_build(1);

    cin >> k;
    for(int i = 0; i < k; i++){
        cin >> u;
        station.insert(u);
    }

    int m;cin >> m;
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        plans.push_back({u, v});
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int op;
        cin >> op;
        if(op == 1){
            cin >> u >> v;
            u = u ^ (x * lastans);
            v = v ^ (x * lastans);
            repaired.insert({u, v});
            repaired.insert({v, u});
        }
        else{
            lastans = check();
            cout << lastans << endl;
        }
    }
}